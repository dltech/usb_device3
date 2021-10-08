#include "rcc.h"
#include "inttypes.h"

enum{
    ETHMACRX,
    ETHMACTX,
    ETHMAC,
    OTGFS,
    CRC,
    FLITF,
    SRAM,
    DMA2,
    DMA1,
    USART1,
    SPI1,
    TIM1,
    ADC2,
    ADC1,
    IOPE,
    IOPD,
    IOPC,
    IOPB,
    IOPA,
    AFIO,
    DAC,
    PWR,
    BKP,
    CAN2,
    CAN1,
    I2C2,
    I2C1,
    UART5,
    UART4,
    UART3,
    UART2,
    SPI3,
    SPI2,
    WWDG,
    TIM7,
    TIM6,
    TIM5,
    TIM4,
    TIM2
} periphClock;

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
    uint32_t cfgr = PLLMUL9 | PLLSRC | PPRE2_HCLK_NODIV | \
                    PPRE1_HCLK_DIV2 | HPRE_SYSCLK_NODIV;
    RCC_CFGR = cfgr;
    // что то с памятью, копипаста с функций stmhal
    FLASH_ACR = PRFTBE | LATENCY_72M;
    // передергиваем PLL, что бы точно все включилось
    timeout = 9e6;
    if ( (RCC_CFGR & SWS_MASK) == SWS_PLL )
    {
        RCC_CFGR &= ~((uint32_t)SW_MASK);
        while ( ((RCC_CFGR & SWS_MASK) != SWS_HSI) && (--timeout > 1) );
    }
    RCC_CR &= ~((uint32_t)PLLON);
    timeout = 9e6;
    while( ((RCC_CR & PLLRDY) != 0) && (--timeout > 1) );
    RCC_CR |= PLLON;
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

