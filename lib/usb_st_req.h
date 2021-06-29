/* request tables */
// bmRequestType
#define DEVICE_GET          0x80
#define INTERFACE_GET       0x81
#define ENDPOINT_GET        0x82

// bRequest
#define GET_STATUS          0x00
#define CLEAR_FEATURE       0x01
#define SET_FEATURE         0x03
#define SET_ADDRESS         0x05
#define GET_CONFIGURATION   0x08
#define SET_CONFIGURATION   0x09
#define GET_INTERFASE       0x0a
#define SET_INTERFACE       0x0b

// descriptor type
#define DEVICE_TYP           0x01
#define CONFIGURATION_TYP    0x02
#define STRING_TYP           0x03
#define INTERFACE_TYP        0x04
#define ENDPOINT_TYP         0x05
#define DEVICE_QUALIFIER_TYP 0x06

// getStatus defs
// for device
#define REMOTE_WAKEUP       0x0002
#define SELF_POWERED        0x0001
#define BUS_POWERED         0x0000
// for interface
#define INTERFACE_STATUS    0x0000
// for endpoint
#define ENDP_HALT_STATUS    0x0001
#define ENDP_ACTIVE_STATUS  0x0000

#define REQUEST_SIZE        9

// standard request package
typedef struct
{
    uint8_t     bmRequestType;
    uint8_t     bRequest;
    uint16_t    wValue;
    uint16_t    wIndex;
    uint16_t    wLength;
} requestTyp;

int isRequest(void);
int reqHandler(void);
