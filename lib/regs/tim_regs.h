#ifndef H_TIM_REGS
#define H_TIM_REGS
/*
 * Part of Belkin STM32 HAL, timer registers of STMF103 MCU.
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

/* TIM1 control register 1 */
#define TIM1_CR1    MMIO32(TIM1_BASE + 0x00)
/* TIM8 control register 1 */
#define TIM8_CR1    MMIO32(TIM8_BASE + 0x00)
// Clock division
#define CKD_CK_INT      0x0000
#define CKD_CK_INT_DIV2 0x0100
#define CKD_CK_INT_DIV4 0x0200
#define ARPE            0x0080
// Center-aligned mode selection
#define CMS_EDGE        0x0000
#define CMS_CENTER1     0x0020
#define CMS_CENTER2     0x0040
#define CMS_CENTER3     0x0060
#define DIR             0x0010
#define OPM             0x0008
#define UDS             0x0004
#define UDIS            0x0002
#define CEN             0x0001
/* TIM2 control register 1 */
#define TIM2_CR1   MMIO32(TIM2_BASE + 0x00)
/* TIM3 control register 1 */
#define TIM3_CR1   MMIO32(TIM3_BASE + 0x00)
/* TIM4 control register 1 */
#define TIM4_CR1   MMIO32(TIM4_BASE + 0x00)
/* TIM5 control register 1 */
#define TIM5_CR1   MMIO32(TIM5_BASE + 0x00)
/* TIM6 control register 1 */
#define TIM6_CR1   MMIO32(TIM6_BASE + 0x00)
/* TIM7 control register 1 */
#define TIM7_CR1   MMIO32(TIM7_BASE + 0x00)
/* TIM9 control register 1 */
#define TIM9_CR1   MMIO32(TIM9_BASE + 0x00)
/* TIM10 control register 1 */
#define TIM10_CR1  MMIO32(TIM10_BASE + 0x00)
/* TIM11 control register 1 */
#define TIM11_CR1  MMIO32(TIM11_BASE + 0x00)
/* TIM12 control register 1 */
#define TIM12_CR1  MMIO32(TIM12_BASE + 0x00)
/* TIM13 control register 1 */
#define TIM13_CR1  MMIO32(TIM13_BASE + 0x00)
/* TIM14 control register 1 */
#define TIM14_CR1  MMIO32(TIM14_BASE + 0x00)

/* TIM1 control register 2 */
#define TIM1_CR2    MMIO32(TIM1_BASE + 0x04)
/* TIM8 control register 2 */
#define TIM8_CR2    MMIO32(TIM8_BASE + 0x04)
#define OIS4        0x4000
#define OIS3N       0x2000
#define OIS3        0x1000
#define OIS2N       0x0800
#define OIS2        0x0400
#define OIS1N       0x0200
#define OIS1        0x0100
#define TI1S        0x0080
// Master mode selection
#define MMS_RESET           0x0000
#define MMS_ENABLE          0x0010
#define MMS_UPDATE          0x0020
#define MMS_COMPARE_PULSE   0x0030
#define MMS_COMPARE_OC1REF  0x0040
#define MMS_COMPARE_OC2REF  0x0050
#define MMS_COMPARE_OC3REF  0x0060
#define MMS_COMPARE_OC4REF  0x0070
#define CCDS                0x0008
#define CCUS                0x0004
#define CCPS                0x0001
/* TIM2 control register 2 */
#define TIM2_CR2    MMIO32(TIM2_BASE + 0x04)
/* TIM3 control register 2 */
#define TIM3_CR2    MMIO32(TIM3_BASE + 0x04)
/* TIM4 control register 2 */
#define TIM4_CR2    MMIO32(TIM4_BASE + 0x04)
/* TIM5 control register 2 */
#define TIM5_CR2    MMIO32(TIM5_BASE + 0x04)
/* TIM6 control register 2 */
#define TIM6_CR2    MMIO32(TIM6_BASE + 0x04)
/* TIM7 control register 2 */
#define TIM7_CR2    MMIO32(TIM7_BASE + 0x04)

