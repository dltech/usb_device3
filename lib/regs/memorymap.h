#ifndef H_MEMORYMAP
#define H_MEMORYMAP
/*
 * Part of Belkin STM32 HAL, memorymap, base addresses, access macro.
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

// Register boundary addresses
#define FMSC_BASE       0xa0000000
#define USB_OTG_FS_BASE 0x50000000
#define ETHERNET_BASE   0x40028000
#define CRC_BASE        0x40023000
#define RCC_BASE        0x40021000
#define DMA2_BASE       0x40020400
#define DMA1_BASE       0x40020000
#define SDIO_BASE       0x40018000
#define TIM11_BASE      0x40015400
#define TIM10_BASE      0x40015000
#define TIM9_BASE       0x40014c00
#define ADC3_BASE       0x40013c00
#define USART1_BASE     0x40013800
#define TIM8_BASE       0x40013400
#define SPI1_BASE       0x40013000
#define TIM1_BASE       0x40012c00
#define ADC2_BASE       0x40012800
#define ADC1_BASE       0x40012400
#define GPIOG_BASE      0x40012000
#define GPIOF_BASE      0x40011c00
#define GPIOE_BASE      0x40011800
#define GPIOD_BASE      0x40011400
#define GPIOC_BASE      0x40011000
#define GPIOB_BASE      0x40010c00
#define GPIOA_BASE      0x40010800
#define EXTI_BASE       0x40010400
#define AFIO_BASE       0x40010000
#define DAC_BASE        0x40007400
#define PWR_BASE        0x40007000
#define BKP_BASE        0x40006c00
#define CAN1_BASE       0x40006400
#define CAN2_BASE       0x40006800
#define USB_CAN_SRAM_BASE 0x40006000
#define USB_DEVICE_BASE 0x40005c00
#define I2C2_BASE       0x40005800
#define I2C1_BASE       0x40005400
#define UART5_BASE      0x40005000
#define UART4_BASE      0x40004c00
#define USART3_BASE     0x40004800
#define USART2_BASE     0x40004400
#define SPI3_I2S_BASE   0x40003c00
#define SPI2_I2S_BASE   0x40003800
#define IWDG_BASE       0x40003000
#define WWDG_BASE       0x40002c00
#define RTC_BASE        0x40002800
#define TIM14_BASE      0x40002000
#define TIM13_BASE      0x40001c00
#define TIM12_BASE      0x40001800
#define TIM7_BASE       0x40001400
#define TIM6_BASE       0x40001000
#define TIM5_BASE       0x40000c00
#define TIM4_BASE       0x40000800
#define TIM3_BASE       0x40000400
#define TIM2_BASE       0x40000000
#define FLASH_BASE      0x40022000

// access to register with specified address
#define  MMIO32(addr)		(*(volatile uint32_t *)(addr))

/* Flash access control register */
#define FLASH_ACR       MMIO32(FLASH_BASE + 0x00)
// Prefetch buffer status
#define PRFTBS      0x20
// Prefetch buffer enable
#define PRFTBE      0x10
// Flash half cycle access enable
#define HLFCYA      0x08
// Latency
#define LATENCY_24M 0x00
#define LATENCY_48M 0x01
#define LATENCY_72M 0x02

#endif
