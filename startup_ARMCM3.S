/**************************************************************************//**
 * @file     startup_ARMCM3.S
 * @brief    CMSIS-Core(M) Device Startup File for Cortex-M3 Device
 * @version  V2.2.0
 * @date     26. May 2021
 ******************************************************************************/
/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
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

                .syntax  unified
                .arch    armv7-m

                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
__Vectors:
                .long    __StackTop                         /*     Top of Stack */
                .long    Reset_Handler                      /*     Reset Handler */
                .long    NMI_Handler                        /* -14 NMI Handler */
                .long    HardFault_Handler                  /* -13 Hard Fault Handler */
                .long    MemManage_Handler                  /* -12 MPU Fault Handler */
                .long    BusFault_Handler                   /* -11 Bus Fault Handler */
                .long    UsageFault_Handler                 /* -10 Usage Fault Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SVC_Handler                        /*  -5 SVC Handler */
                .long    DebugMon_Handler                   /*  -4 Debug Monitor Handler */
                .long    0                                  /*     Reserved */
                .long    PendSV_Handler                     /*  -2 PendSV Handler */
                .long    SysTick_Handler                    /*  -1 SysTick Handler */
                /* STM32 Related Interrupts */
                .long  WWDG_Handler
                .long  PVD_Handler
                .long  TAMPER_Handler
                .long  RTC_Handler
                .long  FLASH_Handler
                .long  RCC_Handler
                .long  EXTI0_Handler
                .long  EXTI1_Handler
                .long  EXTI2_Handler
                .long  EXTI3_Handler
                .long  EXTI4_Handler
                .long  DMA1_Channel1_Handler
                .long  DMA1_Channel2_Handler
                .long  DMA1_Channel3_Handler
                .long  DMA1_Channel4_Handler
                .long  DMA1_Channel5_Handler
                .long  DMA1_Channel6_Handler
                .long  DMA1_Channel7_Handler
                .long  ADC_Handler
                .long  usb_hp_can_tx_Handler
                .long  usb_hp_can_rx_Handler
                .long  CAN_RX1_Handler
                .long  CAN_SCE_Handler
                .long  EXTI9_5_Handler
                .long  TIM1_BRK_TIM15_Handler
                .long  TIM1_UP_TIM16_Handler
                .long  TIM1_TRG_COM_TIM17_Handler
                .long  TIM1_CC_Handler
                .long  TIM2_Handler
                .long  TIM3_Handler
                .long  TIM4_Handler
                .long  I2C1_EV_Handler
                .long  I2C1_ER_Handler
                .long  I2C2_EV_Handler
                .long  I2C2_ER_Handler
                .long  SPI1_Handler
                .long  SPI2_Handler
                .long  USART1_Handler
                .long  USART2_Handler
                .long  USART3_Handler
                .long  EXTI15_10_Handler
                .long  RTCAlarm_Handler
                .long  USB_Wakeup_Handler
                .long  TIM8_BRK_Handler
                .long  TIM8_UP_Handler
                .long  TIM8_TRG_COM_Handler
                .long  TIM8_CC_Handler
                .long  ADC3_Handler
                .long  FSMC_Handler
                .long  SDIO_Handler
                .long  TIM5_Handler
                .long  SPI3_Handler
                .long  UART4_Handler
                .long  UART5_Handler
                .long  TIM6_DAC_Handler
                .long  TIM7_Handler
                .lond  DMA2_Channel1_Handler
                .long  DMA2_Channel2_Handler
                .long  DMA2_Channel3_Handler
                .long  DMA2_Channel4_5_Handler
                .space   (155 * 4)       /* Interrupts 59 .. 224 are left out */
__Vectors_End:
                .equ     __Vectors_Size, __Vectors_End - __Vectors
                .size    __Vectors, . - __Vectors


                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
                .fnstart
Reset_Handler:
                bl       SystemInit

                ldr      r4, =__copy_table_start__
                ldr      r5, =__copy_table_end__

