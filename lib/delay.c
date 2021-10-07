#include "delay.h"

void delay_s(uint16_t s)
{
    uint32_t cnt = ((uint32_t)s)*20;
    while(cnt-- > 0) rough_delay_us(50000);
}

void delay_ms(uint16_t ms)
{
    while(ms-- > 0) rough_delay_us(1000);
}

void rough_delay_us(uint16_t us)
{
    // podbiral na glazok
    volatile uint32_t cnt = (uint32_t)us*(uint32_t)5;
    while(cnt-- > 0);
}
