#ifndef H_USB_HID
#define H_USB_HID
/*
 * Part of USB HID gamepad STM32 based solution.
 * Here are HID related request handlers. There are only 3 in simplest case.
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
#include <inttypes.h>
#include "usb_core.h"

// bRequest
#define GET_REPORT      0x01
#define GET_IDLE        0x02
#define GET_PROTOCOL    0x03
#define SET_REPORT      0x09
#define SET_IDLE        0x0a
#define SET_PROTOCOL    0x0b
// bmRequestType
#define HID_GET         0xa1
#define HID_SET         0x21

// report type
#define INPUT_REP       0x0100
#define OUTPUT_REP      0x0200
#define FEATURE_REP     0x0300
// report duration formula, returns period in ms from Set_Idle parameter
#define REPORT_DURATION(wvalue) ((wvalue*4) >> 8)
// vice versa for Get_Idle
#define DURATION_TO_PARAM(ms)   ((uint8_t)(ms/4))

#define KBD_REPORT_SIZE     8
#define KBD_SYMBOL_POINTER  2

// this function is just a part of main request handler
int hidReqHandler(requestTyp *request);
// checks is request of HID type (ret 1) or not (0)
int isHidReqTyp(requestTyp *request);

// send HID gamepad report
int sendReport(uint8_t report, int *ms);
void sendKbdReport(uint8_t *report);


#endif
