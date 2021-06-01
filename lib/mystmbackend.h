#ifndef H_MYSTM
#define H_MYSTM

#include "inttypes.h"

#define SCL 9
#define SDA 10

#define I2C_ADD_NE_ADD 0x00
#define TIMEOUT_CLKS    10000

void clkInit(void);
void rough_delay_us(uint16_t us);
void delay_ms(uint16_t ms);
void delay_s(uint16_t s);


#endif
