#include "../libopencm3/include/libopencm3/stm32/gpio.h"

// port poll frequency in ms
#define POLLRATE    1
#define READ_RATE   7
#define POLL_PSC    (SYS_CLK / POLLRATE / 72000) - 1

// pin definitions
#define PORT1           GPIOA_ODR
#define UP_PIN          GPIO6
#define LEFT_PIN        GPIO5
#define RIGHT_PIN       GPIO7
#define PORT2           GPIOB_ODR
#define DN_PIN          GPIO0
#define BUTTON1_PIN     GPIO1
#define BUTTON2_PIN     GPIO2

typedef struct {
    int upCnt = 0;
    int dnCnt = 0;
    int leftCnt = 0;
    int rightCnt = 0;
    int button1Cnt = 0;
    int button2Cnt = 0;
    const int cntPressed = READ_RATE / POLLRATE;
    int report = 0;
} joyParamStruct;
volatile joyParamStruct joyPar;

void joyInit(void);
