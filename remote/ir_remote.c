/*
 * Part of USB HID IR adapter. Main file, of IR, initiates IR receiver
 * periodical poll. Runs code recognition and sends a report with a symbol
 * according to a table.
 *
 * Copyright 2022 Mikhail Belkin <dltech174@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stm32f103.h"
#include "rcc.h"
#include "tim_regs.h"
#include "delay.h"
#include "usb_hid.h"
#include "ir_decoder.h"
#include "ir_remote.h"

volatile codeTyp codeTable[NUM_CODES];

void gpioInit(void);
void pollPortIrqInit(void);
void codeTableInit(void);
int findCode(uint16_t irCode);

void gpioInit()
{
    // GPIO input mode
    RCC_APB2ENR |= IOPAEN;
    GPIOA_CRL = CNF_FLOATING(IR_PIN_INIT);
    GPIOA_ODR = 0;//IR_PIN;
    RCC_APB2ENR |= IOPBEN;
    GPIOB_CRL = CNF_PUSH_PULL(IR_PIN_INIT) | MODE_OUTPUT50(ON_PIN_INIT);
    GPIOB_ODR = 0;
}

// setting up timer interrupt for sending a report
void pollPortIrqInit()
{
    RCC_APB1ENR |= TIM3EN;
    TIM3_CR1   = (uint32_t) CKD_CK_INT;
    TIM3_PSC   = (uint32_t) POLL_PSC;
    TIM3_ARR   = (uint32_t) 1;
    TIM3_DIER  = (uint32_t) UIE;
    TIM3_CR1  |= (uint32_t) CEN;
    TIM3_SR    = 0;
    TIM3_EGR  |= (uint32_t) UG;
    NVIC_EnableIRQ(TIM3_IRQn);
//    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);
}

// initialisation of a IR remote (it's address and it's button codes)
void codeTableInit()
{
    codeTable[0].irCode = 0xd02f;
    codeTable[0].keyboardCode = 0x52;
    codeTable[1].irCode = 0xd629;
    codeTable[1].keyboardCode = 0x51;
    codeTable[2].irCode = 0x827d;
    codeTable[2].keyboardCode = 0x50;
    codeTable[3].irCode = 0x817e;
    codeTable[3].keyboardCode = 0x4f;
    codeTable[4].irCode = 0xe01f;
    codeTable[4].keyboardCode = 0x2a;
    codeTable[5].irCode = 0xeb14;
    codeTable[5].keyboardCode = 0x29;
    codeTable[6].irCode = 0xa35c;
    codeTable[6].keyboardCode = 0x28;
    codeTable[7].irCode = 0xee11;
    codeTable[7].keyboardCode = 0x27;
    codeTable[8].irCode = 0xfb04;
    codeTable[8].keyboardCode = 0x1e;
    codeTable[9].irCode = 0xfa05;
    codeTable[9].keyboardCode = 0x1f;
    codeTable[10].irCode = 0xf906;
    codeTable[10].keyboardCode = 0x20;
    codeTable[11].irCode = 0xf708;
    codeTable[11].keyboardCode = 0x21;
    codeTable[12].irCode = 0xf609;
    codeTable[12].keyboardCode = 0x22;
    codeTable[13].irCode = 0xf50a;
    codeTable[13].keyboardCode = 0x23;
    codeTable[14].irCode = 0xf30c;
    codeTable[14].keyboardCode = 0x24;
    codeTable[15].irCode = 0xf20d;
    codeTable[15].keyboardCode = 0x25;
    codeTable[16].irCode = 0xf10e;
    codeTable[16].keyboardCode = 0x26;
    codeTable[17].irCode = 0xef10;
    codeTable[17].keyboardCode = 0x81;
    codeTable[18].irCode = 0xed12;
    codeTable[18].keyboardCode = 0x80;
    codeTable[19].irCode = 0xe11e;
    codeTable[19].keyboardCode = 0x7f;
    codeTable[20].irCode = 0x8a75;
    codeTable[20].keyboardCode = 0x2c;
}

// main init
void irInit()
{
    gpioInit();
    pollPortIrqInit();
    codeTableInit();
}

int findCode(uint16_t irCodeIn)
{
    for(int i=0 ; i<NUM_CODES ; ++i)
    {
        if(codeTable[i].irCode == irCodeIn) return i;
    }
    return NUM_CODES -1;
}

void TIM3_Handler()
{
    static int delay = 0;
    uint16_t code = detect((uint8_t)(IR_PORT & IR_PIN), 0xffff);
    uint8_t report[8] = {0};
    if(code != 0xffff) {
        report[0] = codeTable[findCode(code)].tabCode;
        report[2] = codeTable[findCode(code)].keyboardCode;
        sendKbdReport(report);
        delay = 100;
    }
    if(delay > 1) --delay;
    if(delay == 1) {
        sendKbdReport(report);
        delay = 0;
    }
    if(code == ONCODE) {
        ON_PORT |= (uint32_t)ON_PIN;
        delay_ms(80);
        ON_PORT &= ~(uint32_t)ON_PIN;
    }
    TIM3_SR = 0;
}
