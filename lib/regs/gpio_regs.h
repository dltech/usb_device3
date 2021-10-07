#ifndef H_GPIO_REGS
#define H_GPIO_REGS
/*
 * Part of Belkin STM32 HAL, gpio registers of STMF103 MCU.
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

/* Port configuration register low */
#define GPIOA_CRL   MMIO32(GPIOA_BASE + 0x00)
#define GPIOB_CRL   MMIO32(GPIOB_BASE + 0x00)
#define GPIOC_CRL   MMIO32(GPIOC_BASE + 0x00)
#define GPIOD_CRL   MMIO32(GPIOD_BASE + 0x00)
#define GPIOE_CRL   MMIO32(GPIOE_BASE + 0x00)
/* Port configuration register high */
#define GPIOA_CRH   MMIO32(GPIOA_BASE + 0x04)
#define GPIOB_CRH   MMIO32(GPIOB_BASE + 0x04)
#define GPIOC_CRH   MMIO32(GPIOC_BASE + 0x04)
#define GPIOD_CRH   MMIO32(GPIOD_BASE + 0x04)
#define GPIOE_CRH   MMIO32(GPIOE_BASE + 0x04)
// port x configuration in input mode
#define CNF_ANALOG(n)    0x00000000
#define CNF_FLOATING(n)  ((uint32_t)(0x4 << (n*4)))
#define CNF_PUPD(n)      ((uint32_t)(0x8 << (n*4)))
#define CNF0_ANALOG      0x00000000
#define CNF0_FLOATING    0x00000004
#define CNF0_PUPD        0x00000008
#define CNF1_ANALOG      0x00000000
#define CNF1_FLOATING    0x00000040
#define CNF1_PUPD        0x00000080
#define CNF2_ANALOG      0x00000000
#define CNF2_FLOATING    0x00000400
#define CNF2_PUPD        0x00000800
#define CNF3_ANALOG      0x00000000
#define CNF3_FLOATING    0x00004000
#define CNF3_PUPD        0x00008000
#define CNF4_ANALOG      0x00000000
#define CNF4_FLOATING    0x00040000
#define CNF4_PUPD        0x00080000
#define CNF5_ANALOG      0x00000000
#define CNF5_FLOATING    0x00400000
#define CNF5_PUPD        0x00800000
#define CNF6_ANALOG      0x00000000
#define CNF6_FLOATING    0x04000000
#define CNF6_PUPD        0x08000000
#define CNF7_ANALOG      0x00000000
#define CNF7_FLOATING    0x40000000
#define CNF7_PUPD        0x80000000
// port x configuration in output mode
#define CNF_PUSH_PULL(n)     0x00000000
#define CNF_OPEN_DRAIN(n)    ((uint32_t)(0x4 << (n*4)))
#define CNF_AF_PUSH_PULL(n)  ((uint32_t)(0x8 << (n*4)))
#define CNF_AF_OPEN_DRAIN(n) ((uint32_t)(0xc << (n*4)))
#define CNF0_PUSH_PULL       0x00000000
#define CNF0_OPEN_DRAIN      0x00000004
#define CNF0_AF_PUSH_PULL    0x00000008
#define CNF0_AF_OPEN_DRAIN   0x0000000c
#define CNF1_PUSH_PULL       0x00000000
#define CNF1_OPEN_DRAIN      0x00000040
#define CNF1_AF_PUSH_PULL    0x00000080
#define CNF1_AF_OPEN_DRAIN   0x000000c0
#define CNF2_PUSH_PULL       0x00000000
#define CNF2_OPEN_DRAIN      0x00000400
#define CNF2_AF_PUSH_PULL    0x00000800
#define CNF2_AF_OPEN_DRAIN   0x00000c00
#define CNF3_PUSH_PULL       0x00000000
#define CNF3_OPEN_DRAIN      0x00004000
#define CNF3_AF_PUSH_PULL    0x00008000
#define CNF3_AF_OPEN_DRAIN   0x0000c000
#define CNF4_PUSH_PULL       0x00000000
#define CNF4_OPEN_DRAIN      0x00040000
#define CNF4_AF_PUSH_PULL    0x00080000
#define CNF4_AF_OPEN_DRAIN   0x000c0000
#define CNF5_PUSH_PULL       0x00000000
#define CNF5_OPEN_DRAIN      0x00400000
#define CNF5_AF_PUSH_PULL    0x00800000
#define CNF5_AF_OPEN_DRAIN   0x00c00000
#define CNF6_PUSH_PULL       0x00000000
#define CNF6_OPEN_DRAIN      0x04000000
#define CNF6_AF_PUSH_PULL    0x08000000
#define CNF6_AF_OPEN_DRAIN   0x0c000000
#define CNF7_PUSH_PULL       0x00000000
#define CNF7_OPEN_DRAIN      0x40000000
#define CNF7_AF_PUSH_PULL    0x80000000
#define CNF7_AF_OPEN_DRAIN   0xc0000000
// Port mode bits
#define MODE_INPUT(n)    0x00000000
#define MODE_OUTPUT10(n) ((uint32_t)(0x1 << (n*4)))
#define MODE_OUTPUT2(n)  ((uint32_t)(0x2 << (n*4)))
#define MODE_OUTPUT50(n) ((uint32_t)(0x3 << (n*4)))
#define MODE0_INPUT       0x00000000
#define MODE0_OUTPUT10    0x00000001
#define MODE0_OUTPUT2     0x00000002
#define MODE0_OUTPUT50    0x00000003
#define MODE1_INPUT       0x00000000
#define MODE1_OUTPUT10    0x00000010
#define MODE1_OUTPUT2     0x00000020
#define MODE1_OUTPUT50    0x00000030
#define MODE2_INPUT       0x00000000
#define MODE2_OUTPUT10    0x00000100
#define MODE2_OUTPUT2     0x00000200
#define MODE2_OUTPUT50    0x00000300
#define MODE3_INPUT       0x00000000
#define MODE3_OUTPUT10    0x00001000
#define MODE3_OUTPUT2     0x00002000
#define MODE3_OUTPUT50    0x00003000
#define MODE4_INPUT       0x00000000
#define MODE4_OUTPUT10    0x00010000
#define MODE4_OUTPUT2     0x00020000
#define MODE4_OUTPUT50    0x00030000
#define MODE5_INPUT       0x00000000
#define MODE5_OUTPUT10    0x00100000
#define MODE5_OUTPUT2     0x00200000
#define MODE5_OUTPUT50    0x00300000
#define MODE6_INPUT       0x00000000
#define MODE6_OUTPUT10    0x01000000
#define MODE6_OUTPUT2     0x02000000
#define MODE6_OUTPUT50    0x03000000
#define MODE7_INPUT       0x00000000
#define MODE7_OUTPUT10    0x10000000
#define MODE7_OUTPUT2     0x20000000
#define MODE7_OUTPUT50    0x30000000

