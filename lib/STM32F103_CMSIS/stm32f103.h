/**************************************************************************//**
 * @file     ARMCM3.h
 * @brief    CMSIS Core Peripheral Access Layer Header File for
 *           ARMCM3 Device
 * @version  V5.3.1
 * @date     09. July 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARMCM3_H
#define ARMCM3_H

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define  XTAL            (72000000UL)     /* Oscillator frequency */

#define  SYSTEM_CLOCK    XTAL	// only maximum, another freqs a left out

// prototypes of irqs again fo -wmissingprototypes ok
void WWDG_Handler(void);
void PVD_Handler(void);
void TAMPER_Handler(void);
void RTC_Handler(void);
void FLASH_Handler(void);
void RCC_Handler(void);
void EXTI0_Handler(void);
void EXTI1_Handler(void);
void EXTI2_Handler(void);
void EXTI3_Handler(void);
void EXTI4_Handler(void);
void DMA1_Channel1_Handler(void);
void DMA1_Channel2_Handler(void);
void DMA1_Channel3_Handler(void);
void DMA1_Channel4_Handler(void);
void DMA1_Channel5_Handler(void);
void DMA1_Channel6_Handler(void);
void DMA1_Channel7_Handler(void);
void ADC_Handler(void);
void usb_hp_can_tx_Handler(void);
void usb_lp_can_rx_Handler(void);
void CAN_RX1_Handler(void);
void CAN_SCE_Handler(void);
void EXTI9_5_Handler(void);
void TIM1_BRK_TIM15_Handler(void);
void TIM1_UP_TIM16_Handler(void);
void TIM1_TRG_COM_TIM17_Handler(void);
void TIM1_CC_Handler(void);
void TIM2_Handler(void);
void TIM3_Handler(void);
void TIM4_Handler(void);
void I2C1_EV_Handler(void);
void I2C1_ER_Handler(void);
void I2C2_EV_Handler(void);
void I2C2_ER_Handler(void);
void SPI1_Handler(void);
void SPI2_Handler(void);
void USART1_Handler(void);
void USART2_Handler(void);
void USART3_Handler(void);
void EXTI15_10_Handler(void);
void RTCAlarm_Handler(void);
void USB_Wakeup_Handler(void);
void TIM8_BRK_Handler(void);
void TIM8_UP_Handler(void);
void TIM8_TRG_COM_Handler(void);
void TIM8_CC_Handler(void);
void ADC3_Handler(void);
void FSMC_Handler(void);
void SDIO_Handler(void);
void TIM5_Handler(void);
void SPI3_Handler(void);
void UART4_Handler(void);
void UART5_Handler(void);
void TIM6_DAC_Handler(void);
void TIM7_Handler(void);
void DMA2_Channel1_Handler(void);
void DMA2_Channel2_Handler(void);
void DMA2_Channel3_Handler(void);
void DMA2_Channel4_5_Handler(void);

/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
/* -------------------  Processor Exceptions Numbers  ----------------------------- */
  NonMaskableInt_IRQn           = -14,     /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,     /*  3 HardFault Interrupt */
  MemoryManagement_IRQn         = -12,     /*  4 Memory Management Interrupt */
  BusFault_IRQn                 = -11,     /*  5 Bus Fault Interrupt */
  UsageFault_IRQn               = -10,     /*  6 Usage Fault Interrupt */
  SVCall_IRQn                   =  -5,     /* 11 SV Call Interrupt */
  DebugMonitor_IRQn             =  -4,     /* 12 Debug Monitor Interrupt */
  PendSV_IRQn                   =  -2,     /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,     /* 15 System Tick Interrupt */

/* -------------------  Processor Interrupt Numbers  ------------------------------ */
  WWDG_IRQn						= 0,
  PVD_IRQn						= 1,
  TAMPER_IRQn					= 2,
  RTC_IRQn						= 3,
  FLASH_IRQn					= 4,
  RCC_IRQn						= 5,
  EXTI0_IRQn					= 6,
  EXTI1_IRQn					= 7,
  EXTI2_IRQn					= 8,
  EXTI3_IRQn					= 9,
  EXTI4_IRQn					= 10,
  DMA1_Channel1_IRQn			= 11,
  DMA1_Channel2_IRQn			= 12,
  DMA1_Channel3_IRQn			= 13,
  DMA1_Channel4_IRQn			= 14,
  DMA1_Channel5_IRQn			= 15,
  DMA1_Channel6_IRQn			= 16,
  DMA1_Channel7_IRQn			= 17,
  ADC_IRQn						= 18,
  usb_hp_can_tx_IRQn			= 19,
  usb_lp_can_rx_IRQn			= 20,
  CAN_RX1_IRQn					= 21,
  CAN_SCE_IRQn					= 22,
  EXTI9_5_IRQn				 	= 23,
  TIM1_BRK_TIM15_IRQn			= 24,
  TIM1_UP_TIM16_IRQn			= 25,
  TIM1_TRG_COM_TIM17_IRQn		= 26,
  TIM1_CC_IRQn					= 27,
  TIM2_IRQn						= 28,
  TIM3_IRQn						= 29,
  TIM4_IRQn						= 30,
  I2C1_EV_IRQn					= 31,
  I2C1_ER_IRQn					= 32,
  I2C2_EV_IRQn					= 33,
  I2C2_ER_IRQn					= 34,
  SPI1_IRQn						= 35,
  SPI2_IRQn						= 36,
  USART1_IRQn					= 37,
  USART2_IRQn					= 38,
  USART3_IRQn					= 39,
  EXTI15_10_IRQn				= 40,
  RTCAlarm_IRQn					= 41,
  USB_Wakeup_IRQn				= 42,
  TIM8_BRK_IRQn					= 43,
  TIM8_UP_IRQn					= 44,
  TIM8_TRG_COM_IRQn				= 45,
  TIM8_CC_IRQn					= 46,
  ADC3_IRQn						= 47,
  FSMC_IRQn						= 48,
  SDIO_IRQn						= 49,
  TIM5_IRQn						= 50,
  SPI3_IRQn						= 51,
  UART4_IRQn					= 52,
  UART5_IRQn					= 53,
  TIM6_DAC_IRQn					= 54,
  TIM7_IRQn						= 55,
  DMA2_Channel1_IRQn			= 56,
  DMA2_Channel2_IRQn			= 57,
  DMA2_Channel3_IRQn			= 58,
  DMA2_Channel4_5_IRQn  		= 59
  /* Interrupts 60 .. 224 are left out */
} IRQn_Type;


/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* --------  Configuration of Core Peripherals  ----------------------------------- */
#define __CM3_REV                 0x0201U   /* Core revision r2p1 */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          3U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */

#include "../CMSIS_5/CMSIS/Core/Include/core_cm3.h"                       /* Processor and core peripherals */
#include "system_stm32f103.h"                  /* System Header */


/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


#ifdef __cplusplus
}
#endif

#endif  /* ARMCM3_H */
