#ifndef H_USB_DEVICE_REGS
#define H_USB_DEVICE_REGS
/*
 * Part of USB HID gamepad STM32 based solution.
 * USB Device registers of STMF103 MCU only.
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
#include "inttypes.h"

/* USB Control register */
#define USB_CNTR	(MMIO32(USB_DEVICE_BASE + 0x40))
// correct transfer interrupt mask (rw)
#define CTRM                0x8000
// packet memory area over/underrun interrupt mask (rw)
#define PMAOVRM             0x4000
// error interrupt mask (rw)
#define ERRM                0x2000
// wakeup interrupt mask (rw)
#define WKUPM               0x1000
// suspend mode interrupt mask (rw)
#define SUSPM               0x0800
// USB reset interrupt mask (rw)
#define RESETM              0x0400
// start of frame interrupt mask (rw)
#define SOFM                0x0200
// expected start of frame interrupt mask (rw)
#define ESOFM               0x0100
// resume request (rw)
#define RESUME              0x0010
// force suspend (rw)
#define FSUSP               0x0008
// low-power mode (rw)
#define LP_MODE             0x0004
// power down (rw)
#define PDWN                0x0002
// force USB reset (rw)
#define FRES                0x0001

/* USB Interrupt status register */
#define USB_ISTR	(MMIO32(USB_DEVICE_BASE + 0x44))
// correct transfer (r)
#define CTR                 0x8000
// packet memory area over/underrun (rc_w0)
#define PMAOVR              0x4000
// error (rc_w0)
#define ERR                 0x2000
// wakeup (rc_w0)
#define WKUP                0x1000
// suspend mode request (rc_w0)
#define SUSP                0x0800
// USB reset request (rc_w0)
#define RESET               0x0400
// start of frame (rc_w0)
#define SOF                 0x0200
// expected start of frame (rc_w0)
#define ESOF                0x0100
// direction of transaction (r)
#define DIR                 0x0010
// endpoint identifier (r)
#define EP_ID_MASK          0x000f
#define EP_ID_OFFS          0

/* USB Frame number register */
#define USB_FNR		(MMIO32(USB_DEVICE_BASE + 0x48))
// receive data + line status (r)
#define RXDP                0x8000
// receive data - line status (r)
#define RXDM                0x4000
// locked (r)
#define LCK                 0x2000
// lost SOF (r)
#define LSOF_MASK           0x1800
#define LSOF_OFFS           11
// frame number (r)
#define FN_MASK             0x007f
#define FN_OFFS             0

/* USB Device address register */
#define USB_DADDR	(MMIO32(USB_DEVICE_BASE + 0x4C))
// enable function (rw)
#define EF                  0x0080
// device address (rw)
#define ADD_MASK            0x007f
#define ADD_OFFS            0

/* USB Buffer table address register */
#define USB_BTABLE  (MMIO32(USB_DEVICE_BASE + 0x50))
// buffer table (rw)
#define BTABLE_MASK         0xfff8

/* USB endpoint registers */
#define USB_EP0R    (MMIO32(USB_DEVICE_BASE + 0x00))
#define USB_EP1R	(MMIO32(USB_DEVICE_BASE + 0x04))
#define USB_EP2R	(MMIO32(USB_DEVICE_BASE + 0x08))
#define USB_EP3R	(MMIO32(USB_DEVICE_BASE + 0x0c))
#define USB_EP4R	(MMIO32(USB_DEVICE_BASE + 0x10))
#define USB_EP5R	(MMIO32(USB_DEVICE_BASE + 0x14))
#define USB_EP6R	(MMIO32(USB_DEVICE_BASE + 0x18))
#define USB_EP7R	(MMIO32(USB_DEVICE_BASE + 0x1c))
#define USB_EPNR(n) (MMIO32(USB_DEVICE_BASE + 0x04*n))
// correct transfer for reception (rc_w0)
#define CTR_RX              0x8000
// data toggle for reception transfers (t)
#define DTOG_RX             0x4000
// status bits for reception transfers (t)
#define STAT_RX_DISABLED    0x0000
#define STAT_RX_STALL       0x1000
#define STAT_RX_NAK         0x2000
#define STAT_RX_VALID       0x3000
#define STAT_RX_OFFS        12
#define STAT_RX_MASK        0x3000
// setup transaction completed (r)
#define SETUP               0x0800
// endpoint type (rw)
#define EP_TYPE_BULK        0x0000
#define EP_TYPE_CONTROL     0x0200
#define EP_TYPE_ISO         0x0400
#define EP_TYPE_INTERRUPT   0x0600
// endpoint kind (rw)
#define EP_KIND             0x0100
// correct transfer for transmission (rc_w0)
#define CTR_TX              0x0080
// data toggle for transmission transfers (t)
#define DTOG_TX             0x0040
// status bits for transmission transfers (t)
#define STAT_TX_DISABLED    0x0000
#define STAT_TX_STALL       0x0010
#define STAT_TX_NAK         0x0020
#define STAT_TX_VALID       0x0030
#define STAT_TX_OFFS        4
#define STAT_TX_MASK        0x0030
// endpoint address (rw)
#define EA_MASK             0x000f
#define EA_OFFS             0
// mask for safe modyfying
#define USB_EP_RCWO_MASK    0x8080
#define USB_EP_RESET_CTR_MASK 0x060f

