#ifndef H_RCC_REGS
#define H_RCC_REGS
/*
 * Part of Belkin STM32 HAL, rcc registers of STMF103 MCU.
 *
 * Copyright 2021 Mikhail Belkin <dltech174@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "memorymap.h"

/* Clock control register */
#define RCC_CR          MMIO32(RCC_BASE + 0x00)
// PLL clock ready flag
#define PLLRDY  0x02000000
// PLL enable
#define PLLON   0x01000000
// Clock security system enable
#define CSSON   0x00080000
// External high-speed clock bypass
#define HSEBYP  0x00040000
// External high-speed clock ready flag
#define HSERDY  0x00020000
// HSE clock enable
#define HSEON   0x00010000
// Internal high-speed clock calibration
#define HSICAL_OFFS     8
// Internal high-speed clock trimming
#define HSITRIM_OFFS    3
// Internal high-speed clock ready flag
#define HSIRDY  0x00000002
// Internal high-speed clock enable
#define HSION   0x00000001

/* Clock configuration register */
#define RCC_CFGR        MMIO32(RCC_BASE + 0x04)
// Microcontroller clock output
#define MCO_NOCLK           0x00000000
#define MCO_SYSCLK          0x04000000
#define MCO_HSI             0x05000000
#define MCO_HSE             0x06000000
#define MCO_PLL_DIV2        0x07000000
// USB prescaler
#define USBPRE              0x00400000
// PLL multiplication factor
#define PLLMUL16            0x003c0000
//#define PLLMUL16            0x00380000
#define PLLMUL15            0x00340000
#define PLLMUL14            0x00300000
#define PLLMUL13            0x002c0000
#define PLLMUL12            0x00280000
#define PLLMUL11            0x00240000
#define PLLMUL10            0x00200000
#define PLLMUL9             0x001c0000
#define PLLMUL8             0x00180000
#define PLLMUL7             0x00140000
#define PLLMUL6             0x00100000
#define PLLMUL5             0x000c0000
#define PLLMUL4             0x00080000
#define PLLMUL3             0x00040000
#define PLLMUL2             0x00000000
// HSE divider for PLL entry
#define PLLXTPRE            0x00020000
// PLL entry clock source
#define PLLSRC              0x00010000
// ADC prescaler
#define ADCPRE_PCLK2_DIV8   0x0000c000
#define ADCPRE_PCLK2_DIV6   0x00008000
#define ADCPRE_PCLK2_DIV4   0x00004000
#define ADCPRE_PCLK2_DIV2   0x00000000
// APB high-speed prescaler (APB2)
#define PPRE2_HCLK_DIV16    0x00003800
#define PPRE2_HCLK_DIV8     0x00003000
#define PPRE2_HCLK_DIV4     0x00002800
#define PPRE2_HCLK_DIV2     0x00002000
#define PPRE2_HCLK_NODIV    0x00000000
// APB low-speed prescaler (APB1)
#define PPRE1_HCLK_DIV16    0x00000700
#define PPRE1_HCLK_DIV8     0x00000600
#define PPRE1_HCLK_DIV4     0x00000500
#define PPRE1_HCLK_DIV2     0x00000400
#define PPRE1_HCLK_NODIV    0x00000000
// AHB prescaler
#define HPRE_SYSCLK_DIV512  0x000000f0
#define HPRE_SYSCLK_DIV256  0x000000e0
#define HPRE_SYSCLK_DIV128  0x000000d0
#define HPRE_SYSCLK_DIV64   0x000000c0
#define HPRE_SYSCLK_DIV16   0x000000b0
#define HPRE_SYSCLK_DIV8    0x000000a0
#define HPRE_SYSCLK_DIV4    0x00000090
#define HPRE_SYSCLK_DIV2    0x00000080
#define HPRE_SYSCLK_NODIV   0x00000000
// System clock switch status
#define SWS_MASK            0x0000000c
#define SWS_HSI             0x00000000
#define SWS_HSE             0x00000004
#define SWS_PLL             0x00000008
// System clock switch
#define SW_MASK             0x00000003
#define SW_HSI              0x00000000
#define SW_HSE              0x00000001
#define SW_PLL              0x00000002

/* Clock interrupt register */
#define RCC_CIR         MMIO32(RCC_BASE + 0x08)
// Clock security system interrupt clear
#define CSSC        0x00800000
// PLL ready interrupt clear
#define PLLRDYC     0x00100000
// HSE ready interrupt clear
#define HSERDYC     0x00080000
// HSI ready interrupt clear
#define HSIRDYC     0x00040000
// LSE ready interrupt clear
#define LSERDYC     0x00020000
// LSI ready interrupt clear
#define LSIRDYC     0x00010000
// PLL ready interrupt enable
#define PLLRDYIE    0x00001000
// HSE ready interrupt enable
#define HSERDYIE    0x00000800
// HSI ready interrupt enable
#define HSIRDYIE    0x00000400
// LSE ready interrupt enable
#define LSERDYIE    0x00000200
// LSI ready interrupt enable
#define LSIRDYIE    0x00000100
// Clock security system interrupt flag
#define CSSF        0x00000080
// PLL ready interrupt flag
#define PLLRDYF     0x00000010
// HSE ready interrupt flag
#define HSERDYF     0x00000008
// HSI ready interrupt flag
#define HSIRDYF     0x00000004
// LSE ready interrupt flag
#define LSERDYF     0x00000002
// LSI ready interrupt flag
#define LSIRDYF     0x00000001