/* TIM1 slave mode control register */
#define TIM1_SMCR   MMIO32(TIM1_BASE + 0x08)
/* TIM8 slave mode control register */
#define TIM8_SMCR   MMIO32(TIM8_BASE + 0x08)
#define ETP             0x8000
#define ECE             0x4000
// External trigger prescaler
#define ETPS_OFF        0x0000
#define ETPS_DIV2       0x1000
#define ETPS_DIV4       0x2000
#define ETPS_DIV8       0x3000
// External trigger filter
#define ETF_MASK        0x0f00
#define ETF_NO_FILTER   0x0000
#define ETF_CK_INT_2    0x0100
#define ETF_CK_INT_4    0x0200
#define ETF_CK_INT_8    0x0300
#define ETF_DTS_DIV2_6  0x0400
#define ETF_DTS_DIV2_8  0x0500
#define ETF_DTS_DIV4_6  0x0600
#define ETF_DTS_DIV4_7  0x0700
#define ETF_DTS_DIV8_6  0x0800
#define ETF_DTS_DIV8_8  0x0900
#define ETF_DTS_DIV16_5 0x0a00
#define ETF_DTS_DIV16_6 0x0b00
#define ETF_DTS_DIV16_8 0x0c00
#define ETF_DTS_DIV32_5 0x0d00
#define ETF_DTS_DIV32_6 0x0e00
#define ETF_DTS_DIV32_8 0x0f00
#define MSM             0x0080
// Trigger selection
#define TS_ITR0         0x0000
#define TS_ITR1         0x0010
#define TS_ITR2         0x0020
#define TS_ITR3         0x0030
#define TS_TI1F_ED      0x0040
#define TS_TI1FP1       0x0050
#define TS_TI1FP2       0x0060
#define TS_ETRF         0x0070
// Slave mode selection
#define SMS_DISABLED    0x0000
#define SMS_ENCODER1    0x0001
#define SMS_ENCODER2    0x0002
#define SMS_ENCODER3    0x0003
#define SMS_RESET       0x0004
#define SMS_GATED       0x0005
#define SMS_TRIGGER     0x0006
#define SMS_EXTERNAL    0x0007
/* TIM2 slave mode control register */
#define TIM2_SMCR   MMIO32(TIM2_BASE + 0x08)
/* TIM3 slave mode control register */
#define TIM3_SMCR   MMIO32(TIM3_BASE + 0x08)
/* TIM4 slave mode control register */
#define TIM4_SMCR   MMIO32(TIM4_BASE + 0x08)
/* TIM5 slave mode control register */
#define TIM5_SMCR   MMIO32(TIM5_BASE + 0x08)
/* TIM9 slave mode control register */
#define TIM9_SMCR   MMIO32(TIM9_BASE + 0x08)
/* TIM12 slave mode control register */
#define TIM12_SMCR  MMIO32(TIM12_BASE + 0x08)


/* TIM1 DMA/interrupt enable register */
#define TIM1_DIER   MMIO32(TIM1_BASE + 0x0c)
/* TIM8 DMA/interrupt enable register */
#define TIM8_DIER   MMIO32(TIM8_BASE + 0x0c)
#define TDE         0x4000
#define COMDE       0x2000
#define CC4DE       0x1000
#define CC3DE       0x0800
#define CC2DE       0x0400
#define CC1DE       0x0200
#define UDE         0x0100
#define BIE         0x0080
#define TIE         0x0040
#define COMIE       0x0020
#define CC4IE       0x0010
#define CC3IE       0x0008
#define CC2IE       0x0004
#define CC1IE       0x0002
#define UIE         0x0001
/* TIM2 DMA/interrupt enable register */
#define TIM2_DIER   MMIO32(TIM2_BASE + 0x0c)
/* TIM3 DMA/interrupt enable register */
#define TIM3_DIER   MMIO32(TIM3_BASE + 0x0c)
/* TIM4 DMA/interrupt enable register */
#define TIM4_DIER   MMIO32(TIM4_BASE + 0x0c)
/* TIM5 DMA/interrupt enable register */
#define TIM5_DIER   MMIO32(TIM5_BASE + 0x0c)
/* TIM6 DMA/interrupt enable register */
#define TIM6_DIER   MMIO32(TIM6_BASE + 0x0c)
/* TIM7 DMA/interrupt enable register */
#define TIM7_DIER   MMIO32(TIM7_BASE + 0x0c)
/* TIM9 Interrupt enable register */
#define TIM9_DIER   MMIO32(TIM9_BASE + 0x0c)
/* TIM10 Interrupt enable register */
#define TIM10_DIER  MMIO32(TIM10_BASE + 0x0c)
/* TIM11 Interrupt enable register */
#define TIM11_DIER  MMIO32(TIM11_BASE + 0x0c)
/* TIM12 Interrupt enable register */
#define TIM12_DIER  MMIO32(TIM12_BASE + 0x0c)
/* TIM13 Interrupt enable register */
#define TIM13_DIER  MMIO32(TIM13_BASE + 0x0c)
/* TIM14 Interrupt enable register */
#define TIM14_DIER  MMIO32(TIM14_BASE + 0x0c)

