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
    return 0;
}

int getIdleReqHandler(requestTyp *request)
{
    return 0;
}

int setIdleReqHandler(requestTyp *request)
{
    return 0;
}
