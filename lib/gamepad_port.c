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

#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "../libopencm3/include/libopencm3/stm32/timer.h"
#include "../libopencm3/include/libopencm3/cm3/nvic.h"
#include "usb_hid.h"
#include "gamepad_port.h"

volatile gamepadParamStruct gamepadPar;

void gpioInit(void);
void pollIrqInit(void);
void portPoll(void);
void reportUpdate(void);
// wakeup from suspend mode by pressed button (not used)
//void wkupByPress(void);

void gpioInit()
{
    // GPIO input mode with 3.3 pullup (0 if button pressed)
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA_CRL = GPIO_CNF_INPUT_PULL_UPDOWN << ((UP_PIN_INIT*4)+2) \
               | GPIO_CNF_INPUT_PULL_UPDOWN << ((LEFT_PIN_INIT*4)+2) \
               | GPIO_CNF_INPUT_PULL_UPDOWN << ((RIGHT_PIN_INIT*4)+2);
    GPIOA_ODR |= UP_PIN | LEFT_PIN | RIGHT_PIN;
    RCC_APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB_CRL = GPIO_CNF_INPUT_PULL_UPDOWN << ((DN_PIN_INIT*4)+2) \
               | GPIO_CNF_INPUT_PULL_UPDOWN << ((BUTTON1_PIN_INIT*4)+2) \
               | GPIO_CNF_INPUT_PULL_UPDOWN << ((BUTTON2_PIN_INIT*4)+2);
    GPIOB_ODR |= DN_PIN | BUTTON1_PIN | BUTTON2_PIN;
}

void pollIrqInit()
{
    // Timer based interrupt which initiates port poll
    RCC_APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2_CR1   = (uint32_t) TIM_CR1_CKD_CK_INT;
    TIM2_PSC   = (uint32_t) POLL_PSC;
    TIM2_ARR   = (uint32_t) 1;
    TIM2_DIER  = (uint32_t) TIM_DIER_UIE;
    TIM2_CR1  |= (uint32_t) TIM_CR1_CEN;
    nvic_enable_irq(NVIC_TIM2_IRQ);
    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);
    TIM2_SR = 0;
    TIM2_EGR  |= (uint32_t) TIM_EGR_UG;
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
    if( (PORT2 & DN_PIN) == 0) {
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
    if( (PORT2 & BUTTON1_PIN) == 0) {
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
    if( gamepadPar.rightCnt >= cntPressed ) {
        gamepadPar.report = HAT0DEG;
    }
    if( (gamepadPar.rightCnt >= cntPressed) && \
        (gamepadPar.dnCnt >= cntPressed) ) {
        gamepadPar.report = HAT45DEG;
    }
    if( gamepadPar.dnCnt >= cntPressed ) {
        gamepadPar.report = HAT90DEG;
    }
    if( (gamepadPar.dnCnt >= cntPressed) && \
        (gamepadPar.leftCnt >= cntPressed) ) {
        gamepadPar.report = HAT135DEG;
    }
    if( gamepadPar.leftCnt >= cntPressed ) {
        gamepadPar.report = HAT180DEG;
    }
    if( (gamepadPar.leftCnt >= cntPressed) && \
        (gamepadPar.upCnt >= cntPressed) ) {
        gamepadPar.report = HAT225DEG;
    }
    if( gamepadPar.upCnt >= cntPressed ) {
        gamepadPar.report = HAT270DEG;
    }
    if( (gamepadPar.upCnt >= cntPressed) && \
        (gamepadPar.rightCnt >= cntPressed) ) {
        gamepadPar.report = HAT315DEG;
    }
    // buttons
    if( gamepadPar.button1Cnt >= cntPressed ) {
        gamepadPar.report |= BUTTON1ON;
    }
    if( gamepadPar.button2Cnt >= cntPressed ) {
        gamepadPar.report |= BUTTON2ON;
    }
}

void tim2_isr()
{
    static int cnt=0;
    portPoll();
    reportUpdate();
    ++cnt;
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