/* TIM1 status register */
#define TIM1_SR     MMIO32(TIM1_BASE + 0x10)
/* TIM8 status register */
#define TIM8_SR     MMIO32(TIM8_BASE + 0x10)
#define CC4OF   0x1000
#define CC3OF   0x0800
#define CC2OF   0x0400
#define CC1OF   0x0200
#define BIF     0x0080
#define TIF     0x0040
#define COMIF   0x0020
#define CC4IF   0x0010
#define CC3IF   0x0008
#define CC2IF   0x0004
#define CC1IF   0x0002
#define UIF     0x0001
/* TIM5 status register */
#define TIM2_SR   MMIO32(TIM2_BASE + 0x10)
/* TIM4 status register */
#define TIM3_SR   MMIO32(TIM3_BASE + 0x10)
/* TIM3 status register */
#define TIM4_SR   MMIO32(TIM4_BASE + 0x10)
/* TIM2 status register */
#define TIM5_SR   MMIO32(TIM5_BASE + 0x10)
/* TIM6 status register */
#define TIM6_SR   MMIO32(TIM6_BASE + 0x10)
/* TIM7 status register */
#define TIM7_SR   MMIO32(TIM7_BASE + 0x10)
/* TIM9 status register */
#define TIM9_SR   MMIO32(TIM9_BASE + 0x10)
/* TIM10 status register */
#define TIM10_SR  MMIO32(TIM10_BASE + 0x10)
/* TIM11 status register */
#define TIM11_SR  MMIO32(TIM11_BASE + 0x10)
/* TIM12 status register */
#define TIM12_SR  MMIO32(TIM12_BASE + 0x10)
/* TIM11 status register */
#define TIM13_SR  MMIO32(TIM13_BASE + 0x10)
/* TIM12 status register */
#define TIM14_SR  MMIO32(TIM14_BASE + 0x10)

/* TIM1 event generation register */
#define TIM1_EGR    MMIO32(TIM1_BASE + 0x14)
/* TIM8 event generation register */
#define TIM8_EGR    MMIO32(TIM8_BASE + 0x14)
#define BG      0x80
#define TG      0x40
#define COMG    0x20
#define CC4G    0x10
#define CC3G    0x08
#define CC2G    0x04
#define CC1G    0x02
#define UG      0x01
/* TIM2 event generation register */
#define TIM2_EGR   MMIO32(TIM2_BASE + 0x14)
/* TIM3 event generation register */
#define TIM3_EGR   MMIO32(TIM3_BASE + 0x14)
/* TIM4 event generation register */
#define TIM4_EGR   MMIO32(TIM4_BASE + 0x14)
/* TIM5 event generation register */
#define TIM5_EGR   MMIO32(TIM5_BASE + 0x14)
/* TIM6 event generation register */
#define TIM6_EGR   MMIO32(TIM6_BASE + 0x14)
/* TIM7 event generation register */
#define TIM7_EGR   MMIO32(TIM7_BASE + 0x14)
/* TIM9 event generation register */
#define TIM9_EGR   MMIO32(TIM9_BASE + 0x14)
/* TIM10 event generation register */
#define TIM10_EGR  MMIO32(TIM10_BASE + 0x14)
/* TIM11 event generation register */
#define TIM11_EGR  MMIO32(TIM11_BASE + 0x14)
/* TIM12 event generation register */
#define TIM12_EGR  MMIO32(TIM12_BASE + 0x14)
/* TIM13 event generation register */
#define TIM13_EGR  MMIO32(TIM13_BASE + 0x14)
/* TIM14 event generation register */
#define TIM14_EGR  MMIO32(TIM14_BASE + 0x14)

