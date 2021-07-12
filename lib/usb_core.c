/*
 * Part of USB HID gamepad STM32 based solution.
 * Here are all USB low-level functions.
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

#include "usb_device_regs.h"
#include "usb_core.h"
#include "../libopencm3/include/libopencm3/cm3/nvic.h"

void epTxStatusSet(int ep, uint16_t status);
void epRxStatusSet(int ep, uint16_t status);
void usbClockInit(void);
void usbReset(void);


void usbClockInit()
{
    RCC_AHBENR |= RCC_AHBENR_OTGFSEN;
    // usb on
    USB_CNTR_REG &= ~PDWN;
    rough_delay_us(1);
    USB_ISTR_REG = 0;
    // reset usb
    USB_CNTR_REG &= ~FRES;
}

void usbReset()
{
    USB_DADDR_REG = USB_DADDR_EF | 0x00;

}

void usbHidEndpInit()
{
    // buffer config
    USB_BTABLE    = USB_TABLE_ADDR;
    // endpoint 0 rx/tx buffers
    USB_ADDR0_TX  = USB_TABLE_END & ADDR_TX_MASK;
    USB_ADDR0_RX  = (((uint16_t)*USB_ADDR0_TX) + EP0_BUFFER_SIZE) & ADDR_TX_MASK;
    USB_COUNT0_RX = BL_SIZE_32B | \
                    (((EP0_BUFFER_SIZE/32) << NUM_BLOCK_OFFS) & NUM_BLOCK_MASK);
    // endp
    USB_EP0R = EP_TYPE_CONTROL | (0 & EA_MASK);
    epPrors[0].isHalt = 0;
}





void usbCoreInit()
{

    // all nterupts are enabled
    USB_CNTR_REG |= CTRM | PMAOVRM | WKUPM | SUSPM | RESETM;
    nvic_enable_irq(NVIC_USB_HP_CAN_TX_IRQ);
    nvic_set_priority(NVIC_USB_HP_CAN_TX_IRQ, 0x00);
}

void epHaltUpdate()
{

}

void usbCore()
{
    if(USB_ISTR & ERR) {

    }
}

void setAddr(uint8_t addr)
{
    USB_DADDR_REG &= ~ADD_MASK;
    USB_DADDR_REG |= addr & ADD_MASK;
    usbProp.deviceStaste = ADDRESS;
}

void controlEpStall()
{
    epRxStatusSet(0, STAT_RX_STALL);
    epTxStatusSet(0, STAT_TX_STALL);
}

int epHaltSet(int ep)
{
    if( (ep == 0) || (ep >= NUM_OF_EP) ) {
        return -1;
    }
    usbProp.epProp[ep].isHalt = 1;
    epRxStatusSet(ep, STAT_RX_STALL);
    epTxStatusSet(ep, STAT_TX_STALL);
    return 0;
}

int epHaltClear(int ep)
{
    if( (ep == 0) || (ep >= NUM_OF_EP) ) {
        return -1;
    }
    usbProp.epProp[ep].isHalt = 0;
    epRxStatusSet(ep, STAT_RX_NAK);
    epTxStatusSet(ep, STAT_TX_NAK);
    return 0;
}


// work with status bits
void epTxStatusSet(int ep, uint16_t status)
{
    // toggle bit 0, if it's nesessary
    if( (USB_EP0R & (1<<STAT_TX_OFFS)) != (status & (1<<STAT_TX_OFFS)) ) {
        USB_EPNR(ep) = (1<<STAT_TX_OFFS) | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
    // toggle bit 1
    if( (USB_EP1R & (1<<(STAT_TX_OFFS+1))) != (status & (1<<(STAT_TX_OFFS+1))) ) {
        USB_EPNR(ep) = (1<<(STAT_TX_OFFS+1)) | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
}

void epRxStatusSet(int ep, uint16_t status)
{
    // toggle bit 0
    if( (USB_EP0R & (1<<STAT_RX_OFFS)) != (status & (1<<STAT_RX_OFFS)) ) {
        USB_EPNR(ep) = (1<<STAT_RX_OFFS) | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
    // toggle bit 1
    if( (USB_EP1R & (1<<(STAT_RX_OFFS+1))) != (status & (1<<(STAT_RX_OFFS+1))) ) {
        USB_EPNR(ep) = (1<<(STAT_RX_OFFS+1)) | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
}