/* APB2 Peripherial reset register */
#define RCC_APB2RSTR    MMIO32(RCC_BASE + 0x0c)
#define TIM11RST     0x00200000
#define TIM10RST     0x00100000
#define TIM9RST      0x00080000
#define ADC3RST      0x00008000
#define USART1RST    0x00004000
#define TIM8RST      0x00002000
#define SPI1RST      0x00001000
#define TIM1RST      0x00000800
#define ADC2RST      0x00000400
#define ADC1RST      0x00000200
#define IOPGRST      0x00000100
#define IOPFRST      0x00000080
#define IOPERST      0x00000040
#define IOPDRST      0x00000020
#define IOPCRST      0x00000010
#define IOPBRST      0x00000008
#define IOPARST      0x00000004
#define AFIORST      0x00000001

/* APB1 Peripherial reset register */
#define RCC_APB1RSTR    MMIO32(RCC_BASE + 0x10)
#define DACRST       0x20000000
#define PWRRST       0x10000000
#define BKPRST       0x08000000
#define CANRST       0x02000000
#define USBRST       0x00800000
#define I2C2RST      0x00400000
#define I2C1RST      0x00200000
#define UART5RST     0x00100000
#define UART4RST     0x00080000
#define UART3RST     0x00040000
#define UART2RST     0x00020000
#define SPI3RST      0x00008000
#define SPI2RST      0x00004000
#define WWDGRST      0x00000800
#define TIM14RST     0x00000100
#define TIM13RST     0x00000080
#define TIM12RST     0x00000040
#define TIM7RST      0x00000020
#define TIM6RST      0x00000010
#define TIM5RST      0x00000008
#define TIM4RST      0x00000004
#define TIM3RST      0x00000002
#define TIM2RST      0x00000001

/* AHB Peripheral Clock enable register */
#define RCC_AHBENR      MMIO32(RCC_BASE + 0x14)
#define SDIOEN    0x0400
#define FSMCEN    0x0100
#define CRCEN     0x0040
#define FLITFEN   0x0010
#define SRAMEN    0x0004
#define DMA2EN    0x0002
#define DMA1EN    0x0001

/* APB2 peripheral clock enable register */
#define RCC_APB2ENR     MMIO32(RCC_BASE + 0x18)
#define TIM11EN     0x00200000
#define TIM10EN     0x00100000
#define TIM9EN      0x00080000
#define ADC3EN      0x00008000
#define USART1EN    0x00004000
#define TIM8EN      0x00002000
#define SPI1EN      0x00001000
#define TIM1EN      0x00000800
#define ADC2EN      0x00000400
#define ADC1EN      0x00000200
#define IOPGEN      0x00000100
#define IOPFEN      0x00000080
#define IOPEEN      0x00000040
#define IOPDEN      0x00000020
#define IOPCEN      0x00000010
#define IOPBEN      0x00000008
#define IOPAEN      0x00000004
#define AFIOEN      0x00000001

/* APB1 peripheral clock enable register */
#define RCC_APB1ENR     MMIO32(RCC_BASE + 0x1c)
#define DACEN       0x20000000
#define PWREN       0x10000000
#define BKPEN       0x08000000
#define CANEN       0x02000000
#define USBEN       0x00800000
#define I2C2EN      0x00400000
#define I2C1EN      0x00200000
#define UART5EN     0x00100000
#define UART4EN     0x00080000
#define UART3EN     0x00040000
#define UART2EN     0x00020000
#define SPI3EN      0x00008000
#define SPI2EN      0x00004000
#define WWDGEN      0x00000800
#define TIM14EN     0x00000100
#define TIM13EN     0x00000080
#define TIM12EN     0x00000040
#define TIM7EN      0x00000020
#define TIM6EN      0x00000010
#define TIM5EN      0x00000008
#define TIM4EN      0x00000004
#define TIM3EN      0x00000002
#define TIM2EN      0x00000001

/* Backup domain control register */
#define RCC_BCDR        MMIO32(RCC_BASE + 0x20)
// Backup domain software reset
#define BDRST           0x00010000
// RTC clock enable
#define RTCEN           0x00008000
// RTC clock source selection
#define RTCSEL_NOCLK    0x00000000
#define RTCSEL_LSE      0x00000100
#define RTCSEL_LSI      0x00000200
#define RTCSEL_HSE      0x00000300
// External low-speed oscillator bypass
#define LSEBYP          0x00000004
// External low-speed oscillator ready
#define LSERDY          0x00000002
// External low-speed oscillator enable
#define LSEON           0x00000001

/* Control/status register */
#define RCC_CSR         MMIO32(RCC_BASE + 0x24)
// Low-power reset flag
#define LPWRRSTF    0x80000000
// Window watchdog reset flag
#define WWDGRSTF    0x40000000
// Independent watchdog reset flag
#define IWDGRSTF    0x20000000
// Software reset flag
#define SFTRSTF     0x10000000
// POR/PDR reset flag
#define PORRSTF     0x08000000
// PIN reset flag
#define PINRSTF     0x04000000
// Remove reset flag
#define RMVF        0x01000000
// Internal low-speed oscillator ready
#define LSIRDY      0x00000002
// Internal low-speed oscillator enable
#define LSION       0x00000001

#endif
