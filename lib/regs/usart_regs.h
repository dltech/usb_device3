#ifndef H_USART_REGS
#define H_USART_REGS
/*
 * Part of Belkin STM32 HAL, USART registers of STMF103 MCU.
 *
 * Copyright 2022 Mikhail Belkin <dltech174@gmail.com>
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

/* Status register */
#define USART1_SR   MMIO32(USART1_BASE + 0x00)
#define USART2_SR   MMIO32(USART2_BASE + 0x00)
#define USART3_SR   MMIO32(USART3_BASE + 0x00)
// CTS flag
#define CTS  0x0200
// LIN break detection flag
#define LBD  0x0100
// Transmit data register empty
#define TXE  0x0080
// Transmission complete
#define TC   0x0040
// Read data register not empty
#define RXNE 0x0020
// IDLE line detected
#define IDLE 0x0010
// Overrun error
#define ORE  0x0008
// Noise error flag
#define NE   0x0004
// Framing error
#define FE   0x0002
// Parity error
#define PE   0x0001

/* Data register */
#define USART1_DR   MMIO32(USART1_BASE + 0x04)
#define USART2_DR   MMIO32(USART2_BASE + 0x04)
#define USART3_DR   MMIO32(USART3_BASE + 0x04)

/* Baud rate register */
#define USART1_BRR  MMIO32(USART1_BASE + 0x08)
#define USART2_BRR  MMIO32(USART2_BASE + 0x08)
#define USART3_BRR  MMIO32(USART3_BASE + 0x08)
// mantissa of USARTDIV
#define DIV_M_SHIFT 4
// fraction of USARTDIV
#define DIV_F_MASK  0x000f

/* Control register 1 */
#define USART1_CR1  MMIO32(USART1_BASE + 0x0c)
#define USART2_CR1  MMIO32(USART2_BASE + 0x0c)
#define USART3_CR1  MMIO32(USART3_BASE + 0x0c)
// USART enable
#define UE      0x2000
// Word length
#define M       0x1000
// Wakeup method
#define WAKE    0x0800
// Parity control enable
#define PCE     0x0400
// Parity selection
#define PS      0x0200
// PE interrupt enable
#define PEIE    0x0100
// TXE interrupt enable
#define TXEIE   0x0080
// Transmission complete interrupt enable
#define UTCIE    0x0040
// RXNE interrupt enable
#define RXNEIE  0x0020
// IDLE interrupt enable
#define IDLEIE  0x0010
// Transmitter enable
#define TE      0x0008
// Receiver enable
#define RE      0x0004
// Receiver wakeup
#define RWU     0x0002
// Send break
#define SBK     0x0001

/* Control register 2 */
#define USART1_CR2  MMIO32(USART1_BASE + 0x10)
#define USART2_CR2  MMIO32(USART2_BASE + 0x10)
#define USART3_CR2  MMIO32(USART3_BASE + 0x10)
// LIN mode enable
#define LINEN   0x4000
// STOP bits
#define STOP_1   0x0000
#define STOP_0P5 0x1000
#define STOP_1P5 0x3000
#define STOP_2   0x2000
#define STOP_MSK 0x3000
// Clock enable
#define CLKEN   0x0800
// Clock polarity
#define CPOL    0x0400
// Clock phase
#define CPHA    0x0200
// Last bit clock pulse
#define LBCL    0x0100
// LIN break detection interrupt enable
#define LBDIE   0x0020
// lin break detection length
#define LBDL    0x0010
// Address of the USART node
#define ADD_MSK 0x0007

/* Control register 3 */
#define USART1_CR3  MMIO32(USART1_BASE + 0x14)
#define USART2_CR3  MMIO32(USART2_BASE + 0x14)
#define USART3_CR3  MMIO32(USART3_BASE + 0x14)
// CTS interrupt enable
#define CTSIE   0x0400
// CTS enable
#define CTSE    0x0200
// RTS enable
#define RTSE    0x0100
// DMA enable transmitter
#define DMAT    0x0080
// DMA enable receiver
#define DMAR    0x0040
// Smartcard mode enable
#define SCEN    0x0020
// Smartcard NACK enable
#define NACK    0x0010
// Half-duplex selection
#define HDSEL   0x0008
// IrDA low-power
#define IRLP    0x0004
// IrDA mode enable
#define IREN    0x0002
// Error interrupt enable
#define EIE     0x0001

/* Guard time and prescaler register */
#define USART1_GTPR MMIO32(USART1_BASE + 0x18)
#define USART2_GTPR MMIO32(USART2_BASE + 0x18)
#define USART3_GTPR MMIO32(USART3_BASE + 0x18)
// Guard time value
#define GT_SHIFT    8
// Prescaler value
#define GT_PSC_MSK  0xff

#define USART_M(baud)   SYSTEM_CLOCK/16/baud
#define USART_FR(baud)  (((((((SYSTEM_CLOCK/16)*100)/baud)%100)*16)/100)&DIV_F_MASK)
#define USART_BR_CALC(baud)  ((USART_M(baud)<<DIV_M_SHIFT)+USART_FR(baud))

#endif