/* TIM1 capture/compare mode register 1 */
#define TIM1_CCMR1  MMIO32(TIM1_BASE + 0x18)
/* TIM8 capture/compare mode register 1 */
#define TIM8_CCMR1  MMIO32(TIM8_BASE + 0x18)
/* Output compare mode */
#define OC2CE       0x8000
// Output Compare 2 mode
#define OC2M_FROZEN         0x0000
#define OC2M_CH1_ACT        0x1000
#define OC2M_CH1_INACT      0x2000
#define OC2M_TOGGLE         0x3000
#define OC2M_FORCE_INACT    0x4000
#define OC2M_FORCE_ACT      0x5000
#define OC2M_PWM1           0x6000
#define OC2M_PWM2           0x7000
#define OC2PE               0x0800
#define OC2FE               0x0400
// Capture/Compare 2 selection
#define CC2S_OUTPUT         0x0000
#define CC2S_INPUT_TI1      0x0100
#define CC2S_INPUT_TI2      0x0200
#define CC2S_INPUT_TRC      0x0300
#define OC1CE               0x0080
// Output Compare 1 mode
#define OC1M_FROZEN         0x0000
#define OC1M_CH1_ACT        0x0010
#define OC1M_CH1_INACT      0x0020
#define OC1M_TOGGLE         0x0030
#define OC1M_FORCE_INACT    0x0040
#define OC1M_FORCE_ACT      0x0050
#define OC1M_PWM1           0x0060
#define OC1M_PWM2           0x0070
#define OC1PE               0x0008
#define OC1FE               0x0004
// Capture/Compare 1 selection
#define CC1S_OUTPUT         0x0000
#define CC1S_INPUT_TI1      0x0001
#define CC1S_INPUT_TI2      0x0002
#define CC1S_INPUT_TRC      0x0003
/* Input capture mode */
// Input capture 2 filter
#define IC2F_NO_FILTER      0x0000
#define IC2F_CK_INT_2       0x1000
#define IC2F_CK_INT_4       0x2000
#define IC2F_CK_INT_8       0x3000
#define IC2F_DTS_DIV2_6     0x4000
#define IC2F_DTS_DIV2_8     0x5000
#define IC2F_DTS_DIV4_6     0x6000
#define IC2F_DTS_DIV4_7     0x7000
#define IC2F_DTS_DIV8_6     0x8000
#define IC2F_DTS_DIV8_8     0x9000
#define IC2F_DTS_DIV16_5    0xa000
#define IC2F_DTS_DIV16_6    0xb000
#define IC2F_DTS_DIV16_8    0xc000
#define IC2F_DTS_DIV32_5    0xd000
#define IC2F_DTS_DIV32_6    0xe000
#define IC2F_DTS_DIV32_8    0xf000
// Input capture 2 prescaler
#define IC2PSC_NO           0x0000
#define IC2PSC_2            0x0400
#define IC2PSC_4            0x0800
#define IC2PSC_8            0x0c00
// Input capture 1 filter
#define IC1F_NO_FILTER      0x0000
#define IC1F_CK_INT_2       0x0010
#define IC1F_CK_INT_4       0x0020
#define IC1F_CK_INT_8       0x0030
#define IC1F_DTS_DIV2_6     0x0040
#define IC1F_DTS_DIV2_8     0x0050
#define IC1F_DTS_DIV4_6     0x0060
#define IC1F_DTS_DIV4_7     0x0070
#define IC1F_DTS_DIV8_6     0x0080
#define IC1F_DTS_DIV8_8     0x0090
#define IC1F_DTS_DIV16_5    0x00a0
#define IC1F_DTS_DIV16_6    0x00b0
#define IC1F_DTS_DIV16_8    0x00c0
#define IC1F_DTS_DIV32_5    0x00d0
#define IC1F_DTS_DIV32_6    0x00e0
#define IC1F_DTS_DIV32_8    0x00f0
// Input capture 1 prescaler
#define IC1PSC_NO           0x0000
#define IC1PSC_2            0x0004
#define IC1PSC_4            0x0008
#define IC1PSC_8            0x000c
/* TIM2 capture/compare mode register 1 */
#define TIM2_CCMR1   MMIO32(TIM2_BASE + 0x18)
/* TIM3 capture/compare mode register 1 */
#define TIM3_CCMR1   MMIO32(TIM3_BASE + 0x18)
/* TIM4 capture/compare mode register 1 */
#define TIM4_CCMR1   MMIO32(TIM4_BASE + 0x18)
/* TIM5 capture/compare mode register 1 */
#define TIM5_CCMR1   MMIO32(TIM5_BASE + 0x18)
/* TIM9 capture/compare mode register 1 */
#define TIM9_CCMR1   MMIO32(TIM9_BASE + 0x18)
/* TIM10 capture/compare mode register 1 */
#define TIM10_CCMR1  MMIO32(TIM10_BASE + 0x18)
/* TIM11 capture/compare mode register 1 */
#define TIM11_CCMR1  MMIO32(TIM11_BASE + 0x18)
/* TIM12 capture/compare mode register 1 */
#define TIM12_CCMR1  MMIO32(TIM12_BASE + 0x18)
/* TIM13 capture/compare mode register 1 */
#define TIM13_CCMR1  MMIO32(TIM13_BASE + 0x18)
/* TIM14 capture/compare mode register 1 */
#define TIM14_CCMR1  MMIO32(TIM14_BASE + 0x18)

