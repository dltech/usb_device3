/******************************************************************************
 * @file     startup_ARMCM3.c
 * @brief    CMSIS-Core(M) Device Startup File for a Cortex-M3 Device
 * @version  V2.0.3
 * @date     31. March 2020
 ******************************************************************************/
/*
 * Copyright (c) 2009-2020 Arm Limited. All rights reserved.
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

#if defined (ARMCM3)
  #include "stm32f103.h"
#else
  #error device not specified!
#endif

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;

//extern __NO_RETURN void __PROGRAM_START(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler  (void);
            void Default_Handler(void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak));
void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));

void WWDG_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void TAMPER_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel3_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel5_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel6_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel7_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void ADC_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void usb_hp_can_tx_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void usb_lp_can_rx_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN_RX1_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN_SCE_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM15_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM16_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM17_Handler (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM4_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void RTCAlarm_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void USB_Wakeup_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_BRK_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void ADC3_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void FSMC_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_Handler		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_Handler			(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel1_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel2_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel3_Handler	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Channel4_5_Handler (void) __attribute__ ((weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const VECTOR_TABLE_Type __VECTOR_TABLE[240];
       const VECTOR_TABLE_Type __VECTOR_TABLE[240] __VECTOR_TABLE_ATTRIBUTE = {
  (VECTOR_TABLE_Type)(&__INITIAL_SP),       /*     Initial Stack Pointer */
  Reset_Handler,                            /*     Reset Handler */
  NMI_Handler,                              /* -14 NMI Handler */
  HardFault_Handler,                        /* -13 Hard Fault Handler */
  MemManage_Handler,                        /* -12 MPU Fault Handler */
  BusFault_Handler,                         /* -11 Bus Fault Handler */
  UsageFault_Handler,                       /* -10 Usage Fault Handler */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  SVC_Handler,                              /*  -5 SVC Handler */
  DebugMon_Handler,                         /*  -4 Debug Monitor Handler */
  0,                                        /*     Reserved */
  PendSV_Handler,                           /*  -2 PendSV Handler */
  SysTick_Handler,                          /*  -1 SysTick Handler */

  /* Interrupts */
  WWDG_Handler,					// Window watchdog interrrupt
  PVD_Handler,					// PVD through EXTI Line detection interrupt
  TAMPER_Handler,				// Tamper interrupt
  RTC_Handler,					// RTC global interrupt
  FLASH_Handler,				// Flash global interrupt
  RCC_Handler,					// RCC global interrupt
  EXTI0_Handler,				// EXTI Line0 interrupt
  EXTI1_Handler,				// EXTI Line1 interrupt
  EXTI2_Handler,				// EXTI Line2 interrupt
  EXTI3_Handler,				// EXTI Line3 interrupt
  EXTI4_Handler,				// EXTI Line4 interrupt
  DMA1_Channel1_Handler,		// DMA Channel1 global interrupt
  DMA1_Channel2_Handler,		// DMA Channel2 global interrupt
  DMA1_Channel3_Handler,		// DMA Channel3 global interrupt
  DMA1_Channel4_Handler,		// DMA Channel4 global interrupt
  DMA1_Channel5_Handler,		// DMA Channel5 global interrupt
  DMA1_Channel6_Handler,		// DMA Channel6 global interrupt
  DMA1_Channel7_Handler,		// DMA Channel7 global interrupt
  ADC_Handler,					// ADC1 and ADC2 global interrupt
  usb_hp_can_tx_Handler,		// USB high priority or CAN TX interrupts
  usb_lp_can_rx_Handler,		// USB Low priority or CAN RX0 interrupts
  CAN_RX1_Handler,				// CAN RX1 interrupt
  CAN_SCE_Handler,				// CAN SCE interrupt
  EXTI9_5_Handler,				// EXTI Line[9:5] interrupts
  TIM1_BRK_TIM15_Handler,		// TIM1 break interrupt
  TIM1_UP_TIM16_Handler,		// TIM1 Update interrupt
  TIM1_TRG_COM_TIM17_Handler, 	// TIM1 Trigger and Communication interrupts
  TIM1_CC_Handler,				// TIM1 Capture Compare interrupt
  TIM2_Handler,					// TIM2 global interrupt
  TIM3_Handler,					// TIM3 global interrupt
  TIM4_Handler,					// TIM4 global interrupt
  I2C1_EV_Handler,				// I2C1 event interrupt
  I2C1_ER_Handler,				// I2C1 error interrupt
  I2C2_EV_Handler,				// I2C2 event interrupt
  I2C2_ER_Handler,				// I2C2 error interrupt
  SPI1_Handler,					// SPI1 global interrupt
  SPI2_Handler,					// SPI2 global interrupt
  USART1_Handler,				// USART1 global interrupt
  USART2_Handler,				// USART2 global interrupt
  USART3_Handler,				// USART3 global interrupt
  EXTI15_10_Handler,			// EXTI Line[15:10] interrupts
  RTCAlarm_Handler,				// RTC alarm through EXTI line interrupt
  USB_Wakeup_Handler,			// USB wakeup from suspend through EXTI line interrupt
  TIM8_BRK_Handler,				// TIM8 Break interrupt
  TIM8_UP_Handler,				// TIM8 Update interrupt
  TIM8_TRG_COM_Handler,			// TIM8 Trigger and communication interrupt
  TIM8_CC_Handler,				// TIM8 Capture Compare interrupt
  ADC3_Handler,					// ADC3 global interrupt
  FSMC_Handler,					// FSMC global interrupt
  SDIO_Handler,					// SDIO global interrupt
  TIM5_Handler,					// TIM5 global interrupt
  SPI3_Handler,					// SPI3 global interrupt
  UART4_Handler,				// UART4 global interrupt
  UART5_Handler,				// UART5 global interrupt
  TIM6_DAC_Handler,				// TIM6 global interrupt
  TIM7_Handler,					// TIM7 global interrupt
  DMA2_Channel1_Handler,		// DMA2 Channel1 global interrupt
  DMA2_Channel2_Handler,		// DMA2 Channel2 global interrupt
  DMA2_Channel3_Handler,		// DMA2 Channel3 global interrupt
  DMA2_Channel4_5_Handler 		// DMA2 Channel4 and DMA2 Channel5 global interrupts
                            /* Interrupts 60 .. 223 are left out */
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
  SystemInit();                             /* CMSIS System Initialization */
  __PROGRAM_START();                        /* Enter PreMain (C library entry point) */
}


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/*----------------------------------------------------------------------------
  Hard Fault Handler
 *----------------------------------------------------------------------------*/
void HardFault_Handler(void)
{
  while(1);
}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#endif
