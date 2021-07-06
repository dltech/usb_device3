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

#include "usb_hid.h"
#include "gamepad_port.h"

extern volatile gamepadParamStruct gamepadPar;

int getReportReqHandler(requestTyp *request);
int getIdleReqHandler(requestTyp *request);
int setIdleReqHandler(requestTyp *request);

int hidReqHandler(requestTyp *request)
{
    int ret = 0;
    switch (request->bRequest) {
        case GET_REPORT:
            return getReportReqHandler(request);
            brake;
        case GET_IDLE:
            return getIdleReqHandler(request);
            brake;
        case SET_IDLE:
            return setIdleReqHandler(request);
            brake;
        default:
            return -1;
    }
    return -1;
}

int getReportReqHandler(requestTyp *request)
{
    // error check
    if( (request->bmRequestType != HID_GET) || (usbProp.state != CONFIGURED) ) {
        return -1;
    }
    // only one report is supported by this device
    if( (request->wValue == INPUT_REP) && \
        (request->wLength == gamepadPar.reportSize) ) {
        reqResponse1(gamepadPar.report);
    }
    return 0;
}

int getIdleReqHandler(requestTyp *request)
{
    if( (request->bmRequestType != HID_GET) || (request->wLength != 1) \
        (request->wValue != 0) || (usbProp.state != CONFIGURED) {
        return -1;
    }
    reqResponse1(DURATION_TO_PARAM(usbProp.reportDuration));
    return 0;
}

int setIdleReqHandler(requestTyp *request)
{
    if( (request->bmRequestType != HID_SET) || (request->wLength != 0) \
       ((request->wValue&0x00ff) != 0) || (usbProp.state != CONFIGURED) {
        return -1;
    }
    usbProp.reportDuration = REPORT_DURATION(request->wValue);
    return 0;
}
