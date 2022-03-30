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

extern volatile usbPropStruct usbProp;
volatile lineCodingTyp lineCoding;

int getLineCoding(requestTyp *request);
int setLineCoding(requestTyp *request);

int cdcReqHandler(requestTyp *request)
{
    switch (request->bRequest) {
        case GET_REPORT:
            return getLineCoding(request);
        case SET_REPORT:
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
    controlTxDataN((uint8_t*)lineCoding, request->wLength);
    return DATA_STAGE;
}

int setLineCoding(requestTyp *request)
{
    if( (request->bmRequestType != CDC_SET) ) {
        return REQ_ERROR;
    }
    uartSetLine((lineCodingTyp)bmRequestType->data);
}
