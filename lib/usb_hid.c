#include "usb_hid.h"

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
    if( (request->bmRequestType != HID_SET) || (request->wLength != 0) \
       ((request->wValue&0x00ff) != 0) || (usbProp.state != CONFIGURED) {
        return -1;
    }    
    // only one report is supported by this device

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
