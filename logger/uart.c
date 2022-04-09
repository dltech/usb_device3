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
#include "../lib/regs/usart_regs.h"
#include "uart.h"

volatile uint8_t uartRx[64];
volatile uint8_t uartTx[64];

void portInit(void);
void periphInit(void);
void dmaInit(void);
void timeoutTimerInit(void);

void portInit()
{
    RCC_APB2ENR |= IOPAEN;
    GPIOA_CRL = CNF_AF_PUSH_PULL(UART_TX) | CNF_FLOATING(UART_RX);
    GPIOA_ODR = 0;
}

void periphInit()
{
    USART1_CR1 |= TE | RE | UE;
    USART1_CR3 |= DMAT | DMAR | EIE;
}

void dmaInit()
{
    RCC_AHBENR |= DMA1EN;
    DMA1_CPAR4  = (uint32_t) uartTx;
    DMA1_CMAR4  = (uint32_t) &USART1_DR;
    DMA1_CNDTR4 = (uint32_t) 64;
    DMA1_CCR4   = MINC | MSIZE_32BIT | PSIZE_32BIT | PL_LOW | CIRC | DIR | DMA_EN;
    DMA1_CPAR5  = (uint32_t) &USART1_DR;
    DMA1_CMAR5  = (uint32_t) uartRx;
    DMA1_CNDTR5 = (uint32_t) 64;
    DMA1_CCR5   = MINC | MSIZE_32BIT | PSIZE_32BIT | PL_LOW | CIRC | DMA_EN;
}

void timeoutTimerInit()
{
    // Timer interrupt for data Rx timeout
    RCC_APB1ENR |= TIM2EN;
    TIM2_CR1   = (uint32_t) CKD_CK_INT;
    TIM2_PSC   = (uint32_t) MAXIMAL_PSC;
    TIM2_ARR   = (uint32_t) POLL_ARR;
    TIM2_DIER  = (uint32_t) UIE;
    TIM2_CR1  |= (uint32_t) CEN;
    NVIC_EnableIRQ(TIM2_IRQn);
//    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);
    TIM2_SR = 0;
    TIM2_EGR  |= (uint32_t) UG;
}

void uartInit()
{
    portInit();
    dmaInit();
    lineCodingTyp initConf;
    initConf.dwDTERate = 9600;
    initConf.bCharFormat = LINE_STOP_BIT_1;
    initConf.bParityType = LINE_PARITY_NONE;
    initConf.bDataBits = 8;
    uartSetLine(&initConf);
    periphInit();
}

// install usart settings using setlinecoding parameters
void uartSetLine(lineCodingTyp *line)
{
    USART1_BRR = USART_BR_CALC(line->dwDTERate);
    if(line->bCharFormat == LINE_STOP_BIT_1)    USART1_CR2 |= STOP_1;
    if(line->bCharFormat == LINE_STOP_BIT_1P5)  USART1_CR2 |= STOP_1P5;
    if(line->bCharFormat == LINE_STOP_BIT_2)    USART1_CR2 |= STOP_2;
    if(line->bParityType == LINE_PARITY_ODD)    USART1_CR1 |= PCE | PS;
    if(line->bParityType == LINE_PARITY_EVEN)   USART1_CR1 |= PCE;
    if(line->bDataBits == 9)                    USART1_CR1 |= M;
}
