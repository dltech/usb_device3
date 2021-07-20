#ifndef H_USB_CORE
#define H_USB_CORE
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

#define EP0_BUFFER_SIZE         64*2
#define EP1_BUFFER_SIZE         4
// buffer table
#define USB_TABLE_ADDR          0
#define USB_TABLE_END           USB_TABLE_ADDR + 0x40
#define EP0_TX_START            USB_TABLE_END
#define EP0_RX_START            EP0_TX_START + EP0_BUFFER_SIZE
#define EP1_TX_START            EP0_RX_START
// endpoints
#define NUM_OF_EP   2
#define configValue 0x01

enum deviceStates {
    DEV_RESET = 0,
    DEFAULT,
    ADDRESS,
    CONFIGURED
};
enum inEpState {
    EP_IDLE = 1,
    EP_SENT,
    EP_ACK
};

// all usb low-level information
typedef struct {
    int isHalt;
    int epState;
} epProp;
typedef struct {
    int isSusp;
    epProp epProps[NUM_OF_EP];
    int deviceState;
    int reportDuration;
} usbPropStruct;
volatile usbPropStruct usbProp;

// standard request package
typedef struct
{
    uint8_t     bmRequestType;
    uint8_t     bRequest;
    uint16_t    wValue;
    uint16_t    wIndex;
    uint16_t    wLength;
} requestTyp;
enum reqType {
    REQ_ERROR = -1,
    NULL_REQ = 0,
    DATA_STAGE = 1,
    NOT_ST_REQ
};

// usb init
void usbCoreInit(void);
// this function handles all USB events
void usbCore(void);
// functions for request handler
void setAddr(uint8_t addr);
int epHaltSet(int ep);
int epHaltClear(int ep);
void controlTxData0(void);
void controlTxData1(uint8_t data);
void controlTxData2(uint16_t data);
void controlTxDataN(uint8_t *data, int size);
// for gamepad port poll function
void reportTx(uint8_t report);

#endif
