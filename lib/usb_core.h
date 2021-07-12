/*
 * Part of USB HID gamepad STM32 based solution.
 * Here are all USB low-level functions.
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

// buffer table
#define USB_TABLE_ADDR          0
#define USB_TABLE_END           USB_BTABLE_ADDR + 0x40
#define EP0_BUFFER_SIZE         64*2
// endpoints
#define NUM_OF_EP   2

enum deviceStates {
    RESET = 0,
    DEFAULT,
    ADDRESS,
    CONFIGURED
};
enum epStatus {

};

// all usb low-level information
typedef struct {
    int isHalt;
    int epType;
} epProp;
typedef struct {
    epProp epPrors[NUM_OF_EP];
    int deviceStaste = DEFAULT;
    const uint8_t configValue 0x01;
    int reportDuration;
} usbPropStruct;
volatile usbPropStruct usbProp;

// usb init
void usbCoreInit(void);
// this function handles all USB events
void usbCore(void);
// functions for request handler
void setAddr(uint8_t addr);
int epHaltSet(int ep);
int epHaltClear(int ep);
void controlEpStall(void);
