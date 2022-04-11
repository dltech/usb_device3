/*
 * Part of USB VCP on STM32.
 * here are two basic requests to install parameters of com port.
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
#include "usb_cdc_req.h"
#include "uart.h"

extern volatile usbPropStruct usbProp;
extern volatile lineCodingTyp lineCoding;

int getLineCoding(requestTyp *request);
int setLineCoding(requestTyp *request);

int cdcReqHandler(requestTyp *request)
{
    switch (request->bRequest) {
        case GET_LINE_CODING:
            return getLineCoding(request);
        case SET_LINE_CODING:
            return setLineCoding(request);
        default:
            return REQ_ERROR;
    }
    return REQ_ERROR;
}

int isCdcReqTyp(requestTyp *request)
{
    if( (request->bmRequestType == CDC_GET) || \
        (request->bmRequestType == CDC_SET) ) {
        return 1;
    }
    return 0;
}

int getLineCoding(requestTyp *request)
{
    if( (request->bmRequestType != CDC_GET) ) {
        return REQ_ERROR;
    }
    uint8_t lineBufer[LINECODING_SIZE];
    lineBufer[0] = (uint8_t)(lineCoding.dwDTERate);
    lineBufer[1] = (uint8_t)(lineCoding.dwDTERate << 8);
    lineBufer[2] = (uint8_t)(lineCoding.dwDTERate << 16);
    lineBufer[3] = (uint8_t)(lineCoding.dwDTERate << 24);
    lineBufer[4] = lineCoding.bCharFormat;
    lineBufer[5] = lineCoding.bParityType;
    lineBufer[6] = lineCoding.bDataBits;
    controlTxDataN(lineBufer, LINECODING_SIZE);
    return DATA_STAGE;
}

int setLineCoding(requestTyp *request)
{
    if( (request->bmRequestType != CDC_SET) ) {
        return REQ_ERROR;
    }
    return DATA_OUT_STAGE;
}
