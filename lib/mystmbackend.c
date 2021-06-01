#include "mystmbackend.h"
#include "../libopencm3/include/libopencm3/stm32/i2c.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "../libopencm3/include/libopencm3/stm32/gpio.h"


void clkInit()
{
    // не знаю зачем, на всякий случай
    RCC_CR  |= RCC_CR_HSION;
    RCC_CFGR2 = RCC_CFGR2_PREDIV_NODIV;
    // такирование от встроенных RC генераторов, SYS 48 МГц, AHB 48МГц, APB 48 МГц
    uint32_t timeout = TIMEOUT_CLKS;
    if ( (RCC_CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL )
    {
        RCC_CFGR &= ~RCC_CFGR_SW;
        while ( ((RCC_CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) || \
                (--timeout > 1) );
    }
    RCC_CFGR |= RCC_CFGR_PLLSRC_HSI_CLK_DIV2;
    RCC_CR &= (uint32_t)(~RCC_CR_PLLON);
    timeout = TIMEOUT_CLKS;
    while( ((RCC_CR & RCC_CR_PLLRDY) != 0) && (--timeout > 1) );
    RCC_CFGR &= ~RCC_CFGR_PLLMUL;
    RCC_CFGR |= RCC_CFGR_PLLMUL_MUL12;
    RCC_CR |= RCC_CR_PLLON;
    timeout = TIMEOUT_CLKS;
    while( ((RCC_CR & RCC_CR_PLLRDY) == 0) && (--timeout > 1) );
    RCC_CFGR |= (uint32_t) (RCC_CFGR_SW_PLL);
    timeout = TIMEOUT_CLKS;
    while ( ((RCC_CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) && (--timeout > 1) );
    RCC_CFGR |= (uint32_t) RCC_CFGR_HPRE_NODIV | RCC_CFGR_PPRE_NODIV;
    RCC_CSR  |= (uint32_t) RCC_CSR_LSION;
    timeout = TIMEOUT_CLKS;
    while ( ((RCC_CSR & RCC_CSR_LSIRDY) == 0 ) && (--timeout > 0) );
}

void delay_s(uint16_t s)
{
    uint16_t cnt = s*20;
    while(cnt-- > 0) rough_delay_us(50000);
}

void rough_delay_us(uint16_t us)
{
    // podbiral na glazok
    volatile uint32_t cnt = (uint32_t)us*(uint32_t)5;
    while(cnt-- > 0);
}

void delay_ms(uint16_t ms)
{
    while(ms-- > 0) rough_delay_us(1000);
}
