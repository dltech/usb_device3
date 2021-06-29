#include "usb_st_req.h"
#include "usb_core.h"

extern volatile epProp epPrors[NUM_OF_EP];

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
            reqResponse(BUS_POWERED);
            brake;
        }
        case INTERFACE_GET: {
            reqResponse(INTERFACE_STATUS);
            brake;
        }
        case ENDPOINT_GET: {
            if(epPrors[request->wIndex].isHalt > 0) {
                reqResponse(ENDP_HALT_STATUS);
            } else {
                reqResponse(ENDP_ACTIVE_STATUS);
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
    if( (request->wIndex != 0) && (request->wLength != 0) && \
        (request->wValue > 127) ) {
        return -1;
    }

}

void reqResponse(uint16_t data)
{

}

void hidReqHandler()
{

}
