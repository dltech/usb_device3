/*
 * Part of USB HID IR adapter. Main file, of IR, initiates IR receiver
 * periodical poll. Runs code recognition and sends a report with a symbol
 * according to a table.
 *
 * Copyright 2021 Mikhail Belkin <dltech174@gmail.com>
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
#include "dma_regs.h"
#include "tim_regs.h"
#include "usb_hid.h"
#include "ir_remote.h"

// A little of global variables, in order to keep data between interrupt calls
volatile uint32_t irFrame[SEQUENCE_LEN];
volatile remotePropStruct remoteProp;
// remote information


void gpioInit(void);
void periodicPortPollTimerInit(void);
void periodicPortPollDmaInit(void);
void sendReportIrqInit(void);
void remotePropInit(void);


uint8_t keyTest(void);
// wakeup from suspend mode by pressed button (not used)
//void wkupByPress(void);

void gpioInit()
{
    // GPIO input mode
    RCC_APB2ENR |= IOPAEN;
    GPIOA_CRL = CNF_PUPD(IR_PIN_INIT);
    GPIOA_ODR = 0;//IR_PIN;
}

// setting up timer of IR receiver periodical reading
void periodicPortPollTimerInit()
{
    RCC_APB1ENR |= TIM2EN;
    TIM2_CR1   = (uint32_t) CKD_CK_INT;
    TIM2_PSC   = (uint32_t) POLL_PSC;
    TIM2_ARR   = (uint32_t) 1;
    TIM2_DIER  = (uint32_t) UDE;
    TIM2_CR1  |= (uint32_t) CEN;
//    NVIC_EnableIRQ(TIM2_IRQn);
//    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);
    TIM2_SR    = 0;
    TIM2_EGR  |= (uint32_t) UG;
}

// dma circular read of port with cyclical save in array
void periodicPortPollDmaInit()
{
    RCC_AHBENR |= DMA1EN;
    DMA1_CPAR2  = (uint32_t) &IR_PORT;
    DMA1_CMAR2  = (uint32_t) irFrame;
    DMA1_CNDTR2 = (uint32_t) SEQUENCE_LEN;
    DMA1_CCR2   = MINC | MSIZE_32BIT | PSIZE_32BIT | PL_LOW | CIRC | TEIE;
}

// setting up timer interrupt for sending a report
void sendReportIrqInit()
{
    RCC_APB1ENR |= TIM3EN;
    TIM3_CR1   = (uint32_t) CKD_CK_INT;
    TIM3_PSC   = (uint32_t) MAXIMAL_PSC;
    TIM3_ARR   = (uint32_t) DECODE_RATE_ARR;
    TIM3_DIER  = (uint32_t) UIE;
    TIM3_CR1  |= (uint32_t) CEN;
    NVIC_EnableIRQ(TIM3_IRQn);
//    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);
    TIM3_SR    = 0;
    TIM3_EGR  |= (uint32_t) UG;
}

// initialisation of a IR remote (it's address and it's button codes)
void remotePropInit()
{
    remoteProp.address = 0;
    remoteProp.codeTable[100] = 0x5d;
    remoteProp.codeTable[200] = 0x57;
}

// main init
void irInit()
{
    gpioInit();
    periodicPortPollTimerInit();
    periodicPortPollDmaInit();
    sendReportIrqInit();
    remotePropInit();
}

uint8_t keyTest()
{
    static int eeee=0;
    static uint8_t key=0;
    if((eeee++)<1000) return 0;
    for( ; key<255 ; ++key) if(remoteProp.codeTable[key] > 0) return key;
    if(key > 254) key = 0;
    return 0;
}

void TIM3_Handler()
{
    uint8_t report[8] = {0};
    report[2] = keyTest();
    sendKbdReport(report);
    TIM3_SR = 0;
}

//void wkupByPress()
//{
//    static uint8_t prevReport = 0;
//    if( gamepadPar.isSusp == 0 ) {
//        return;
//    }
//    if(gamepadPar.report != prevReport) {
//        usbWakeup();
//    }
//    prevReport = gamepadPar.report;
//}
