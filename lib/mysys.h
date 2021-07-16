#ifndef H_MYSTM
#define H_MYSTM

#include "inttypes.h"

#define SYS_CLK 72000000

#define TIMEOUT_CLKS    10000

void clkInit(void);
// clock source in usb suspend mode
void suspSysClk(void);
// cyclic delays
void rough_delay_us(uint16_t us);
void delay_ms(uint16_t ms);
void delay_s(uint16_t s);


#endif
