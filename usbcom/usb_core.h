#ifndef H_USB_CORE
#define H_USB_CORE
/*
 * Part of USB VCP.
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
#include "../lib/regs/gpio_regs.h"
#include <inttypes.h>

#define EP0_BUFFER_SIZE         64
#define EP1_BUFFER_SIZE         64
#define EP2_BUFFER_SIZE         64
// buffer table
#define USB_TABLE_ADDR          0
#define USB_TABLE_END           (USB_TABLE_ADDR + 0x40)
#define EP0_TX_START            USB_TABLE_END
#define EP0_RX_START            (EP0_TX_START + EP0_BUFFER_SIZE)
#define EP1_RX_START            (EP0_RX_START + EP0_BUFFER_SIZE)
#define EP2_TX_START            (EP1_RX_START + EP1_BUFFER_SIZE)
#define EP3_TX_START            (EP2_TX_START + EP2_BUFFER_SIZE)

// endpoints
#define NUM_OF_EP   4
#define configValue 0x01
// pins
#define USBDM_PIN_INIT          3
#define USBDP_PIN_INIT          4
#define USBDM_PIN               GPIO11
#define USBDP_PIN               GPIO12
// properties
#define MULTIPACKAGE_BUFFER_SIZE    128


enum deviceStates {
    DEV_RESET = 0,
    DEFAULT,
    ADDRESS,
    SET_ADDRESS_REQ,
    CONFIGURED
};
enum inEpState {
    EP_IDLE = 1,
    EP_SENT,
    EP_ACK
};
enum reqStage {
    CONTROL_SETUP = 0,
    CONTROL_DATA,
    CONTROL_STATUS,
    CONTROL_DATA_OUT,
    CONTROL_ERROR
};

// all usb low-level information
typedef struct {
    int isHalt;
    int epState;
} epProp;

typedef struct {
    const uint16_t deviseSize;
    const uint16_t configurationSize;
    const uint16_t interfaceSize;
    const uint16_t endpSize;
    const uint16_t functionalSize;
    const uint16_t confTotalSize;
    const uint16_t stringLangIdSize;
    const uint16_t stringVendorSize;
    const uint16_t stringProductSize;
    const uint16_t deviceQualifierSize;
    const uint8_t *devise;
    const uint8_t *configuration;
    const uint8_t *interface1;
    const uint8_t *interface2;
    const uint8_t *ctrlEndp;
    const uint8_t *inEndp;
    const uint8_t *outEndp;
    const uint8_t *functional;
    const uint8_t *stringLangId;
    const uint8_t *stringVendor;
    const uint8_t *stringProduct;
    const uint8_t *deviceQualifier;
} descriptorsTyp;

typedef struct {
    int isRepCompl;
    int isSusp;
    epProp epProps[NUM_OF_EP];
    int deviceState;
    int reportDuration;
    int controlStage;
    uint8_t address;
    uint8_t isBoot;
    const descriptorsTyp *desc;
    uint8_t iFace;
    uint8_t mBuffer[EP0_BUFFER_SIZE];
    int overflow;
} usbPropStruct;

// standard request package
#define REQ_DATA_SIZE 7
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
    DATA_OUT_STAGE,
    NOT_ST_REQ,
};

// usb init
void usbCoreInit(const descriptorsTyp *descr);
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
// output data handler
void vcpTx(uint8_t *data, int size);
int vcpRx(uint8_t *data, int size);

// descriptor concatenator (a part of GetDescr request)
int descCat(const uint8_t *in, uint8_t *out, int prev, uint16_t size, uint16_t mainLen);

#endif
