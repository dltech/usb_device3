#include "mysys.h"
#include "rcc.h"

void sysClk()
{
    // включаем кварц, ждем пока прогреется
    RCC_CR |= HSEON;
    uint32_t timeout = 1e8;
    while ( ((RCC_CR & HSERDY) == 0) && (--timeout > 1) );
    // рассчет на тактирование от кварца 8 мГц, на максимальную частоту в 72 мГц
    // тактирование USB настроено нормально
    // AHB 72, APB1 36, APB2 72 (разрешенный максимум)
    // на АЦП забили, не используем.
    uint32_t cfgr = OTGFSPRE | PLLMUL9 | PLLSRC | PPRE2_HCLK_NODIV | \
                    PPRE1_HCLK_DIV2 | HPRE_SYSCLK_NODIV;
    RCC_CFGR = cfgr;
    // что то с памятью, копипаста с функций stmhal
    FLASH_ACR |= (uint32_t)FLASH_ACR_PRFTBE;
    FLASH_ACR &= ((uint32_t)~FLASH_ACR_LATENCY_MASK);
    FLASH_ACR |= (uint32_t)FLASH_ACR_LATENCY_2WS;
    // передергиваем PLL, что бы точно все включилось
    timeout = 9e6;
    if ( (RCC_CFGR & SWS_MASK) == SWS_PLLCLK )
    {
        RCC_CFGR &= ~(SW_MASK);
        while ( ((RCC_CFGR & SWS_MASK) != SWS_HSI) && (--timeout > 1) );
    }
    RCC_CR &= ~(PLLON);
    timeout = 9e6;
    while( ((RCC_CR & PLLRDY) != 0) && (--timeout > 1) );
    RCC_CR |= (uint32_t)PLLON;
    timeout = 9e6;
    while( ((RCC_CR & PLLRDY) == 0) && (--timeout > 1) );

    // включаем sysclk, ждем
    RCC_CFGR |= SW_PLL;
    timeout = 9e6;
    while( ((RCC_CFGR & SWS_MASK) != SWS_PLL) && (--timeout > 1) );
}

void suspSysClk()
{
    // off everything, only internal RC generator will work
    RCC_CR = HSION;
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
