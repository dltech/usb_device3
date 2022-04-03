#ifndef H_USB_HID
#define H_USB_HID
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

// linecoding parameters
typedef struct {
  uint32_t dwDTERate;
  uint8_t bCharFormat;
  uint8_t bParityType;
  uint8_t bDataBits;
} lineCodingTyp;
enum {
  STOP_BIT_1 = 0,
  STOP_BIT_1P5,
  STOP_BIT_2
};
enum {
  PARITY_NONE = 0,
  PARITY_ODD,
  PARITY_EVEN,
  PARITY_MARK,
  PARITY_SPACE
};

// this function is just a part of main request handler
int cdcReqHandler(requestTyp *request);
// checks is request of HID type (ret 1) or not (0)
int isCdcReqTyp(requestTyp *request);

#endif