/* TIM1 capture/compare mode register 2 */
#define TIM1_CCMR2  MMIO32(TIM1_BASE + 0x1c)
/* TIM8 capture/compare mode register 2 */
#define TIM8_CCMR2  MMIO32(TIM8_BASE + 0x1c)
/* Output compare mode */
#define OC4CE       0x8000
// Output Compare 2 mode
#define OC4M_FROZEN         0x0000
#define OC4M_CH1_ACT        0x1000
#define OC4M_CH1_INACT      0x2000
#define OC4M_TOGGLE         0x3000
#define OC4M_FORCE_INACT    0x4000
#define OC4M_FORCE_ACT      0x5000
#define OC4M_PWM1           0x6000
#define OC4M_PWM2           0x7000
#define OC4PE               0x0800
#define OC4FE               0x0400
// Capture/Compare 2 selection
#define CC4S_OUTPUT         0x0000
#define CC4S_INPUT_TI1      0x0100
#define CC4S_INPUT_TI2      0x0200
#define CC4S_INPUT_TRC      0x0300
#define OC3CE               0x0080
// Output Compare 1 mode
#define OC3M_FROZEN         0x0000
#define OC3M_CH1_ACT        0x0010
#define OC3M_CH1_INACT      0x0020
#define OC3M_TOGGLE         0x0030
#define OC3M_FORCE_INACT    0x0040
#define OC3M_FORCE_ACT      0x0050
#define OC3M_PWM1           0x0060
#define OC3M_PWM2           0x0070
#define OC3PE               0x0008
#define OC3FE               0x0004
// Capture/Compare 1 selection
#define CC3S_OUTPUT         0x0000
#define CC3S_INPUT_TI1      0x0001
#define CC3S_INPUT_TI2      0x0002
#define CC3S_INPUT_TRC      0x0003
/* Input capture mode */
// Input capture 2 filter
#define IC4F_NO_FILTER      0x0000
#define IC4F_CK_INT_2       0x1000
#define IC4F_CK_INT_4       0x2000
#define IC4F_CK_INT_8       0x3000
#define IC4F_DTS_DIV2_6     0x4000
#define IC4F_DTS_DIV2_8     0x5000
#define IC4F_DTS_DIV4_6     0x6000
#define IC4F_DTS_DIV4_7     0x7000
#define IC4F_DTS_DIV8_6     0x8000
#define IC4F_DTS_DIV8_8     0x9000
#define IC4F_DTS_DIV16_5    0xa000
#define IC4F_DTS_DIV16_6    0xb000
#define IC4F_DTS_DIV16_8    0xc000
#define IC4F_DTS_DIV32_5    0xd000
#define IC4F_DTS_DIV32_6    0xe000
#define IC4F_DTS_DIV32_8    0xf000
// Input capture 2 prescaler
#define IC4PSC_NO           0x0000
#define IC4PSC_2            0x0400
#define IC4PSC_4            0x0800
#define IC4PSC_8            0x0c00
// Input capture 1 filter
#define IC3F_NO_FILTER      0x0000
#define IC3F_CK_INT_2       0x0010
#define IC3F_CK_INT_4       0x0020
#define IC3F_CK_INT_8       0x0030
#define IC3F_DTS_DIV2_6     0x0040
#define IC3F_DTS_DIV2_8     0x0050
#define IC3F_DTS_DIV4_6     0x0060
#define IC3F_DTS_DIV4_7     0x0070
#define IC3F_DTS_DIV8_6     0x0080
#define IC3F_DTS_DIV8_8     0x0090
#define IC3F_DTS_DIV16_5    0x00a0
#define IC3F_DTS_DIV16_6    0x00b0
#define IC3F_DTS_DIV16_8    0x00c0
#define IC3F_DTS_DIV32_5    0x00d0
#define IC3F_DTS_DIV32_6    0x00e0
#define IC3F_DTS_DIV32_8    0x00f0
// Input capture 1 prescaler
#define IC3PSC_NO           0x0000
#define IC3PSC_2            0x0004
#define IC3PSC_4            0x0008
#define IC3PSC_8            0x000c
/* TIM2 capture/compare mode register 2 */
#define TIM2_CCMR2  MMIO32(TIM2_BASE + 0x1c)
/* TIM3 capture/compare mode register 2 */
#define TIM3_CCMR2  MMIO32(TIM3_BASE + 0x1c)
/* TIM4 capture/compare mode register 2 */
#define TIM4_CCMR2  MMIO32(TIM4_BASE + 0x1c)
/* TIM5 capture/compare mode register 2 */
#define TIM5_CCMR2  MMIO32(TIM5_BASE + 0x1c)

