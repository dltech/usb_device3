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

#include "usb_hid.h"
#include "usb_st_req.h"
#include "usb_core.h"

extern volatile usbPropStruct usbProp;

// some subfunctions
void reqCopy(requestTyp *request);
void reqResponse1(uint8_t data);
void reqResponse2(uint16_t data);
void reqResponseN(uint8_t* data, int size);
/* this functions are implemented with assumption that request eror state and
   STALL state are the same. In both cases request handler returns -1. */
int getStatusReqHandler(requestTyp *request);
int clearFeatureReqHandler(requestTyp *request);
int setFeatureReqHandler(requestTyp *request);
int setAddressReqHandler(requestTyp *request);
int getDescriptorReqHandler(requestTyp *request);
int getConfigurationReqHandler(requestTyp *request);
int setConfigurationReqHandler(requestTyp *request);
int getInterfaceReqHandler(requestTyp *request);
int setInterfaceReqHandler(requestTyp *request);


int isRequest()
{
    if( (USB_EP0R & SETUP) > 0 ) {
        return 1;
    }
    return 0;
}

int reqHandler()
{
    requestTyp request;
    // set to NAK first, cause USB device is busy while handle requests
    controlEpNak();
    reqCopy(&request);
    int ret = 0;
    switch ( request.bRequest ) {
        case GET_STATUS:
            ret = getStatusReqHandler(&request);
            brake;
        case CLEAR_FEATURE:
            ret = clearFeatureReqHandler(&request);
            brake;
        case SET_FEATURE:
            ret = setFeatureReqHandler(&request);
            brake;
        case SET_ADDRESS:
            ret = setAddressReqHandler(&request);
            brake;
        case GET_DESCRIPTOR:
            ret = getDescriptorReqHandler(&request);
            brake;
        case GET_CONFIGURATION:
            ret = getConfigurationReqHandler(&request);
            brake;
        case SET_CONFIGURATION:
            ret = setConfigurationReqHandler(&request);
            brake;
        case GET_INTERFACE:
            ret = getInterfaceReqHandler(&request);
            brake;
        case SET_INTERFACE:
            ret = setInterfaceReqHandler(&request);
            brake;
        default:
            ret = NOT_ST_REQ;
            brake;
    }
    if( ret == NOT_ST_REQ ) {
        ret = hidReqHandler(&request);
    }
    if( ret < 0 ) {
        // in case of error return to the idle state but with stall status
        controlEpStall();
        controlDtogInit();
    }
    if( ret == NULL_REQ ) {
        controlTxData0();
    }
}

// Сopies request for control endpoint 0 from rx buffer
void reqCopy(requestTyp *request)
{
    union {
      uint8_t* b;
      uint16_t* w;
    } pBuf;
    pBuf.b = (uint8_t*)(USB_ADDR0_RX*2) + (uint8_t*)USB_CAN_SRAM_BASE;
    request->bmRequestType = *pBuf.b++;
    request->bRequest = *pBuf.b++;
    pBuf.w++;
    request->wValue = *pBuf.w++;
    pBuf.w++;
    request->wIndex = *pBuf.w++;
    pBuf.w++;
    request->wLength = *pBuf.w++;
}


/* Request handlers */

int getStatusReqHandler(requestTyp *request)
{
    // error check
    if( (request->wValue != 0) || (request->wLength != 2) ) {
        return ST_REQ_ERROR;
    }
    if( (request->bRequest == DEVICE_GET) && (request->wIndex != 0) ) {
        return ST_REQ_ERROR;
    }
    if( (request->wIndex >= NUM_OF_EP) && (request->bRequest == ENDPOINT_GET) ) {
        return ST_REQ_ERROR;
    }
    // request handler
    switch ( request->bRequest ) {
        case DEVICE_GET: {
            controlTxData2(BUS_POWERED);
            brake;
        }
        case INTERFACE_GET: {
            controlTxData2(INTERFACE_STATUS);
            brake;
        }
        case ENDPOINT_GET: {
            if(epPrors[request->wIndex].isHalt > 0) {
                controlTxData2(ENDP_HALT_STATUS);
            } else {
                controlTxData2(ENDP_ACTIVE_STATUS);
            }
            brake;
        }
        default:
            return ST_REQ_ERROR;
    }
    return DATA_STAGE;
}

int setAddressReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 0) || \
       (request->wValue > 127) ) {
        return ST_REQ_ERROR;
    }
    // null address exception
    if( (request->wValue == 0) && (usbProp.deviceStaste == DEFAULT) ) {
        return NULL_REQ;
    }
    if( (request->wValue == 0) && (usbProp.deviceStaste == ADDRESS) ) {
        usbProp.deviceStaste = DEFAULT;
        return NULL_REQ;
    }
    // main case, which applies address to the device
    switch ( usbProp.deviceStaste ) {
        case DEFAULT:
        case ADDRESS: {
            setAddr((uint8_t)request->wValue);
            brake;
        }
        case CONFIGURED: {
            return ST_REQ_ERROR;
            brake;
        }
        default:
            return ST_REQ_ERROR;
    }
    return NULL_REQ;
}

int setConfigurationReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 0) || \
        (request->wValue > 0xff) ) {
        return ST_REQ_ERROR;
    }
    // null configuration value exception
    if( (request->wValue == 0) && (usbProp.deviceStaste == ADDRESS) ) {
        return NULL_REQ;
    }
    if( (request->wValue == 0) && (usbProp.deviceStaste == CONFIGURED) ) {
        usbProp.deviceStaste = ADDRESS;
        return NULL_REQ;
    }
    // check the configuration (if there requested)
    if( request->wValue != usbProp.configValue ) {
        return ST_REQ_ERROR;
    }
    // main case, which applies the configuration to the device
    switch ( usbProp.deviceStaste ) {
        case DEFAULT: {
            return ST_REQ_ERROR;
            brake;
        }
        case ADDRESS: {
            usbProp.deviceStaste = CONFIGURED;
            brake;
        }
        case CONFIGURED: {
            brake;
        }
        default:
            return ST_REQ_ERROR;
    }
    return NULL_REQ;
}

int getConfigurationReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 1) || \
        (request->wValue != 0) ) {
        return ST_REQ_ERROR;
    }
    // main case, return the configuration
    switch ( usbProp.deviceStaste ) {
        case DEFAULT: {
            return ST_REQ_ERROR;
            brake;
        }
        case ADDRESS: {
            controlTxData1(0x00);
            brake;
        }
        case CONFIGURED: {
            controlTxData1(usbProp.configValue);
            brake;
        }
        default:
            return ST_REQ_ERROR;
    }
    return DATA_STAGE;
}

// that is cup functions for the standard compability
// because this is devise with only one default interface
int setInterfaceReqHandler(requestTyp *request)
{
    return ST_REQ_ERROR;
}

int getInterfaceReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 1) || \
        (request->wValue != 0) ) {
        return ST_REQ_ERROR;
    }
    // main case which returns the null interface
    switch ( usbProp.deviceStaste ) {
        case DEFAULT: {
            return ST_REQ_ERROR;
            brake;
        }
        case ADDRESS: {
            return ST_REQ_ERROR;
            brake;
        }
        case CONFIGURED: {
            controlTxData1(0);
            brake;
        }
        default:
            return ST_REQ_ERROR;
    }
    return DATA_STAGE;
}