/*
void enablePeriphClock(uint16_t periph)
{
    switch (periph) {
        case ETHMACRX:
            RCC_AHBENR |= ETHMACRXEN;
            break;
        case ETHMACTX:
            RCC_AHBENR |= ETHMACTXEN;
            break;
        case ETHMAC:
            RCC_AHBENR |= ETHMACEN;
            break;
        case OTGFS:
            RCC_AHBENR |= OTGFSEN;
            break;
        case CRC:
            RCC_AHBENR |= CRCEN;
            break;
        case FLITF:
            RCC_AHBENR |= FLITFEN;
            break;
        case SRAM:
            RCC_AHBENR |= SRAMEN;
            break;
        case DMA2:
            RCC_AHBENR |= DMA2EN;
            break;
        case DMA1:
            RCC_AHBENR |= DMA1EN;
            break;
        case USART1:
            RCC_APB2ENR |= USART1EN;
            break;
        case SPI1:
            RCC_APB2ENR |= SPI1EN;
            break;
        case TIM1:
            RCC_APB2ENR |= TIM1EN;
            break;
        case ADC2:
            RCC_APB2ENR |= ADC2EN;
            break;
        case ADC1:
            RCC_APB2ENR |= ADC1EN;
            break;
        case IOPE:
            RCC_APB2ENR |= IOPEEN;
            break;
        case IOPD:
            RCC_APB2ENR |= IOPDEN;
            break;
        case IOPC:
            RCC_APB2ENR |= IOPCEN;
            break;
        case IOPB:
            RCC_APB2ENR |= IOPBEN;
            break;
        case IOPA:
            RCC_APB2ENR |= IOPAEN;
            break;
        case AFIO:
            RCC_APB2ENR |= AFIOEN;
            break;
        case DAC:
            RCC_APB1ENR |= DACEN;
            break;
        case PWR:
            RCC_APB1ENR |= PWREN;
            break;
        case BKP:
            RCC_APB1ENR |= BKPEN;
            break;
        case CAN2:
            RCC_APB1ENR |= CAN2;
            break;
        case CAN1:
            RCC_APB1ENR |= CAN1;
            break;
        case I2C2:
            RCC_APB1ENR |= I2C2EN;
            break;
        case I2C1:
            RCC_APB1ENR |= I2C1EN;
            break;
        case UART5:
            RCC_APB1ENR |= UART5EN;
            break;
        case UART4:
            RCC_APB1ENR |= UART4EN;
            break;
        case UART3:
            RCC_APB1ENR |= UART3EN;
            break;
        case UART2:
            RCC_APB1ENR |= UART2EN;
            break;
        case SPI3:
            RCC_APB1ENR |= SPI3EN;
            break;
        case SPI2:
            RCC_APB1ENR |= SPI2EN;
            break;
        case WWDG:
            RCC_APB1ENR |= WWDGEN;
            break;
        case TIM7:
            RCC_APB1ENR |= TIM7EN;
            break;
        case TIM6:
            RCC_APB1ENR |= TIM6EN;
            break;
        case TIM5:
            RCC_APB1ENR |= TIM5EN;
            break;
        case TIM4:
            RCC_APB1ENR |= TIM4EN;
            break;
        case TIM3:
            RCC_APB1ENR |= TIM3EN;
            break;
        case TIM2:
            RCC_APB1ENR |= TIM2EN;
            break;
        case TIM1:
            RCC_APB1ENR |= TIM1EN;
            break;
    }
}

void resetPeriphClock(uint16_t periph)
{
    switch (periph) {
        case ETHMAC:
            RCC_AHBRSTR |= ETHMACRST;
            break;
        case OTGFS:
            RCC_AHBRSTR |= OTGFSRST;
            break;
        case USART1:
            RCC_APB2RSTR |= USART1RST;
            break;
        case SPI1:
            RCC_APB2RSTR |= SPI1RST;
            break;
        case TIM1:
            RCC_APB2RSTR |= TIM1RST;
            break;
        case ADC2:
            RCC_APB2RSTR |= ADC2RST;
            break;
        case ADC1:
            RCC_APB2RSTR |= ADC1RST;
            break;
        case IOPE:
            RCC_APB2RSTR |= IOPERST;
            break;
        case IOPD:
            RCC_APB2RSTR |= IOPDRST;
            break;
        case IOPC:
            RCC_APB2RSTR |= IOPCRST;
            break;
        case IOPB:
            RCC_APB2RSTR |= IOPBRST;
            break;
        case IOPA:
            RCC_APB2RSTR |= IOPARST;
            break;
        case AFIO:
            RCC_APB2RSTR |= AFIORST;
            break;
        case DAC:
            RCC_APB1RSTR |= DACRST;
            break;
        case PWR:
            RCC_APB1RSTR |= PWRRST;
            break;
        case BKP:
            RCC_APB1RSTR |= BKPRST;
            break;
        case CAN2:
            RCC_APB1RSTR |= CAN2;
            break;
        case CAN1:
            RCC_APB1RSTR |= CAN1;
            break;
        case I2C2:
            RCC_APB1RSTR |= I2C2RST;
            break;
        case I2C1:
            RCC_APB1RSTR |= I2C1RST;
            break;
        case UART5:
            RCC_APB1RSTR |= UART5RST;
            break;
        case UART4:
            RCC_APB1RSTR |= UART4RST;
            break;
        case UART3:
            RCC_APB1RSTR |= UART3RST;
            break;
        case UART2:
            RCC_APB1RSTR |= UART2RST;
            break;
        case SPI3:
            RCC_APB1RSTR |= SPI3RST;
            break;
        case SPI2:
            RCC_APB1RSTR |= SPI2RST;
            break;
        case WWDG:
            RCC_APB1RSTR |= WWDGRST;
            break;
        case TIM7:
            RCC_APB1RSTR |= TIM7RST;
            break;
        case TIM6:
            RCC_APB1RSTR |= TIM6RST;
            break;
        case TIM5:
            RCC_APB1RSTR |= TIM5RST;
            break;
        case TIM4:
            RCC_APB1RSTR |= TIM4RST;
            break;
        case TIM3:
            RCC_APB1RSTR |= TIM3RST;
            break;
        case TIM2:
            RCC_APB1RSTR |= TIM2RST;
            break;
        case TIM1:
            RCC_APB1RSTR |= TIM1RST;
            break;
    }
}
*/
