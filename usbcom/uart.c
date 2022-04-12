/*
 * Part of USB VCP on STM32.
 * All of UART functions including linecoding settings setup.
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
#include "../lib/regs/dma_regs.h"
#include "../lib/regs/gpio_regs.h"
#include "../lib/regs/tim_regs.h"
#include "../lib/regs/rcc_regs.h"
#include "../lib/regs/usart_regs.h"
#include "usb_core.h"
#include "uart.h"

volatile uint8_t uartRx[RX_SIZE];
volatile uint8_t uartTxb[TX_SIZE];
volatile int rxCnt = 0;
volatile lineCodingTyp lineCoding;

void portInit(void);
void periphInit(void);
void dmaInit(void);
void timeoutTimerInit(void);

void portInit()
{
    RCC_APB2ENR |= IOPAEN;
    GPIOA_CRH = CNF_AF_PUSH_PULL(1) | MODE_OUTPUT50(1) | CNF_FLOATING(2);
    GPIOA_ODR = 0;
}

void periphInit()
{
    RCC_APB2ENR |= USART1EN;
    USART1_CR3 |= DMAT;
    USART1_CR1 |= TE | RE | RXNEIE;
    NVIC_EnableIRQ(USART1_IRQn);
}

void dmaInit()
{
    RCC_AHBENR |= DMA1EN;
    DMA1_CPAR4  = (uint32_t)&USART1_DR;
    DMA1_CMAR4  = (uint32_t)uartTxb;
    DMA1_CNDTR4 = 1;
    DMA1_CCR4   = MINC | MSIZE_8BIT | PSIZE_8BIT | PL_LOW | DIR | TCIE;
//    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}

void timeoutTimerInit()
{
    // Timer interrupt for data Rx timeout
    RCC_APB1ENR |= TIM2EN;
    TIM2_CR1  = OPM | CKD_CK_INT;
    TIM2_PSC  = PSC_400BAUD;
    TIM2_ARR  = 0xffff;
    TIM2_DIER = UIE;
    TIM2_SR   = 0;
    TIM2_EGR |= UG;
    NVIC_EnableIRQ(TIM2_IRQn);
//    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);
}

void uartInit()
{
    portInit();
    periphInit();
    lineCodingTyp initConf;
    initConf.dwDTERate = 9600;
    initConf.bCharFormat = LINE_STOP_BIT_1;
    initConf.bParityType = LINE_PARITY_NONE;
    initConf.bDataBits = 8;
    uartSetLine(&initConf);
    dmaInit();
    timeoutTimerInit();
    USART1_CR1 |= UE;
}

// install usart settings using setlinecoding parameters
void uartSetLine(lineCodingTyp *line)
{
    USART1_BRR = USART_BR_CALC(line->dwDTERate);
    if(line->bCharFormat == LINE_STOP_BIT_1P5)  USART1_CR2 = STOP_1P5;
    if(line->bCharFormat == LINE_STOP_BIT_2)    USART1_CR2 = STOP_2;
    USART1_CR1 &= ~((uint32_t)(PS | PCE | M));
    if(line->bParityType == LINE_PARITY_ODD)    USART1_CR1 |= PCE | PS;
    if(line->bParityType == LINE_PARITY_EVEN)   USART1_CR1 |= PCE;
    if(line->bDataBits == 9)                    USART1_CR1 |= M;
    TIM2_ARR = TOUT_CALC(line->dwDTERate);
    TIM2_EGR |= UG;
    TIM2_CR1 |= CEN;
    lineCoding = *line;
}

void USART1_Handler()
{
    if((USART1_SR & RXNE) > 0) {
        uartRx[rxCnt++] = (uint8_t)USART1_DR;
        if(rxCnt == RX_SIZE) {
            vcpTx((uint8_t*)uartRx,rxCnt);
            rxCnt = 0;
        }
        TIM2_CNT = 0;
    }
    USART1_SR = 0;
}

void TIM2_Handler()
{
    TIM2_SR = 0;
    if( rxCnt > 0 ) {
        vcpTx((uint8_t*)uartRx,rxCnt);
        rxCnt = 0;
    }
    TIM2_CNT = 0;
    TIM2_CR1 |= CEN;
}

void uartTx(uint8_t *data, int size)
{
    DMA1_CCR4 &= ~((uint32_t)DMA_EN);
    for(int i=0 ; i<size ; ++i) uartTxb[i] = data[i];
    DMA1_CNDTR4 = (uint32_t)size;
    DMA1_CCR4 |= DMA_EN;
}

void DMA1_Channel4_Handler()
{
//    DMA1_CCR4 &= ~((uint32_t)DMA_EN);
}
