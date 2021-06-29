

// buffer table
#define USB_TABLE_ADDR          0
#define USB_TABLE_END           USB_BTABLE_ADDR + 0x40
#define EP0_BUFFER_SIZE         64*2

// endpoints
#define NUM_OF_EP   2

typedef struct {
    int isHalt;
} epProp;

volatile epProp epPrors[NUM_OF_EP];