/* Port input data register */
#define GPIOA_IDR   MMIO32(GPIOA_BASE + 0x08)
#define GPIOB_IDR   MMIO32(GPIOB_BASE + 0x08)
#define GPIOC_IDR   MMIO32(GPIOC_BASE + 0x08)
#define GPIOD_IDR   MMIO32(GPIOD_BASE + 0x08)
#define GPIOE_IDR   MMIO32(GPIOE_BASE + 0x08)
// pin bit definitions, they are the same for IDR, ODR, BSRR, BRR, LCKR regs
#define GPIO0   0x0001
#define GPIO1   0x0002
#define GPIO2   0x0004
#define GPIO3   0x0008
#define GPIO4   0x0010
#define GPIO5   0x0020
#define GPIO6   0x0040
#define GPIO7   0x0080
#define GPIO8   0x0100
#define GPIO9   0x0200
#define GPIO10  0x0400
#define GPIO11  0x0800
#define GPIO12  0x1000
#define GPIO13  0x2000
#define GPIO14  0x4000
#define GPIO15  0x8000
// IDR Port input data
#define IDR(n)  (1 << n)

/* Port output data register */
#define GPIOA_ODR   MMIO32(GPIOA_BASE + 0x0c)
#define GPIOB_ODR   MMIO32(GPIOB_BASE + 0x0c)
#define GPIOC_ODR   MMIO32(GPIOC_BASE + 0x0c)
#define GPIOD_ODR   MMIO32(GPIOD_BASE + 0x0c)
#define GPIOE_ODR   MMIO32(GPIOE_BASE + 0x0c)
// ODR Port output data
#define ODR(n)  (1 << n)

