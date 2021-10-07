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
#include "regs/tim_regs.h"
#include "usb_hid.h"
#include "gamepad_port.h"

volatile gamepadParamStruct gamepadPar;

void gpioInit(void);
void pollIrqInit(void);
void portPoll(void);
void reportUpdate(void);
void repTest(void);
// wakeup from suspend mode by pressed button (not used)
//void wkupByPress(void);

void gpioInit()
{
    // GPIO input mode with 3.3 pullup (0 if button pressed)
    RCC_APB2ENR |= IOPAEN;
    GPIOA_CRL = (uint32_t)CNF_PUPD(UP_PIN_INIT) | CNF_PUPD(LEFT_PIN_INIT) | \
                CNF_PUPD(RIGHT_PIN_INIT) | CNF_PUPD(DN_PIN_INIT) | \
                CNF_PUPD(BUTTON1_PIN_INIT);
    GPIOA_ODR |= UP_PIN | LEFT_PIN | RIGHT_PIN | DN_PIN | BUTTON1_PIN;
    RCC_APB2ENR |= IOPBEN;
    GPIOB_CRL = CNF_PUPD(BUTTON2_PIN_INIT);
    GPIOB_ODR |= BUTTON2_PIN;
}

void pollIrqInit()
{
    // Timer based interrupt which initiates port poll
    RCC_APB1ENR |= TIM2EN;
    TIM2_CR1   = (uint32_t) CKD_CK_INT;
    TIM2_PSC   = (uint32_t) POLL_PSC;
    TIM2_ARR   = (uint32_t) 1;
    TIM2_DIER  = (uint32_t) UIE;
    TIM2_CR1  |= (uint32_t) CEN;
    NVIC_EnableIRQ(TIM2_IRQn);
//    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);
    TIM2_SR = 0;
    TIM2_EGR  |= (uint32_t) UG;
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
