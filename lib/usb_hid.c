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
#include "gamepad_port.h"
#include "usb_hid.h"

int getReportReqHandler(requestTyp *request);
int getIdleReqHandler(requestTyp *request);
int setIdleReqHandler(requestTyp *request);

int hidReqHandler(requestTyp *request)
{
    switch (request->bRequest) {
        case GET_REPORT:
            return getReportReqHandler(request);
        case GET_IDLE:
            return getIdleReqHandler(request);
        case SET_IDLE:
            return setIdleReqHandler(request);
        default:
            return REQ_ERROR;
    }
    return REQ_ERROR;
}

int getReportReqHandler(requestTyp *req)
{
    // error check
    if( (req->bmRequestType != HID_GET) || (usbProp.deviceState != CONFIGURED) ) {
        return REQ_ERROR;
    }
    // only one report is supported by this device
    if( (req->wValue == INPUT_REP) && \
        (req->wLength == reportSize) ) {
        controlTxData1(gamepadPar.report);
        return DATA_STAGE;
    }
    return NULL_REQ;
}

int getIdleReqHandler(requestTyp *req)
{
    if( (req->bmRequestType != HID_GET) || (((uint16_t)req->wLength) != ((uint16_t)1)) \
        (req->wValue != 0) || (usbProp.deviceState != CONFIGURED) ) {
        return REQ_ERROR;
    }
    controlTxData1(DURATION_TO_PARAM(usbProp.reportDuration));
    return DATA_STAGE;
}

int setIdleReqHandler(requestTyp *req)
{
    if( (req->bmRequestType != HID_SET) || (((uint16_t)req->wLength) != ((uint16_t)0)) \
       ((req->wValue&0x00ff) != 0) || (usbProp.deviceState != CONFIGURED) ) {
        return REQ_ERROR;
    }
    usbProp.reportDuration = REPORT_DURATION(req->wValue);
    return NULL_REQ;
}

void sendReport(uint8_t report, int *ms)
{
    static uint8_t prevReport;
    if( (usbProp.reportDuration == 0) && (prevReport != report) ) {
        reportTx(report);
        *ms = 0;
    } else if(*ms > usbProp.reportDuration) {
        reportTx(report);
        *ms = 0;
    }
}