/* Port bit set/reset register */
#define GPIOA_BSRR  MMIO32(GPIOA_BASE + 0x10)
#define GPIOB_BSRR  MMIO32(GPIOB_BASE + 0x10)
#define GPIOC_BSRR  MMIO32(GPIOC_BASE + 0x10)
#define GPIOD_BSRR  MMIO32(GPIOD_BASE + 0x10)
#define GPIOE_BSRR  MMIO32(GPIOE_BASE + 0x10)
// Port reset bit
#define BR(n)   ((uint32_t)(1 << n+16))
// Port set bit
#define BS(n)   ((uint32_t)(1 << n))

/* Port bit reset register */
#define GPIOA_BRR   MMIO32(GPIOA_BASE + 0x14)
#define GPIOB_BRR   MMIO32(GPIOB_BASE + 0x14)
#define GPIOC_BRR   MMIO32(GPIOC_BASE + 0x14)
#define GPIOD_BRR   MMIO32(GPIOD_BASE + 0x14)
#define GPIOE_BRR   MMIO32(GPIOE_BASE + 0x14)

/* Port configuration lock register */
#define GPIOA_LCKR  MMIO32(GPIOA_BASE + 0x18)
#define GPIOB_LCKR  MMIO32(GPIOB_BASE + 0x18)
#define GPIOC_LCKR  MMIO32(GPIOC_BASE + 0x18)
#define GPIOD_LCKR  MMIO32(GPIOD_BASE + 0x18)
#define GPIOE_LCKR  MMIO32(GPIOE_BASE + 0x18)
// Lock key
#define LCKK    0x00010000
// Port lock bit
#define LCK_GPIO(n)   ((uint32_t)(1 << n))

/* Event control register */
#define AFIO_EVCR    MMIO32(AFIO_BASE + 0x00)
// event output enable
#define EVOE        0x80
// Port selection
#define EV_PORTE    0x40
#define EV_PORTD    0x30
#define EV_PORTC    0x20
#define EV_PORTB    0x10
#define EV_PORTA    0x00
// Pin selection
#define EV_PIN15    0x0f
#define EV_PIN14    0x0e
#define EV_PIN13    0x0d
#define EV_PIN12    0x0c
#define EV_PIN11    0x0b
#define EV_PIN10    0x0a
#define EV_PIN9     0x09
#define EV_PIN8     0x08
#define EV_PIN7     0x07
#define EV_PIN6     0x06
#define EV_PIN5     0x05
#define EV_PIN4     0x04
#define EV_PIN3     0x03
#define EV_PIN2     0x02
#define EV_PIN1     0x01
#define EV_PIN0     0x00