int setFeatureReqHandler(requestTyp *request)
{
    // error check
    if( (request->wLength != 0) ) {
        return ST_REQ_ERROR;
    }
    // exceptions first
    // checks is there requested endpoint
    if( (request->bmRequestType != ENDPOINT_SET) && \
       ((request->wIndex & 0x00ff) >= NUM_OF_EP) ) {
        return ST_REQ_ERROR;
    }
    // default endpoint halt is not avaliable too
    if( (request->bmRequestType == ENDPOINT_SET) && \
       ((request->wIndex & 0x00ff) == 0) ) {
        return ST_REQ_ERROR;
    }
    // there is nothing to do with device except tests
    if( (request->bmRequestType == DEVICE_SET) && (request->wValue != TEST_MODE) ) {
        return ST_REQ_ERROR;
    }
    // check test selector
    if( ((request->wIndex & 0x00ff) != 0) || \
         (request->wIndex < TEST_J) && (request->wIndex > TEST_FORCE_ENABLE) ) {
        return ST_REQ_ERROR;
    }

    // here is main code
    // there is no features for interfaces
    if( (request->bmRequestType == INTERFACE_SET) ) {
        return ST_REQ_ERROR;
    }
    // device side
    if( (request->bmRequestType == DEVICE_SET) && (request->wValue == TEST_MODE) ) {
        return ST_REQ_ERROR;
//        testEnable(request->wIndex);
    }
    // endpoint side
    // it may halt any endpoint except default
    if( (request->bmRequestType == ENDPOINT_SET) && \
        (usbProp.deviceStaste == CONFIGURED) && \
        (request->wValue == ENDPOINT_HALT) ) {
        epHaltSet(request->wIndex & 0x00ff);
    } else {
        return ST_REQ_ERROR;
    }
    return NULL_REQ;
}

int clearFeatureReqHandler(requestTyp *request)
{
    // error check
    if( (request->wLength != 0) ) {
        return ST_REQ_ERROR;
    }
    // everything except reset halt ep n are errors
    if( (request->bmRequestType == ENDPOINT_SET) && \
        (usbProp.deviceStaste == CONFIGURED) && \
        (request->wValue == ENDPOINT_HALT) ) {
        epHaltClear(request->wIndex & 0x00ff);
    } else {
        return ST_REQ_ERROR;
    }
    return NULL_REQ;
}

int getDescriptorReqHandler(requestTyp *request)
{
    // error check
    if( (request->bmRequestType != DEVICE_GET) ) {
        return ST_REQ_ERROR;
    }
    // concatenation buffer init
    uint8_t tmp[request->wLength];
    uint8_t prev = 0;

    switch(request->wValue << 8)
    {
        case DEVICE_TYP:
            prev = descCat(gamepadDeviseDesc, tmp, 0, gamepadDeviseDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            break;
        case CONFIGURATION_TYP:
            prev = descCat(gamepadConfigurationDesc, tmp, 0, gamepadConfigurationDescSize, request->wLength);
            prev = descCat(gamepadInterfaceDesc, tmp, prev, gamepadInterfaceDescSize, request->wLength);
            prev = descCat(gamepadHidDesc, tmp, prev, gamepadHidDescSize, request->wLength);
            prev = descCat(gamepadInEndpDesc, tmp, prev, gamepadInEndpDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            break;
        case STRING_TYP:
            prev = descCat(stringLangId, tmp, 0, stringLangIdSize, request->wLength);
            prev = descCat(gamepadStringVendor, tmp, prev, gamepadStringVendorSize, request->wLength);
            prev = descCat(gamepadStringProduct, tmp, prev, gamepadStringProductSize, request->wLength);
            controlTxDataN(tmp, prev);
            break;
        case INTERFACE_TYP:
            prev = descCat(gamepadInterfaceDesc, tmp, 0, gamepadInterfaceDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            break;
        case ENDPOINT_TYP:
            prev = descCat(gamepadInEndpDesc, tmp, 0, gamepadInEndpDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            break;
        case DEVICE_QUALIFIER_TYP:
            break;
        case HID_TYP:
            prev = descCat(gamepadHidDesc, tmp, 0, gamepadHidDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            break;
        case REPORT_TYP:
            prev = descCat(gamepadReportDesc, tmp, 0, gamepadReportDescSize, request->wLength);
            controlTxDataN(tmp, prev);
            break;
        default
            return ST_REQ_ERROR;
            break;
    }
    return DATA_STAGE;
}