.L_loop0:
                cmp      r4, r5
                bge      .L_loop0_done
                ldr      r1, [r4]                /* source address */
                ldr      r2, [r4, #4]            /* destination address */
                ldr      r3, [r4, #8]            /* word count */
                lsls     r3, r3, #2              /* byte count */

.L_loop0_0:
                subs     r3, #4                  /* decrement byte count */
                ittt     ge
                ldrge    r0, [r1, r3]
                strge    r0, [r2, r3]
                bge      .L_loop0_0

                adds     r4, #12
                b        .L_loop0
.L_loop0_done:

                ldr      r3, =__zero_table_start__
                ldr      r4, =__zero_table_end__

.L_loop2:
                cmp      r3, r4
                bge      .L_loop2_done
                ldr      r1, [r3]                /* destination address */
                ldr      r2, [r3, #4]            /* word count */
                lsls     r2, r2, #2              /* byte count */
                movs     r0, 0

.L_loop2_0:
                subs     r2, #4                  /* decrement byte count */
                itt      ge
                strge    r0, [r1, r2]
                bge      .L_loop2_0

                adds     r3, #8
                b        .L_loop2
.L_loop2_done:

                bl       _start

                .fnend
                .size    Reset_Handler, . - Reset_Handler

/* The default macro is not used for HardFault_Handler
 * because this results in a poor debug illusion.
 */
                .thumb_func
                .type    HardFault_Handler, %function
                .weak    HardFault_Handler
                .fnstart
HardFault_Handler:
                b        .
                .fnend
                .size    HardFault_Handler, . - HardFault_Handler

                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
                .fnstart
Default_Handler:
                b        .
                .fnend
                .size    Default_Handler, . - Default_Handler

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm


/* Default exception/interrupt handler */

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  MemManage_Handler
                Set_Default_Handler  BusFault_Handler
                Set_Default_Handler  UsageFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  DebugMon_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  WWDG_Handler
                Set_Default_Handler  PVD_Handler
                Set_Default_Handler  TAMPER_Handler
                Set_Default_Handler  RTC_Handler
                Set_Default_Handler  FLASH_Handler
                Set_Default_Handler  RCC_Handler
                Set_Default_Handler  EXTI0_Handler
                Set_Default_Handler  EXTI1_Handler
                Set_Default_Handler  EXTI2_Handler
                Set_Default_Handler  EXTI3_Handler
                Set_Default_Handler  EXTI4_Handler
                Set_Default_Handler  DMA1_Channel1_Handler
                Set_Default_Handler  DMA1_Channel2_Handler
                Set_Default_Handler  DMA1_Channel3_Handler
                Set_Default_Handler  DMA1_Channel4_Handler
                Set_Default_Handler  DMA1_Channel5_Handler
                Set_Default_Handler  DMA1_Channel6_Handler
                Set_Default_Handler  DMA1_Channel7_Handler
                Set_Default_Handler  ADC_Handler
                Set_Default_Handler  usb_hp_can_tx_Handler
                Set_Default_Handler  usb_hp_can_rx_Handler
                Set_Default_Handler  CAN_RX1_Handler
                Set_Default_Handler  CAN_SCE_Handler
                Set_Default_Handler  EXTI9_5_Handler
                Set_Default_Handler  TIM1_BRK_TIM15_Handler
                Set_Default_Handler  TIM1_UP_TIM16_Handler
                Set_Default_Handler  TIM1_TRG_COM_TIM17_Handler
                Set_Default_Handler  TIM1_CC_Handler
                Set_Default_Handler  TIM2_Handler
                Set_Default_Handler  TIM3_Handler
                Set_Default_Handler  TIM4_Handler
                Set_Default_Handler  I2C1_EV_Handler
                Set_Default_Handler  I2C1_ER_Handler
                Set_Default_Handler  I2C2_EV_Handler
                Set_Default_Handler  I2C2_ER_Handler
                Set_Default_Handler  SPI1_Handler
                Set_Default_Handler  SPI2_Handler
                Set_Default_Handler  USART1_Handler
                Set_Default_Handler  USART2_Handler
                Set_Default_Handler  USART3_Handler
                Set_Default_Handler  EXTI15_10_Handler
                Set_Default_Handler  RTCAlarm_Handler
                Set_Default_Handler  USB_Wakeup_Handler
                Set_Default_Handler  TIM8_BRK_Handler
                Set_Default_Handler  TIM8_UP_Handler
                Set_Default_Handler  TIM8_TRG_COM_Handler
                Set_Default_Handler  TIM8_CC_Handler
                Set_Default_Handler  ADC3_Handler
                Set_Default_Handler  FSMC_Handler
                Set_Default_Handler  SDIO_Handler
                Set_Default_Handler  TIM5_Handler
                Set_Default_Handler  SPI3_Handler
                Set_Default_Handler  UART4_Handler
                Set_Default_Handler  UART5_Handler
                Set_Default_Handler  TIM6_DAC_Handler
                Set_Default_Handler  TIM7_Handler
                Set_Default_Handler  DMA2_Channel1_Handler
                Set_Default_Handler  DMA2_Channel2_Handler
                Set_Default_Handler  DMA2_Channel3_Handler
                Set_Default_Handler  DMA2_Channel4_5_Handler

                .end
