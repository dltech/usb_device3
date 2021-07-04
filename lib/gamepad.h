/*
 * Main file of USB HID gamepad STM32 based solution.
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

#include "../libopencm3/include/libopencm3/stm32/gpio.h"

// port poll frequency in ms
#define POLLRATE    1
#define READ_RATE   7
#define POLL_PSC    (SYS_CLK / POLLRATE / 72000) - 1

// pin definitions
#define PORT1           GPIOA_ODR
#define UP_PIN          GPIO6
#define LEFT_PIN        GPIO5
#define RIGHT_PIN       GPIO7
#define UP_PIN_INIT          6
#define LEFT_PIN_INIT        5
#define RIGHT_PIN_INIT       7
#define PORT2           GPIOB_ODR
#define DN_PIN          GPIO0
#define BUTTON1_PIN     GPIO1
#define BUTTON2_PIN     GPIO2
#define DN_PIN_INIT          0
#define BUTTON1_PIN_INIT     1
#define BUTTON2_PIN_INIT     2

// report map
// hat switch
#define HAT0DEG     0x00
#define HAT45DEG    0x01
#define HAT90DEG    0x02
#define HAT135DEG   0x03
#define HAT180DEG   0x04
#define HAT225DEG   0x05
#define HAT270DEG   0x06
#define HAT315DEG   0x07
// buttons
#define BUTTON1ON   0x10
#define BUTTON2ON   0x20

// buttons condition data
typedef struct {
    int upCnt = 0;
    int dnCnt = 0;
    int leftCnt = 0;
    int rightCnt = 0;
    int button1Cnt = 0;
    int button2Cnt = 0;
    const int cntPressed = READ_RATE / POLLRATE;
    int report = 0;
} gamepadParamStruct;
volatile gamepadParamStruct gamepadPar;

// main init function, just call this and device will work
void gamepadInit(void);
