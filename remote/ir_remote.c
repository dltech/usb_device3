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
#include "usb_hid.h"
#include "ir_decode.h"
#include "ir_remote.h"

volatile codeTyp codeTable[NUM_CODES];

void gpioInit(void);
void pollPortIrqInit(void);
void codeTableInit(void);
uint8_t findCode(uint16_t irCode);

void gpioInit()
{
    // GPIO input mode
    RCC_APB2ENR |= IOPAEN;
    GPIOA_CRL = CNF_FLOATING(IR_PIN_INIT);
    GPIOA_ODR = 0;//IR_PIN;
}

// setting up timer interrupt for sending a report
void pollPortIrqInit()
{
    RCC_APB1ENR |= TIM3EN;
    TIM3_CR1   = (uint32_t) CKD_CK_INT;
    TIM3_PSC   = (uint32_t) POLL_PSC;
    TIM3_ARR   = (uint32_t) 1;//
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
    codeTable[0].irCode = 0;
    codeTable[0].keyboardCode = 0;
    codeTable[1].irCode = 0;
    codeTable[1].keyboardCode = 0;
    codeTable[2].irCode = 0;
    codeTable[2].keyboardCode = 0;
    codeTable[3].irCode = 0;
    codeTable[3].keyboardCode = 0;
    codeTable[4].irCode = 0;
    codeTable[4].keyboardCode = 0;
    codeTable[5].irCode = 0;
    codeTable[5].keyboardCode = 0;
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
    return 0;
}

void TIM3_Handler()
{
    uint16_t code = detect((uint8_t)(IR_PORT & IR_PIN), 0xffff);
    uint8_t report[8];
    report[0] = codeTable[findCode(code)].tabCode;
    report[3] = codeTable[findCode(code)].keyboardCode;
    sendKbdReport(report);
    TIM3_SR = 0;
}
