

// buffer table
#define USB_TABLE_ADDR          0
#define USB_TABLE_END           USB_BTABLE_ADDR + 0x40
#define EP0_BUFFER_SIZE         64*2

// endpoints
#define NUM_OF_EP   2

typedef struct {
    int isHalt;
} epProp;

enum deviceStates {
    RESET = 0,
    DEFAULT,
    ADDRESS,
    CONFIGURED
};

typedef struct {
    epProp epPrors[NUM_OF_EP];
    int deviceStaste = DEFAULT;
    const uint8_t configValue 0x01;
} usbPropStruct;

volatile usbPropStruct usbProp;

// functions for request handler
void epHaltSet(int nEndpoint);
void epHaltClear(int nEndpoint);
