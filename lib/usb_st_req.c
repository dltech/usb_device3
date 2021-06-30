#include "usb_st_req.h"
#include "usb_core.h"

extern volatile usbPropStruct usbProp;


void reqCopy(requestTyp *request);
int getStatusReqHandler();
int setAddressReqHandler();


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
    reqCopy(request);
    int ret;
    switch ( request.bRequest ) {
        case GET_STATUS:
            ret = getStatusReqHandler();
            brake;
        case CLEAR_FEATURE:
            brake;

        case SET_ADDRESS:
            ret = setAddressReqHandler();
            brake;
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
    // requests with data do not understood
}

int getStatusReqHandler()
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

int setAddressReqHandler()
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
        case DEFAULT: {
            USB_DADDR_REG &= ~ADD_MASK;
            USB_DADDR_REG |= request->wValue & ADD_MASK;
            usbProp.deviceStaste = ADDRESS;
            brake;
        }
        case ADDRESS: {
            USB_DADDR_REG &= ~ADD_MASK;
            USB_DADDR_REG |= request->wValue & ADD_MASK;
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

int setConfigurationReqHandler()
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

int getConfigurationReqHandler()
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
// because this is devise with default interface
int getInterfaceReqHandler()
{
    // error check
    if( (request->wIndex != 0) || (request->wLength != 1) || \
        (request->wValue != 0) ) {
        return -1;
    }
    // main case, return the null interface
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

// method overloading imitation one byte and two byte variants
void reqResponse2(uint16_t data)
{

}

void reqResponse1(uint8_t data)
{

}

void hidReqHandler()
{

}
