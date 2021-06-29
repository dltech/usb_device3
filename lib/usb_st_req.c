#include "usb_st_req.h"

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
    if( (request->wValue != 0) && (request->wLength != 2) ) {
        return -1;
    }
    switch ( request.bRequest ) {
        case DEVICE_GET: {
            reqResponse();
        }
        case INTERFACE_GET: {
            reqResponse(INTERFACE_STATUS);
        }
        case ENDPOINT_GET: {
            reqResponse(ENDP_HALT_STATUS);
        }
    }

}

int getStatusReqHandler()
{
    if( (request->wValue != 0) && (request->wLength != 2) ) {
        return -1;
    }

}

void reqResponse(uint16_t data)
{

}

void hidReqHandler()
{

}
