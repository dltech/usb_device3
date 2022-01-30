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
//#include "gamepad_port.h"
#include "usb_hid.h"

extern volatile usbPropStruct usbProp;
//extern volatile gamepadParamStruct gamepadPar;

//int getReportReqHandler(requestTyp *request);
int setReportReqHandler(requestTyp *request);
int getIdleReqHandler(requestTyp *request);
int setIdleReqHandler(requestTyp *request);
int setProtocol(requestTyp *request);
int getProtocol(requestTyp *request);

int hidReqHandler(requestTyp *request)
{
    switch (request->bRequest) {
        case GET_REPORT:
            return REQ_ERROR;
//            return getReportReqHandler(request);
        case SET_REPORT:
            return setReportReqHandler(request);
        case GET_IDLE:
            return getIdleReqHandler(request);
        case SET_IDLE:
            return setIdleReqHandler(request);
        case GET_PROTOCOL:
            return getProtocol(request);
        case SET_PROTOCOL:
            return setProtocol(request);
        default:
            return REQ_ERROR;
    }
    return REQ_ERROR;
}

int isHidReqTyp(requestTyp *request)
{
    if( (request->bmRequestType == HID_GET) || \
        (request->bmRequestType == HID_SET) ) {
        return 1;
    }
    return 0;
}

/*int getReportReqHandler(requestTyp *req)
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
}*/

// cup function for request set in case of kbd leds
int setReportReqHandler(requestTyp *req)
{
    // error check
    if( (req->bmRequestType != HID_SET) || (usbProp.deviceState != CONFIGURED) ) {
        return REQ_ERROR;
    }
    return NULL_REQ;
}

int getIdleReqHandler(requestTyp *requestt)
{
    if( (requestt->bmRequestType != HID_GET) || (requestt->wLength != 1) || \
        (requestt->wValue != 0) || (usbProp.deviceState != CONFIGURED) ) {
        return REQ_ERROR;
    }
    controlTxData1(DURATION_TO_PARAM(usbProp.reportDuration));
    return DATA_STAGE;
}

int setIdleReqHandler(requestTyp *requestt)
{
    if( (requestt->bmRequestType != HID_SET) || (requestt->wLength != 0) || \
       ((requestt->wValue&0x00ff) != 0) || (usbProp.deviceState != CONFIGURED) ) {
        return REQ_ERROR;
    }
    usbProp.reportDuration = REPORT_DURATION(requestt->wValue);
    return NULL_REQ;
}

// boot devices supports boot and report protocols, in my case it doesn't mean
// anything
int getProtocol(requestTyp *request)
{
    if( (request->bmRequestType != HID_GET) ) {
        return REQ_ERROR;
    }
    controlTxData1(usbProp.isBoot);
    return DATA_STAGE;
}

int setProtocol(requestTyp *request)
{
    if( (request->bmRequestType != HID_SET) || (request->wValue > 1) ) {
        return REQ_ERROR;
    }
    usbProp.isBoot = (uint8_t)request->wValue;
    return NULL_REQ;
}

void sendKbdReport(uint8_t *report)
{
    if( (usbProp.deviceState != CONFIGURED) || (usbProp.epProps[1].isHalt == 1) ) {
        return;
    }
    reportTxN(report, 8);
}

int sendReport(uint8_t report, int *ms)
{
    if( (usbProp.deviceState != CONFIGURED) || (usbProp.epProps[1].isHalt == 1) ) {
        return 0;
    }
    if( (usbProp.reportDuration > 0) && ((*ms) < usbProp.reportDuration) ) {
        return *ms - usbProp.reportDuration;
    }
    reportTx(report);
    *ms = 0;
    return 0;
}