/* USB RAM table */
/* Transmission buffer address 0 */
#define USB_ADDR0_TX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x00)*2)
// 16bit aligned addr (rw)
#define ADDR_TX_MASK   0xfffe

/* Transmission byte count 0 */
#define USB_COUNT0_TX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x02)*2)
// transmission byte count (rw)
#define COUNT_TX_MASK  0x03ff

/* Reception buffer address 0 */
#define USB_ADDR0_RX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x04)*2)
#define ADDR_RX_MASK   0xfffe

/* Reception byte count 0 */
#define USB_COUNT0_RX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x06)*2)
// block size (rw)
#define BL_SIZE_2B      0x0000
#define BL_SIZE_32B     0x8000
// number of blocks (rw)
#define NUM_BLOCK_MASK  0x7c00
#define NUM_BLOCK_OFFS  10
// reception byte count (r)
#define COUNT_RX_MASK   0x03ff

// addresses of endpoint 1
#define USB_ADDR1_TX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x08)*2)
#define USB_COUNT1_TX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x0a)*2)
#define USB_ADDR1_RX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x0c)*2)
#define USB_COUNT1_RX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x0e)*2)
// addresses of endpoint 2
#define USB_ADDR2_TX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x10)*2)
#define USB_COUNT2_TX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x12)*2)
#define USB_ADDR2_RX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x14)*2)
#define USB_COUNT2_RX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x16)*2)
// addresses of endpoint 3
#define USB_ADDR3_TX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x18)*2)
#define USB_COUNT3_TX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x1a)*2)
#define USB_ADDR3_RX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x1c)*2)
#define USB_COUNT3_RX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x1e)*2)
// addresses of endpoint 4
#define USB_ADDR4_TX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x20)*2)
#define USB_COUNT4_TX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x22)*2)
#define USB_ADDR4_RX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x24)*2)
#define USB_COUNT4_RX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x26)*2)
// addresses of endpoint 5
#define USB_ADDR5_TX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x28)*2)
#define USB_COUNT5_TX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x2a)*2)
#define USB_ADDR5_RX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x2c)*2)
#define USB_COUNT5_RX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x2e)*2)
// addresses of endpoint 6
#define USB_ADDR6_TX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x30)*2)
#define USB_COUNT6_TX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x32)*2)
#define USB_ADDR6_RX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x34)*2)
#define USB_COUNT6_RX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x36)*2)
// addresses of endpoint 7
#define USB_ADDR7_TX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x38)*2)
#define USB_COUNT7_TX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x3a)*2)
#define USB_ADDR7_RX    MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x3c)*2)
#define USB_COUNT7_RX   MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x3e)*2)
// addresses of endpoint n
#define USB_ADDRN_TX(n) MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x00 + 0x08*n)*2)
#define USB_COUNTN_TX(n) MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x02 + 0x08*n)*2)
#define USB_ADDRN_RX(n) MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x04 + 0x08*n)*2)
#define USB_COUNTN_RX(n) MMIO32(USB_CAN_SRAM_BASE + ((uint16_t)USB_BTABLE + 0x06 + 0x08*n)*2)

// ep ass-tricky register, control functions
void epTxStatusSet(int ep, uint16_t status);
void epRxStatusSet(int ep, uint16_t status);
void controlDtogInit(void);
void defaultDtogInit(int nep);

#endif