/* TIM1 capture/compare enable register */
#define TIM1_CCER   MMIO32(TIM1_BASE + 0x20)
/* TIM8 capture/compare enable register */
#define TIM8_CCER   MMIO32(TIM8_BASE + 0x20)
#define CC4P    0x2000
#define CC4E    0x1000
#define CC3NP   0x0800
#define CC3NE   0x0400
#define CC3P    0x0200
#define CC3E    0x0100
#define CC2NP   0x0080
#define CC2NE   0x0040
#define CC2P    0x0020
#define CC2E    0x0010
#define CC1NP   0x0008
#define CC1NE   0x0004
#define CC1P    0x0002
#define CC1E    0x0001
/* TIM2 capture/compare enable register */
#define TIM2_CCER    MMIO32(TIM2_BASE + 0x20)
/* TIM3 capture/compare enable register */
#define TIM3_CCER    MMIO32(TIM3_BASE + 0x20)
/* TIM4 capture/compare enable register */
#define TIM4_CCER    MMIO32(TIM4_BASE + 0x20)
/* TIM5 capture/compare enable register */
#define TIM5_CCER    MMIO32(TIM5_BASE + 0x20)
/* TIM9 capture/compare enable register */
#define TIM9_CCER    MMIO32(TIM9_BASE + 0x20)
/* TIM10 capture/compare enable register */
#define TIM10_CCER   MMIO32(TIM10_BASE + 0x20)
/* TIM11 capture/compare enable register */
#define TIM11_CCER   MMIO32(TIM11_BASE + 0x20)
/* TIM12 capture/compare enable register */
#define TIM12_CCER   MMIO32(TIM12_BASE + 0x20)
/* TIM13 capture/compare enable register */
#define TIM13_CCER   MMIO32(TIM13_BASE + 0x20)
/* TIM14 capture/compare enable register */
#define TIM14_CCER   MMIO32(TIM14_BASE + 0x20)

/* TIM1 counter */
#define TIM1_CNT    MMIO32(TIM1_BASE + 0x24)
/* TIM8 counter */
#define TIM8_CNT    MMIO32(TIM8_BASE + 0x24)
/* TIM2 counter */
#define TIM2_CNT    MMIO32(TIM2_BASE + 0x24)
/* TIM3 counter */
#define TIM3_CNT    MMIO32(TIM3_BASE + 0x24)
/* TIM4 capture/compare register 1 */
#define TIM4_CNT    MMIO32(TIM4_BASE + 0x24)
/* TIM5 capture/compare register 1 */
#define TIM5_CNT    MMIO32(TIM5_BASE + 0x24)
/* TIM6 capture/compare register 1 */
#define TIM6_CNT    MMIO32(TIM6_BASE + 0x24)
/* TIM7 capture/compare register 1 */
#define TIM7_CNT    MMIO32(TIM7_BASE + 0x24)
/* TIM9 capture/compare register 1 */
#define TIM9_CNT    MMIO32(TIM9_BASE + 0x24)
/* TIM10 capture/compare register 1 */
#define TIM10_CNT   MMIO32(TIM10_BASE + 0x24)
/* TIM11 capture/compare register 1 */
#define TIM11_CNT   MMIO32(TIM11_BASE + 0x24)
/* TIM12 capture/compare register 1 */
#define TIM12_CNT   MMIO32(TIM12_BASE + 0x24)
/* TIM13 capture/compare register 1 */
#define TIM13_CNT   MMIO32(TIM13_BASE + 0x24)
/* TIM14 capture/compare register 1 */
#define TIM14_CNT   MMIO32(TIM14_BASE + 0x24)

/* TIM1 prescaler */
#define TIM1_PSC    MMIO32(TIM1_BASE + 0x28)
/* TIM8 prescaler */
#define TIM8_PSC    MMIO32(TIM8_BASE + 0x28)
/* TIM2 prescaler */
#define TIM2_PSC    MMIO32(TIM2_BASE + 0x28)
/* TIM3 prescaler */
#define TIM3_PSC    MMIO32(TIM3_BASE + 0x28)
/* TIM4 prescaler */
#define TIM4_PSC    MMIO32(TIM4_BASE + 0x28)
/* TIM5 prescaler */
#define TIM5_PSC    MMIO32(TIM5_BASE + 0x28)
/* TIM6 prescaler */
#define TIM6_PSC    MMIO32(TIM6_BASE + 0x28)
/* TIM7 prescaler */
#define TIM7_PSC    MMIO32(TIM7_BASE + 0x28)
/* TIM9 prescaler */
#define TIM9_PSC    MMIO32(TIM9_BASE + 0x28)
/* TIM10 prescaler */
#define TIM10_PSC   MMIO32(TIM10_BASE + 0x28)
/* TIM11 prescaler */
#define TIM11_PSC   MMIO32(TIM11_BASE + 0x28)
/* TIM12 prescaler */
#define TIM12_PSC   MMIO32(TIM12_BASE + 0x28)
/* TIM13 prescaler */
#define TIM13_PSC   MMIO32(TIM13_BASE + 0x28)
/* TIM14 prescaler */
#define TIM14_PSC   MMIO32(TIM14_BASE + 0x28)

