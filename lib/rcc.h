#ifndef H_RCC
#define H_RCC

#include "regs/rcc_regs.h"


// maximal frequency system clock
void sysClk(void);
// slowest system clock
void suspSysClk(void);
// simplified clock enable interface
//void enablePeriphClock(uint16_t periph);
// simplified clock disable interface
//void resetPeriphClock(uint16_t periph);

#endif
