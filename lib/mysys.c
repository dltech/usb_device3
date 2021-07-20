#include "mysys.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "../libopencm3/include/libopencm3/stm32/gpio.h"
#include "../libopencm3/include/libopencm3/stm32/flash.h"

void sysClk()
{
    // включаем кварц, ждем пока прогреется
    RCC_CR |= (uint32_t)RCC_CR_HSEON;
    uint32_t timeout = 1e8;
    while ( ((RCC_CR & RCC_CR_HSERDY) == 0) && (--timeout > 1) );
    // рассчет на тактирование от кварца 8 мГц, на максимальную частоту в 72 мГц
    // AHB, APB1, APB2 36 (разрешенный максимум)
    // APB2 36 мГц (для таймеров 72), на АЦП забили, не используем.
    uint32_t cfgr = (RCC_CFGR_USBPRE_PLL_CLK_DIV1_5 << 22)                  \
                  | (RCC_CFGR_PLLMUL_PLL_CLK_MUL9 << RCC_CFGR_PLLMUL_SHIFT) \
                  | (RCC_CFGR_PLLXTPRE_HSE_CLK << 17)                       \
                  | (RCC_CFGR_PLLSRC_HSE_CLK << 16)                         \
                  | (RCC_CFGR_PPRE2_HCLK_NODIV << RCC_CFGR_PPRE2_SHIFT)     \
                  | (RCC_CFGR_PPRE1_HCLK_NODIV << RCC_CFGR_PPRE1_SHIFT)     \
                  | (RCC_CFGR_HPRE_SYSCLK_DIV2 << RCC_CFGR_HPRE_SHIFT);
    RCC_CFGR = cfgr;
    // что то с памятью, копипаста с функций stmhal
    FLASH_ACR |= (uint32_t)FLASH_ACR_PRFTBE;
    FLASH_ACR &= ((uint32_t)~FLASH_ACR_LATENCY_MASK);
    FLASH_ACR |= (uint32_t)FLASH_ACR_LATENCY_2WS;
    // передергиваем PLL, что бы точно все включилось
    timeout = 9e6;
    if ( (RCC_CFGR & RCC_CFGR_SWS) == (RCC_CFGR_SWS_SYSCLKSEL_PLLCLK << RCC_CFGR_SWS_SHIFT) )
    {
        RCC_CFGR &= ~((uint32_t)RCC_CFGR_SW);
        while ( ((RCC_CFGR & RCC_CFGR_SWS) != (RCC_CFGR_SWS_SYSCLKSEL_HSICLK << RCC_CFGR_SWS_SHIFT) ) && \
                (--timeout > 1) );
    }
    RCC_CR &= ~(uint32_t)(RCC_CR_PLLON);
    timeout = 9e6;
    while( ((RCC_CR & RCC_CR_PLLRDY) != 0) && (--timeout > 1) );
    RCC_CR |= (uint32_t)RCC_CR_PLLON;
    timeout = 9e6;
    while( ((RCC_CR & RCC_CR_PLLRDY) == 0) && (--timeout > 1) );

    // включаем sysclk, ждем
    RCC_CFGR |= (uint32_t)(RCC_CFGR_SW_SYSCLKSEL_PLLCLK << RCC_CFGR_SW_SHIFT);
    timeout = 9e6;
    while( ((RCC_CFGR & RCC_CFGR_SWS) != (RCC_CFGR_SWS_SYSCLKSEL_PLLCLK << RCC_CFGR_SWS_SHIFT)) && (--timeout > 1) );
}

void suspSysClk()
{
    // off everything, only internal RC generator will work
    RCC_CR = RCC_CR_HSION;
}

void delay_s(uint16_t s)
{
    uint16_t cnt = s*20;
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
