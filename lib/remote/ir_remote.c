/*
 * Part of USB HID gamepad STM32 based solution.
 * Detects and collects buttons press. Automatically using interrupt.
 * And forms USB report at maximally accesible speed, which described in
 * HID standard.
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

#include "STM32F103_CMSIS/stm32f103.h"
#include "rcc.h"
#include "regs/dma.h"
#include "regs/tim_regs.h"
#include "usb_hid.h"
#include "gamepad_port.h"

volatile gamepadParamStruct gamepadPar;
uint32_t irFrame[SEQUENCE_LEN];

void gpioInit(void);
void pollIrqInit(void);
void portPoll(void);
void reportUpdate(void);
void repTest(void);
// wakeup from suspend mode by pressed button (not used)
//void wkupByPress(void);

void gpioInit()
{
    // GPIO input mode
    RCC_APB2ENR |= IOPAEN;
    GPIOA_CRL = CNF_PUPD(IR_PIN_INIT);
//    GPIOA_ODR = IR_PIN;
}

void pollIrqInit()
{
// initiate saving IR receivers data in the array through DMA
    RCC_APB1ENR |= TIM2EN;
    TIM2_CR1   = (uint32_t) CKD_CK_INT;
    TIM2_PSC   = (uint32_t) POLL_PSC;
    TIM2_ARR   = (uint32_t) 1;
    TIM2_DIER  = (uint32_t) UIE;
    TIM2_CR1  |= (uint32_t) CEN;
//    NVIC_EnableIRQ(TIM2_IRQn);
//    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);
    TIM2_SR    = 0;
    TIM2_EGR  |= (uint32_t) UG;
    // dma circular read of port
    RCC_AHBENR |= RCC_AHBENR_DMA1EN;
    DMA1_CPAR2  = (uint32_t) &IR_PORT;
    DMA1_CMAR2  = (uint32_t) irFrame;
    DMA1_CNDTR2 = (uint32_t) SEQUENCE_LEN;
    DMA1_CCR2 = MINC | MSIZE_32BIT | PSIZE_32BIT | PL_LOW | CIRC | TEIE;
}

void portInit()
{
    gpioInit();
    gamepadPar.upCnt = 0;
    gamepadPar.dnCnt = 0;
    gamepadPar.leftCnt = 0;
    gamepadPar.rightCnt = 0;
    gamepadPar.button1Cnt = 0;
    gamepadPar.button2Cnt = 0;
    gamepadPar.report = 0;
    pollIrqInit();
}

// Information about pressed buttons is obtained by sum of consecutive polls
// of port condition
void portPoll()
{
    if( (PORT1 & UP_PIN) == 0) {
        ++gamepadPar.upCnt;
    } else {
        gamepadPar.upCnt = 0;
    }
    if( (PORT1 & DN_PIN) == 0) {
        ++gamepadPar.dnCnt;
    } else {
        gamepadPar.dnCnt = 0;
    }
    if( (PORT1 & LEFT_PIN) == 0) {
        ++gamepadPar.leftCnt;
    } else {
        gamepadPar.leftCnt = 0;
    }
    if( (PORT1 & RIGHT_PIN) == 0) {
        ++gamepadPar.rightCnt;
    } else {
        gamepadPar.rightCnt = 0;
    }
    if( (PORT1 & BUTTON1_PIN) == 0) {
        ++gamepadPar.button1Cnt;
    } else {
        gamepadPar.button1Cnt = 0;
    }
    if( (PORT2 & BUTTON2_PIN) == 0) {
        ++gamepadPar.button2Cnt;
    } else {
        gamepadPar.button2Cnt = 0;
    }
}

void reportUpdate()
{
    gamepadPar.report = 0;
    // angles of d-pad including two buttons pressed simulateously
    if( gamepadPar.leftCnt >= cntPressed ) {
        gamepadPar.report |= XM1;
    }
    if( gamepadPar.rightCnt >= cntPressed ) {
        gamepadPar.report |= XP1;
    }
    if( gamepadPar.upCnt >= cntPressed ) {
        gamepadPar.report |= YM1;
    }
    if( gamepadPar.dnCnt >= cntPressed ) {
        gamepadPar.report |= YP1;
    }
    // buttons
    if( gamepadPar.button1Cnt >= cntPressed ) {
        gamepadPar.report |= BUTTON1ON;
    }
    if( gamepadPar.button2Cnt >= cntPressed ) {
        gamepadPar.report |= BUTTON2ON;
    }
}

void repTest()
{
    static int eeee=0;
    eeee++;
    if(eeee>1000) gamepadPar.report = XM1;
    if(eeee>2000) gamepadPar.report = XP1;
    if(eeee>3000) gamepadPar.report = YM1;
    if(eeee>4000) gamepadPar.report = YP1;
    if(eeee>5000) gamepadPar.report = BUTTON1ON;
    if(eeee>6000) gamepadPar.report = BUTTON2ON;
    if(eeee>7000) eeee=0;
}

void TIM2_Handler()
{
    static int cnt=0;
    portPoll();
    reportUpdate();
    ++cnt;
//    repTest();
    sendReport(gamepadPar.report, &cnt);
    TIM2_SR = 0;
//    wkupByPress();
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
