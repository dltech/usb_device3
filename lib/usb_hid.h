// bRequest
#define GET_REPORT      0x01
#define GET_IDLE        0x02
#define GET_PROTOCOL    0x03
#define SET_REPORT      0x09
#define SET_IDLE        0x0a
#define SET_PROTOCOL    0x0b
// bmRequestType
#define HID_GET         0xa1
#define HID_SET         0x21
// descriptor types
#define HID_TYP         0x21
#define REPORT_TYP      0x22
#define PHYSICAL_TYP    0x23
// report type
#define INPUT_REP       0x0100
#define OUTPUT_REP      0x0200
#define FEATURE_REP     0x0300
// report duration formula
#define REPORT_DURATION(wvalue) ((ms*4) >> 8)

int hidReqHandler(requestTyp *request);