/* AF remap and debug I/O configuration register */
#define AFIO_MAPR    MMIO32(AFIO_BASE + 0x04)
// Serial wire JTAG configuration
#define SWJ_FULL                                0x00000000
#define SWJ_FULL_NJRST_DIS                      0x01000000
#define SWJ_JTAG_DP_DIS_SWD_DP_EN               0x02000000
#define SWJ_JTAG_DP_DIS_SWD_DP_DIS              0x04000000
#define ADC2_ETRGREG_REMAP                      0x00100000
#define ADC2_ETRGINJ_REMAP                      0x00080000
#define ADC1_ETRGREG_REMAP                      0x00040000
#define ADC1_ETRGINJ_REMAP                      0x00020000
#define TIM5CH4_IREMAP                          0x00010000
#define PD01_REMAP                              0x00008000
// CAN alternate function remapping
#define CAN_REMAP_CAN_RX_PA11_CAN_TX_PA12       0x00000000
#define CAN_REMAP_CAN_RX_PB8_CAN_TX_PB9         0x00004000
#define CAN_REMAP_CAN_RX_PD0_CAN_TX_PD1         0x00006000
#define TIM4_REMAP                              0x00001000
// TIM3 remapping
#define TIM3_CH1_PA6_CH2_PA7_CH3_PB0_CH4_PB1    0x00000000
#define TIM3_CH1_PB4_CH2_PB5_CH3_PB0_CH4_PB1    0x00000800
#define TIM3_CH1_PC6_CH2_PC7_CH3_PC8_CH4_PC9    0x00000c00
// TIM2 remapping
#define TIM2_CH1_PA0_CH2_PA1_CH3_PA2_CH4_PA3    0x00000000
#define TIM2_CH1_PB15_CH2_PB3_CH3_PB10_CH4_PB11 0x00000100
#define TIM2_CH1_PA0_CH2_PA1_CH3_PB10_CH4_PB11  0x00000200
#define TIM2_CH1_PA15_CH2_PB3_CH3_PB10_CH4_PB11 0x00000300
// TIM1 remapping
#define TIM1_NO_REMAP                           0x00000000
#define TIM1_PARTIAL_REMAP                      0x00000040
#define TIM1_FULL_REMAP                         0x000000c0
// USART3 remapping
#define USART3_TX_PB10_RX_PB11_CK_PB12_CTS_PB13_RTS_PB14    0x00000000
#define USART3_TX_PC10_RX_PC11_CK_PC12_CTS_PB13_RTS_PB14    0x00000010
#define USART3_TX_PD8_RX_PD9_CK_PD10_CTS_PD11_RTS_PD12      0x00000030
#define USART2_REMAP                            0x00000008
#define USART1_REMAP                            0x00000004
#define I2C1_REMAP                              0x00000002
#define SPI1_REMAP                              0x00000001

/* External interrupt configuration register 1 */
#define AFIO_EXTICR1 MMIO32(AFIO_BASE + 0x08)
#define EXTI_PA(n)  ((uint32_t)(0x0 << (n*4)))
#define EXTI_PB(n)  ((uint32_t)(0x1 << (n*4)))
#define EXTI_PC(n)  ((uint32_t)(0x2 << (n*4)))
#define EXTI_PD(n)  ((uint32_t)(0x3 << (n*4)))
#define EXTI_PE(n)  ((uint32_t)(0x4 << (n*4)))
#define EXTI_PF(n)  ((uint32_t)(0x5 << (n*4)))
#define EXTI_PG(n)  ((uint32_t)(0x6 << (n*4)))
/* External interrupt configuration register 2 */
#define AFIO_EXTICR2 MMIO32(AFIO_BASE + 0x0c)
/* External interrupt configuration register 3 */
#define AFIO_EXTICR3 MMIO32(AFIO_BASE + 0x10)
/* External interrupt configuration register 4 */
#define AFIO_EXTICR4 MMIO32(AFIO_BASE + 0x14)

/* AF remap and debug I/O configuration register2 */
#define AFIO_MAPR2   MMIO32(AFIO_BASE + 0x1c)
#define FSMC_NADV   0x0400
#define TIM14_REMAP 0x0200
#define TIM13_REMAP 0x0100
#define TIM11_REMAP 0x0080
#define TIM10_REMAP 0x0040
#define TIM9_REMAP  0x0020

#endif
