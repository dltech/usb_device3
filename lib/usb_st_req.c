/*
 * Part of USB HID gamepad STM32 based solution.
 * All standard USB2.0 requests are implemented here.
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
#include "usb_core.h"
#include "gamepad_desc.h"
#include "usb_st_req.h"

extern volatile usbPropStruct usbProp;

// requests
int getStatusReqHandler(requestTyp *request);
int clearFeatureReqHandler(requestTyp *request);
int setFeatureReqHandler(requestTyp *request);
int setAddressReqHandler(requestTyp *request);
int getDescriptorReqHandler(requestTyp *request);
int getConfigurationReqHandler(requestTyp *request);
int setConfigurationReqHandler(requestTyp *request);
int getInterfaceReqHandler(requestTyp *request);
int setInterfaceReqHandler(requestTyp *request);

// handler of mandatory standard requests
int stReqHandler(requestTyp *request)
{
    switch ( request->bRequest ) {
        case GET_STATUS:
            return getStatusReqHandler(request);
        case CLEAR_FEATURE:
            return clearFeatureReqHandler(request);
        case SET_FEATURE:
            return setFeatureReqHandler(request);
        case SET_ADDRESS:
            return setAddressReqHandler(request);
        case GET_DESCRIPTOR:
            return getDescriptorReqHandler(request);
        case GET_CONFIGURATION:
            return getConfigurationReqHandler(request);
        case SET_CONFIGURATION:
            return setConfigurationReqHandler(request);
        case GET_INTERFACE:
            return getInterfaceReqHandler(request);
        case SET_INTERFACE:
            return setInterfaceReqHandler(request);
        default:
            return NOT_ST_REQ;
    }
    return REQ_ERROR;
}

/* Request handlers */

int getStatusReqHandler(requestTyp *request)
{
    // error check
    if( (request->wValue != 0) || (request->wLength != 2) ) {
        return REQ_ERROR;
    }
    if( (request->bRequest == DEVICE_GET) && (request->wIndex != 0) ) {
        return REQ_ERROR;
    }
    if( (request->wIndex >= NUM_OF_EP) && (request->bRequest == ENDPOINT_GET) ) {
        return REQ_ERROR;
    }
    // request handler
    switch( (uint8_t)request->bRequest ) {
        case DEVICE_GET:
            controlTxData2(BUS_POWERED);
            return DATA_STAGE;
        case INTERFACE_GET:
            controlTxData2(INTERFACE_STATUS);
            return DATA_STAGE;
        case ENDPOINT_GET:
            if(usbProp.epProps[request->wIndex].isHalt > 0) {
                controlTxData2(ENDP_HALT_STATUS);
            } else {
                controlTxData2(ENDP_ACTIVE_STATUS);
            }
            return DATA_STAGE;
    }
    return REQ_ERROR;
}

int setAddressReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 0) || \
       (request->wValue > 127) || (request->wValue == 0) ) {
        return REQ_ERROR;
    }
    // main case, which applies address to the device
    switch ( usbProp.deviceState ) {
        case DEFAULT:
        case ADDRESS:
            usbProp.deviceState = SET_ADDRESS_REQ;
            usbProp.address = (uint8_t)request->wValue;
            return NULL_REQ;
        case CONFIGURED:
            return REQ_ERROR;
    }
    return REQ_ERROR;
}

int setConfigurationReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 0) || \
        (request->wValue > 0xff) ) {
        return REQ_ERROR;
    }
    // null configuration value exception
    if( (request->wValue == 0) && (usbProp.deviceState == ADDRESS) ) {
        return NULL_REQ;
    }
    if( (request->wValue == 0) && (usbProp.deviceState == CONFIGURED) ) {
        usbProp.deviceState = ADDRESS;
        return NULL_REQ;
    }
    // check the configuration (if there requested)
    if( request->wValue != configValue ) {
        return REQ_ERROR;
    }
    // main case, which applies the configuration to the device
    switch ( usbProp.deviceState ) {
        case DEFAULT:
            return REQ_ERROR;
        case ADDRESS:
            usbProp.deviceState = CONFIGURED;
            return NULL_REQ;
        case CONFIGURED:
            return NULL_REQ;
    }
    return REQ_ERROR;
}

int getConfigurationReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 1) || \
        (request->wValue != 0) ) {
        return REQ_ERROR;
    }
    // main case, return the configuration
    switch ( usbProp.deviceState ) {
        case DEFAULT:
            return REQ_ERROR;
        case ADDRESS:
            controlTxData1(0x00);
            return DATA_STAGE;
        case CONFIGURED:
            controlTxData1(configValue);
            return DATA_STAGE;
    }
    return REQ_ERROR;
}

// that is cup functions for the standard compability
// because this is devise with only one default interface
int setInterfaceReqHandler(requestTyp *request)
{
    request->wLength = 0;
    return REQ_ERROR;
}

int getInterfaceReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wValue != 0) ) {
        return REQ_ERROR;
    }
    // main case which returns the null interface
    switch ( usbProp.deviceState ) {
        case DEFAULT:
            return REQ_ERROR;
        case ADDRESS:
            return REQ_ERROR;
        case CONFIGURED:
            controlTxData1(0);
            return DATA_STAGE;
    }
    return REQ_ERROR;
}

int setFeatureReqHandler(requestTyp *request)
{
    // error check
    if( (request->wLength != 0) ) {
        return REQ_ERROR;
    }
    // exceptions first
    // checks is there requested endpoint
    if( (request->bmRequestType != ENDPOINT_SET) && \
       ((request->wIndex & 0x00ff) >= NUM_OF_EP) ) {
        return REQ_ERROR;
    }
    // default endpoint halt is not avaliable too
    if( (request->bmRequestType == ENDPOINT_SET) && \
       ((request->wIndex & 0x00ff) == 0) ) {
        return REQ_ERROR;
    }
    // there is nothing to do with device except tests
    if( (request->bmRequestType == DEVICE_SET) && (request->wValue != TEST_MODE) ) {
        return REQ_ERROR;
    }
    // check test selector
    if( ((request->wIndex & 0x00ff) != 0) || \
         (request->wIndex < TEST_J) || (request->wIndex > TEST_FORCE_ENABLE) ) {
        return REQ_ERROR;
    }

    // here is main code
    // there is no features for interfaces
    if( (request->bmRequestType == INTERFACE_SET) ) {
        return REQ_ERROR;
    }
    // device side
    if( (request->bmRequestType == DEVICE_SET) && (request->wValue == TEST_MODE) ) {
        return REQ_ERROR;
//        testEnable(request->wIndex);
    }
    // endpoint side
    // it may halt any endpoint except default
    if( (request->bmRequestType == ENDPOINT_SET) && \
        (usbProp.deviceState == CONFIGURED) && \
        (request->wValue == ENDPOINT_HALT) ) {
        epHaltSet(request->wIndex & 0x00ff);
    } else {
        return REQ_ERROR;
    }
    return NULL_REQ;
}

int clearFeatureReqHandler(requestTyp *request)
{
    // error check
    if( (request->wLength != 0) ) {
        return REQ_ERROR;
    }
    // everything except reset halt ep n are errors
    if( (request->bmRequestType == ENDPOINT_SET) && \
        (usbProp.deviceState == CONFIGURED) && \
        (request->wValue == ENDPOINT_HALT) ) {
        epHaltClear(request->wIndex & 0x00ff);
    } else {
        return REQ_ERROR;
    }
    return NULL_REQ;
}

int getDescriptorReqHandler(requestTyp *request)
{
    // error check
//    if( (request->bmRequestType != DEVICE_GET) ) {
//        return REQ_ERROR;
//    }
    // concatenation buffer init
    uint8_t tmp[request->wLength];
    int prev = 0;

    switch(request->wValue)
    {
        case DEVICE_TYP<<8:
            prev = descCat(gamepadDeviseDesc, tmp, 0, gamepadDeviseDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            return DATA_STAGE;
        case CONFIGURATION_TYP<<8:
            prev = descCat(gamepadConfigurationDesc, tmp, 0, gamepadConfigurationDescSize, request->wLength);
            prev = descCat(gamepadInterfaceDesc, tmp, prev, gamepadInterfaceDescSize, request->wLength);
            prev = descCat(gamepadHidDesc, tmp, prev, gamepadHidDescSize, request->wLength);
            prev = descCat(gamepadInEndpDesc, tmp, prev, gamepadInEndpDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            return DATA_STAGE;
        case STRING_TYP<<8:
            prev = descCat(stringLangId, tmp, 0, stringLangIdSize, request->wLength);
            controlTxDataN(tmp, prev);
            return DATA_STAGE;
        case (STRING_TYP<<8)+1:
            prev = descCat(gamepadStringVendor, tmp, prev, gamepadStringVendorSize, request->wLength);
            controlTxDataN(tmp, prev);
            return DATA_STAGE;
        case (STRING_TYP<<8)+2:
            prev = descCat(gamepadStringProduct, tmp, prev, gamepadStringProductSize, request->wLength);
            controlTxDataN(tmp, prev);
            return DATA_STAGE;
        case INTERFACE_TYP<<8:
            prev = descCat(gamepadInterfaceDesc, tmp, 0, gamepadInterfaceDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            return DATA_STAGE;
        case ENDPOINT_TYP<<8:
            prev = descCat(gamepadInEndpDesc, tmp, 0, gamepadInEndpDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            return DATA_STAGE;
        case DEVICE_QUALIFIER_TYP<<8:
            return REQ_ERROR;
        case ((uint16_t)HID_TYP)<<8:
            prev = descCat(gamepadHidDesc, tmp, 0, gamepadHidDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            return DATA_STAGE;
        case ((uint16_t)REPORT_TYP)<<8:
            prev = descCat(gamepadReportDesc, tmp, 0, gamepadReportDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            return DATA_STAGE;
    }
    return REQ_ERROR;
}
