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

// port poll frequency in us
#define POLLRATE        200
// port read frame in ms
#define SEQUENCE_TIME   25
// symbol decode rate in ms
#define READ_RATE       SEQUENCE_TIME
// calculating for fre prog
#define POLL_PSC    (SYSTEM_CLOCK / POLLRATE) - 1
#define SEQUENCE_LEN     SEQUENCE_TIME * 1000 / POLLRATE


// pin definitions
#define IR_PORT     GPIOA_IDR
#define IR_PIN      GPIO0
#define IR_PIN_INIT 0U

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

uint32_t portData[]

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
