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
            ret = -2;
            brake;
    }
    if( ret == -2 ) {
        ret = hidReqHandler(&request);
    }
    if( ret < 0 ) {
        controlEpStall();
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

// method overloading imitation one byte and two byte variants
void reqResponse1(uint8_t data)
{

}

void reqResponse2(uint16_t data)
{

}

void reqResponseDesc(uint8_t *desc, int descSize, int wLength)
{

}

/* Request handlers */

int getStatusReqHandler(requestTyp *request)
{
    // error check
    if( (request->wValue != 0) || (request->wLength != 2) ) {
        return -1;
    }
    if( (request->bRequest == DEVICE_GET) && (request->wIndex != 0) ) {
        return -1;
    }
    if( (request->wIndex >= NUM_OF_EP) && (request->bRequest == ENDPOINT_GET) ) {
        return -1;
    }
    // request handler
    switch ( request->bRequest ) {
        case DEVICE_GET: {
            reqResponse2(BUS_POWERED);
            brake;
        }
        case INTERFACE_GET: {
            reqResponse2(INTERFACE_STATUS);
            brake;
        }
        case ENDPOINT_GET: {
            if(epPrors[request->wIndex].isHalt > 0) {
                reqResponse2(ENDP_HALT_STATUS);
            } else {
                reqResponse2(ENDP_ACTIVE_STATUS);
            }
            brake;
        }
        default:
            return -1;
    }
    return 0;
}

int setAddressReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 0) || \
       (request->wValue > 127) ) {
        return -1;
    }
    // null address exception
    if( (request->wValue == 0) && (usbProp.deviceStaste == DEFAULT) ) {
        return 0;
    }
    if( (request->wValue == 0) && (usbProp.deviceStaste == ADDRESS) ) {
        usbProp.deviceStaste = DEFAULT;
        return 0;
    }
    // main case, which applies address to the device
    switch ( usbProp.deviceStaste ) {
        case DEFAULT:
        case ADDRESS: {
            setAddr((uint8_t)request->wValue);
            brake;
        }
        case CONFIGURED: {
            return -1;
            brake;
        }
        default:
            return -1;
    }
    return 0;
}

int setConfigurationReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 0) || \
        (request->wValue > 0xff) ) {
        return -1;
    }
    // null configuration value exception
    if( (request->wValue == 0) && (usbProp.deviceStaste == ADDRESS) ) {
        return 0;
    }
    if( (request->wValue == 0) && (usbProp.deviceStaste == CONFIGURED) ) {
        usbProp.deviceStaste = ADDRESS;
        return 0;
    }
    // check the configuration (if there requested)
    if( request->wValue != usbProp.configValue ) {
        return -1;
    }
    // main case, which applies the configuration to the device
    switch ( usbProp.deviceStaste ) {
        case DEFAULT: {
            return -1;
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
            return -1;
    }
    return 0;
}

int getConfigurationReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 1) || \
        (request->wValue != 0) ) {
        return -1;
    }
    // main case, return the configuration
    switch ( usbProp.deviceStaste ) {
        case DEFAULT: {
            return -1;
            brake;
        }
        case ADDRESS: {
            reqResponse1(0x00);
            brake;
        }
        case CONFIGURED: {
            reqResponse1(usbProp.configValue);
            brake;
        }
        default:
            return -1;
    }
    return 0;
}

// that is cup functions for the standard compability
// because this is devise with only one default interface
int setInterfaceReqHandler(requestTyp *request)
{
    return -1;
}

int getInterfaceReqHandler(requestTyp *request)
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 1) || \
        (request->wValue != 0) ) {
        return -1;
    }
    // main case which returns the null interface
    switch ( usbProp.deviceStaste ) {
        case DEFAULT: {
            return -1;
            brake;
        }
        case ADDRESS: {
            return -1;
            brake;
        }
        case CONFIGURED: {
            reqResponse1(0);
            brake;
        }
        default:
            return -1;
    }
    return 0;
}

