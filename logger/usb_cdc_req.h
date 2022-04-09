#ifndef H_USB_CDC
#define H_USB_CDC
/*
 * Part of USB VCP on STM32.
 * Here are CDC related request handlers.
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
#include <inttypes.h>
#include "usb_core.h"

#define CDC_GET 0x61
#define CDC_SET 0x21

// bRequest
#define SET_LINE_CODING         0x20
#define GET_LINE_CODING         0x21
#define SET_CONTROL_LINE_STATE  0x22
#define SERIAL_STATE            0x20

// this function is just a part of main request handler
int cdcReqHandler(requestTyp *request);
// checks is request of HID type (ret 1) or not (0)
int isCdcReqTyp(requestTyp *request);

#endif