/* TIM1 auto-reload register */
#define TIM1_ARR    MMIO32(TIM1_BASE + 0x2c)
/* TIM8 auto-reload register */
#define TIM8_ARR    MMIO32(TIM8_BASE + 0x2c)
/* TIM2 auto-reload register */
#define TIM2_ARR    MMIO32(TIM2_BASE + 0x2c)
/* TIM3 auto-reload register */
#define TIM3_ARR    MMIO32(TIM3_BASE + 0x2c)
/* TIM4 auto-reload register */
#define TIM4_ARR    MMIO32(TIM4_BASE + 0x2c)
/* TIM5 auto-reload register */
#define TIM5_ARR    MMIO32(TIM5_BASE + 0x2c)
/* TIM6 auto-reload register */
#define TIM6_ARR    MMIO32(TIM6_BASE + 0x2c)
/* TIM7 auto-reload register */
#define TIM7_ARR    MMIO32(TIM7_BASE + 0x2c)
/* TIM9 auto-reload register */
#define TIM9_ARR   MMIO32(TIM9_BASE + 0x2c)
/* TIM10 auto-reload register */
#define TIM10_ARR   MMIO32(TIM10_BASE + 0x2c)
/* TIM11 auto-reload register */
#define TIM11_ARR   MMIO32(TIM11_BASE + 0x2c)
/* TIM12 auto-reload register */
#define TIM12_ARR   MMIO32(TIM12_BASE + 0x2c)
/* TIM13 auto-reload register */
#define TIM13_ARR   MMIO32(TIM13_BASE + 0x2c)
/* TIM14 auto-reload register */
#define TIM14_ARR   MMIO32(TIM14_BASE + 0x2c)

/* TIM1 repetition counter register */
#define TIM1_RCR    MMIO32(TIM1_BASE + 0x30)
/* TIM8 repetition counter register */
#define TIM8_RCR    MMIO32(TIM8_BASE + 0x30)

/* TIM1 capture/compare register 1 */
#define TIM1_CCR1   MMIO32(TIM1_BASE + 0x34)
/* TIM8 capture/compare register 1 */
#define TIM8_CCR1   MMIO32(TIM8_BASE + 0x34)
/* TIM2 capture/compare register 1 */
#define TIM2_CCR1   MMIO32(TIM2_BASE + 0x34)
/* TIM3 capture/compare register 1 */
#define TIM3_CCR1   MMIO32(TIM3_BASE + 0x34)
/* TIM4 capture/compare register 1 */
#define TIM4_CCR1   MMIO32(TIM4_BASE + 0x34)
/* TIM5 capture/compare register 1 */
#define TIM5_CCR1   MMIO32(TIM5_BASE + 0x34)
/* TIM9 capture/compare register 1 */
#define TIM9_CCR1   MMIO32(TIM9_BASE + 0x34)
/* TIM10 capture/compare register 1 */
#define TIM10_CCR1   MMIO32(TIM10_BASE + 0x34)
/* TIM11 capture/compare register 1 */
#define TIM11_CCR1   MMIO32(TIM11_BASE + 0x34)
/* TIM12 capture/compare register 1 */
#define TIM12_CCR1   MMIO32(TIM12_BASE + 0x34)
/* TIM13 capture/compare register 1 */
#define TIM13_CCR1   MMIO32(TIM13_BASE + 0x34)
/* TIM14 capture/compare register 1 */
#define TIM14_CCR1   MMIO32(TIM14_BASE + 0x34)

/* TIM1 capture/compare register 2 */
#define TIM1_CCR2   MMIO32(TIM1_BASE + 0x38)
/* TIM8 capture/compare register 2 */
#define TIM8_CCR2   MMIO32(TIM8_BASE + 0x38)
/* TIM2 capture/compare register 2 */
#define TIM2_CCR2   MMIO32(TIM2_BASE + 0x38)
/* TIM3 capture/compare register 2 */
#define TIM3_CCR2   MMIO32(TIM3_BASE + 0x38)
/* TIM4 capture/compare register 2 */
#define TIM4_CCR2   MMIO32(TIM4_BASE + 0x38)
/* TIM5 capture/compare register 2 */
#define TIM5_CCR2   MMIO32(TIM5_BASE + 0x38)
/* TIM9 capture/compare register 2 */
#define TIM9_CCR2   MMIO32(TIM9_BASE + 0x38)
/* TIM12 capture/compare register 2 */
#define TIM12_CCR2   MMIO32(TIM12_BASE + 0x38)