int setFeatureReqHandler(requestTyp *request)
{
    // error check
    if( (request->wLength != 0) ) {
        return -1;
    }
    // exceptions first
    // checks is there requested endpoint
    if( (request->bmRequestType != ENDPOINT_SET) && \
       ((request->wIndex & 0x00ff) >= NUM_OF_EP) ) {
        return -1;
    }
    // default endpoint halt is not avaliable too
    if( (request->bmRequestType == ENDPOINT_SET) && \
       ((request->wIndex & 0x00ff) == 0) ) {
        return -1;
    }
    // there is nothing to do with device except tests
    if( (request->bmRequestType == DEVICE_SET) && (request->wValue != TEST_MODE) ) {
        return -1;
    }
    // check test selector
    if( ((request->wIndex & 0x00ff) != 0) || \
         (request->wIndex < TEST_J) && (request->wIndex > TEST_FORCE_ENABLE) ) {
        return -1;
    }

    // here is main code
    // there is no features for interfaces
    if( (request->bmRequestType == INTERFACE_SET) ) {
        return -1;
    }
    // device side
    if( (request->bmRequestType == DEVICE_SET) && (request->wValue == TEST_MODE) ) {
        testEnable(request->wIndex);
    }
    // endpoint side
    // it may halt any endpoint except default
    if( (request->bmRequestType == ENDPOINT_SET) && \
        (usbProp.deviceStaste == CONFIGURED) && \
        (request->wValue == ENDPOINT_HALT) ) {
        epHaltSet(request->wIndex & 0x00ff);
    } else {
        return -1;
    }
    return 0;
}

int clearFeatureReqHandler(requestTyp *request)
{
    // error check
    if( (request->wLength != 0) ) {
        return -1;
    }
    // everything except reset halt ep n are errors
    if( (request->bmRequestType == ENDPOINT_SET) && \
        (usbProp.deviceStaste == CONFIGURED) && \
        (request->wValue == ENDPOINT_HALT) ) {
        epHaltClear(request->wIndex & 0x00ff);
    } else {
        return -1;
    }
    return 0;
}

int getDescriptorReqHandler(requestTyp *request)
{
    // error check
    if( (request->bmRequestType != DEVICE_GET) ) {
        return -1;
    }
    // concatenation buffer init
    uint8_t tmp[request->wLength];
    uint8_t prev = 0;

    switch(request->wValue << 8)
    {
        case DEVICE_TYP:
            reqResponseDesc(gamepadDeviseDesc, gamepadDeviseDescSize, request->wLength);
            break;
        case CONFIGURATION_TYP:
            prev = descCat(gamepadConfigurationDesc, tmp, 0, gamepadConfigurationDescSize, request->wLength);
            prev = descCat(gamepadInterfaceDesc, tmp, prev, gamepadInterfaceDescSize, request->wLength);
            prev = descCat(gamepadHidDesc, tmp, prev, gamepadHidDescSize, request->wLength);
            prev = descCat(gamepadInEndpDesc, tmp, prev, gamepadInEndpDescSize, request->wLength);
            reqResponseDesc(tmp, prev, request->wLength);
            break;
        case STRING_TYP:
            prev = descCat(stringLangId, tmp, 0, stringLangIdSize, request->wLength);
            prev = descCat(gamepadStringVendor, tmp, prev, gamepadStringVendorSize, request->wLength);
            prev = descCat(gamepadStringProduct, tmp, prev, gamepadStringProductSize, request->wLength);
            reqResponseDesc(tmp, prev, request->wLength);
            break;
        case INTERFACE_TYP:
            reqResponseDesc(gamepadInterfaceDesc, gamepadInterfaceDescSize, request->wLength);
            break;
        case ENDPOINT_TYP:
            reqResponseDesc(gamepadInEndpDesc, gamepadInEndpDescSize, request->wLength);
            break;
        case DEVICE_QUALIFIER_TYP:
            break;
        case HID_TYP:
            reqResponseDesc(gamepadHidDesc, gamepadHidDescSize, request->wLength);
            break;
        case REPORT_TYP:
            reqResponseDesc(gamepadReportDesc, gamepadReportDescSize, request->wLength);
            break;
        default
            return -1;
            break;
    }
    return 0;
}
