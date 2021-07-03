#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "../libopencm3/include/libopencm3/stm32/timer.h"
#include "../libopencm3/include/libopencm3/cm3/nvic.h"
#include "gamepad.h"

void portInit(void);
void pollIrqInit(void);
void portPoll(void);
void reportUpdate(void);

void portInit()
{

}

void pollIrqInit()
{
    RCC_APB1ENR |= RCC_APB1ENR_TIM6EN;
    TIM6_CR1   = (uint32_t) TIM_CR1_CKD_CK_INT;
    TIM6_PSC   = (uint32_t) POLL_PSC;
    TIM6_ARR   = (uint32_t) 1;
    TIM6_DIER  = (uint32_t) TIM_DIER_UIE;
    TIM6_EGR  |= (uint32_t) TIM_EGR_UG;
    TIM6_SR = 0;
    nvic_enable_irq(NVIC_TIM6_IRQ);
    nvic_set_priority(NVIC_TIM6_IRQ, 0x00);
}

void joyInit()
{

}

// Information about pressed buttons is obtained by sum of consecutive polls
// of port condition
void portPoll()
{
    if( (PORT1 & UP_PIN) == 0) {
        ++joyPar.upCnt;
    } else {
        joyPar.upCnt = 0;
    }
    if( (PORT2 & DN_PIN) == 0) {
        ++joyPar.dnCnt;
    } else {
        joyPar.dnCnt = 0;
    }
    if( (PORT1 & LEFT_PIN) == 0) {
        ++joyPar.leftCnt;
    } else {
        joyPar.leftCnt = 0;
    }
    if( (PORT1 & RIGHT_PIN) == 0) {
        ++joyPar.rightCnt;
    } else {
        joyPar.rightCnt = 0;
    }
    if( (PORT2 & BUTTON1_PIN) == 0) {
        ++joyPar.button1Cnt;
    } else {
        joyPar.button1Cnt = 0;
    }
    if( (PORT2 & BUTTON2_PIN) == 0) {
        ++joyPar.button2Cnt;
    } else {
        joyPar.button2Cnt = 0;
    }
}

void reportUpdate()
{
    if( joyPar.upCnt >= joyPar.cntPressed ) {

    }

}


void tim6_isr()
{
    portPoll();
    reportUpdate();
}