/* TIM1 capture/compare register 3 */
#define TIM1_CCR3   MMIO32(TIM1_BASE + 0x3c)
/* TIM8 capture/compare register 3 */
#define TIM8_CCR3   MMIO32(TIM8_BASE + 0x3c)
/* TIM2 capture/compare register 3 */
#define TIM2_CCR3   MMIO32(TIM2_BASE + 0x3c)
/* TIM3 capture/compare register 3 */
#define TIM3_CCR3   MMIO32(TIM3_BASE + 0x3c)
/* TIM4 capture/compare register 3 */
#define TIM4_CCR3   MMIO32(TIM4_BASE + 0x3c)
/* TIM5 capture/compare register 3 */
#define TIM5_CCR3   MMIO32(TIM5_BASE + 0x3c)


/* TIM1 capture/compare register 4 */
#define TIM1_CCR4   MMIO32(TIM1_BASE + 0x40)
/* TIM8 capture/compare register 4 */
#define TIM8_CCR4   MMIO32(TIM8_BASE + 0x40)
/* TIM2 capture/compare register 4 */
#define TIM2_CCR4   MMIO32(TIM2_BASE + 0x40)
/* TIM3 capture/compare register 4 */
#define TIM3_CCR4   MMIO32(TIM3_BASE + 0x40)
/* TIM4 capture/compare register 4 */
#define TIM4_CCR4   MMIO32(TIM4_BASE + 0x40)
/* TIM5 capture/compare register 4 */
#define TIM5_CCR4   MMIO32(TIM5_BASE + 0x40)

/* TIM1 break and dead-time register */
#define TIM1_BDTR   MMIO32(TIM1_BASE + 0x44)
/* TIM8 break and dead-time register */
#define TIM8_BDTR   MMIO32(TIM8_BASE + 0x44)
#define MOE         0x8000
#define AOE         0x4000
#define BKP         0x2000
#define BKE         0x1000
#define OSSR        0x0800
#define OSSI        0x0400
// Lock configuration
#define LOCK_OFF    0x0000
#define LOCK_LEVEL1 0x0100
#define LOCK_LEVEL2 0x0200
#define LOCK_LEVEL3 0x0300
// Dead-time generator setup

/* TIM1 DMA control register */
#define TIM1_DCR    MMIO32(TIM1_BASE + 0x48)
/* TIM8 DMA control register */
#define TIM8_DCR    MMIO32(TIM8_BASE + 0x48)
// DMA burst length
#define DBL_OFFS    8
// DMA base address
#define DBA_TIM_CR1   0x00
#define DBA_TIM_CR2   0x01
#define DBA_TIM_SMCR  0x02
#define DBA_TIM_DIER  0x03
#define DBA_TIM_SR    0x04
#define DBA_TIM_EGR   0x05
#define DBA_TIM_CCMR1 0x06
#define DBA_TIM_CCMR2 0x07
#define DBA_TIM_CCER  0x08
#define DBA_TIM_CNT   0x09
#define DBA_TIM_PSC   0x0a
#define DBA_TIM_ARR   0x0b
#define DBA_TIM_RCR   0x0c
#define DBA_TIM_CCR1  0x0d
#define DBA_TIM_CCR2  0x0e
#define DBA_TIM_CCR3  0x0f
#define DBA_TIM_CCR4  0x10
#define DBA_TIM_BDTR  0x11
/* TIM2 DMA control register */
#define TIM2_DCR    MMIO32(TIM2_BASE + 0x48)
/* TIM3 DMA control register */
#define TIM3_DCR    MMIO32(TIM3_BASE + 0x48)
/* TIM4 DMA control register */
#define TIM4_DCR    MMIO32(TIM4_BASE + 0x48)
/* TIM5 DMA control register */
#define TIM5_DCR    MMIO32(TIM5_BASE + 0x48)

/* TIM1 DMA address for full transfer */
#define TIM1_DMAR   MMIO32(TIM1_BASE + 0x4c)
/* TIM8 DMA address for full transfer */
#define TIM8_DMAR   MMIO32(TIM8_BASE + 0x4c)
/* TIM2 DMA address for full transfer */
#define TIM2_DMAR   MMIO32(TIM2_BASE + 0x4c)
/* TIM3 DMA address for full transfer */
#define TIM3_DMAR   MMIO32(TIM3_BASE + 0x4c)
/* TIM4 DMA address for full transfer */
#define TIM4_DMAR   MMIO32(TIM4_BASE + 0x4c)
/* TIM5 DMA address for full transfer */
#define TIM5_DMAR   MMIO32(TIM5_BASE + 0x4c)

#endif
