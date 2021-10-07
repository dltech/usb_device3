#ifndef H_GAMEPAD_PORT
#define H_GAMEPAD_PORT
/*
 * Part of USB HID gamepad STM32 based solution.
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

#include "inttypes.h"
#include "regs/gpio_regs.h"
#include "STM32F103_CMSIS/system_stm32f103.h"

// port poll frequency in ms
#define POLLRATE    1
#define READ_RATE   7
#define POLL_PSC    (SYSTEM_CLOCK / POLLRATE / 1000) - 1

// pin definitions
#define PORT1           GPIOA_IDR
#define LEFT_PIN        GPIO3
#define UP_PIN          GPIO4
#define RIGHT_PIN       GPIO5
#define DN_PIN          GPIO6
#define BUTTON1_PIN     GPIO7
#define LEFT_PIN_INIT       3U
#define UP_PIN_INIT         4U
#define RIGHT_PIN_INIT      5U
#define DN_PIN_INIT         6U
#define BUTTON1_PIN_INIT    7U
#define PORT2           GPIOB_IDR
#define BUTTON2_PIN     GPIO0
#define BUTTON2_PIN_INIT    0U

// report map
// hat switch
#define XM1   0x02
#define XP1   0x01
#define YM1   0x08
#define YP1   0x04
// buttons
#define BUTTON1ON   0x10
#define BUTTON2ON   0x20

#define cntPressed  READ_RATE / POLLRATE
#define reportSize  1

// buttons condition data
typedef struct {
    int upCnt;
    int dnCnt;
    int leftCnt;
    int rightCnt;
    int button1Cnt;
    int button2Cnt;
    uint8_t report;
} gamepadParamStruct;

// call this to init port poll
void portInit(void);

#endif
