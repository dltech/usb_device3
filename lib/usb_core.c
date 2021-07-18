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

#include "mysys.h"
#include "usb_device_regs.h"
#include "usb_core.h"
#include "gamepad_port.h"
#include "../libopencm3/include/libopencm3/cm3/nvic.h"

// init functions
// basic init
void usbClockInit(void);
void usbItInit(void);
// endpoints init
void usbHidEndpInit(void);
void usbReportEndpInit(void);
// usb states
// peripherial states
void usbReset(void);
void usbSuspend(void);
void usbWakeup(void);
// the core
void ctrF(void);
void controlEpHandler(void);
void interruptEpHandler(void);
// ep ass-tricky register, control functions
void epTxStatusSet(int ep, uint16_t status);
void epRxStatusSet(int ep, uint16_t status);
void controlDtogInit(int nep);
void defaultDtogInit(void);

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

void usbItInit()
{
    USB_CNTR_REG |= CTRM | WKUPM | SUSPM | RESETM;
    nvic_enable_irq(NVIC_USB_HP_CAN_TX_IRQ);
    nvic_set_priority(NVIC_USB_HP_CAN_TX_IRQ, 0x00);
}

void usbCoreInit()
{
    usbClockInit();
    usbHidEndpInit();
    usbReportEndpInit();
    gamepadPar.deviceStaste = DEFAULT;
}

void usbHidEndpInit()
{
    // buffer init
    USB_BTABLE    = USB_TABLE_ADDR;
    // endpoint 0 rx/tx buffers
    USB_ADDR0_TX  = USB_TABLE_END & ADDR_TX_MASK;
    USB_ADDR0_RX  = (((uint16_t)USB_ADDR0_TX) + EP0_BUFFER_SIZE) & ADDR_RX_MASK;
    USB_COUNT0_RX = BL_SIZE_32B | \
                    (((EP0_BUFFER_SIZE/32) << NUM_BLOCK_OFFS) & NUM_BLOCK_MASK);
    // endpoint 0 address 0, type control endpoint
    USB_EP0R = EP_TYPE_CONTROL | (0 & EA_MASK);
    epPrors[0].isHalt = 0;
    controlDtogInit();
    controlEpNak();
}

void usbReportEndpInit()
{
    // endpoint 1 tx buffer
    USB_ADDR1_TX  = (USB_TABLE_END + EP0_BUFFER_SIZE) & ADDR_TX_MASK;
    // endpoint 1 address 1, type interrupt endpoint
    USB_EP1R = EP_TYPE_INTERRUPT | (1 & EA_MASK);
    epRxStatusSet(1, STAT_RX_DISABLED);
    epRxStatusSet(1, STAT_TX_NAK);
    defaultDtogInit(1);
    epPrors[1].isHalt = 0;
}

void usbReset()
{
    gamepadPar.deviceStaste = RESET;
    USB_DADDR_REG = USB_DADDR_EF | 0x00;
    USB_CNTR_REG &= ~(RESETM);
    USB_CNTR_REG |= FRES;
    // clear all endpoint related registers
    for(int i=0 ; i<NUM_OF_EP ; ++i) {
        epTxStatusSet(i, STAT_TX_DISABLED);
        epRxStatusSet(i, STAT_RX_DISABLED);
        USB_EPNR(i) = 0;
        USB_ADDRN_TX(i) = 0;
        USB_COUNTN_TX(i) = 0;
        USB_ADDRN_RX(i) = 0;
        USB_COUNTN_RX(i) = 0;
    }
    USB_DADDR_REG = 0;
    USB_CNTR_REG = 0;
    USB_ISTR = 0;
    rough_delay_us(100);
    // init again
    usbHidEndpInit();
    usbReportEndpInit();
    usbItInit();
    gamepadPar.deviceStaste = DEFAULT;
}

// I don't know how it works. It's just the shadow of MCD team code.
void usbSuspend()
{
    gamepadPar.isSusp = 1;
    // instanteous reset
    // unmask interrupts
    USB_CNTR_REG &= ~((uint32_t)(RESETM));
    // and reset
    USB_CNTR_REG |= FRES;
    USB_CNTR_REG &= ~((uint32_t)(FRES));
    // wait this reaction
    uint32_t timeout = 1e5;
    while( ((USB_ISTR & RESET) == 0) && (--timeout < 0) );
    USB_ISTR = 0;
    // after which we need to restore endp registers only (why endpoints only?)
    USB_EP0R = EP_TYPE_CONTROL | (0 & EA_MASK);
    USB_EP1R = EP_TYPE_INTERRUPT | (1 & EA_MASK);
    // then we may enter suspend mode safely
    USB_CNTR_REG |= FSUSP;
    // USB low power mode and slow clock
    USB_CNTR_REG |= LP_MODE;
    suspSysClk();
}

void usbWakeup()
{
    gamepadPar.isSusp = 0;
    sysClk();
    USB_CNTR_REG &= ~((uint32_t)(LP_MODE | FSUSP));
    USB_ISTR = 0;
    USB_CNTR_REG |= RESETM;
}

void ctrF()
{
    switch(USB_ISTR & EP_ID_MASK)
    {
        case 0:
            controlEpHandler();
            break;
        case 1:
            interruptEpHandler();
            break;
    }
}

void controlEpHandler()
{

}

void interruptEpHandler()
{

}

void usbCore()
{
    if( ((USB_ISTR & CTR) != 0) && isRequest() ) {
        reqHandler();
    }
    if( ((USB_ISTR & CTR) != 0) && (isRequest() == 0) ) {
        ctrF();
    }
    if(USB_ISTR & WKUPM) {
        usbWkup();
    }
    if(USB_ISTR & SUSPM) {
        usbSusp();
    }
    if(USB_ISTR & RESET) {
        usbReset();
    }
    USB_ISTR = 0;
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

// core functions which called by requests
void setAddr(uint8_t addr)
{
    USB_DADDR_REG &= ~ADD_MASK;
    USB_DADDR_REG |= addr & ADD_MASK;
    usbProp.deviceStaste = ADDRESS;
}

void controlDtogInit()
{
    // set dtog_tx = 1, dtog_rx = 0
    if( (USB_EP0R & DTOG_TX) == 0 ) {
        USB_EPNR0 = DTOG_TX | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
    if( (USB_EP0R & DTOG_RX) != 0 ) {
        USB_EPNR0 = DTOG_RX | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
}

void defaultDtogInit(int nep)
{
    // set dtog_tx = 0, dtog_rx = 0
    if( (USB_EPNR(nep) & DTOG_TX) != 0 ) {
        USB_EPNR(nep) = DTOG_TX | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
    if( (USB_EPNR(nep) & DTOG_RX) != 0 ) {
        USB_EPNR(nep) = DTOG_RX | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
}

void controlEpStall()
{
    epRxStatusSet(0, STAT_RX_STALL);
    epTxStatusSet(0, STAT_TX_STALL);
}

void controlEpNak()
{
    epRxStatusSet(0, STAT_RX_NAK);
    epTxStatusSet(0, STAT_TX_NAK);
}

int epHaltSet(int ep)
{
    if( (ep == 0) || (ep >= NUM_OF_EP) ) return -1;
    usbProp.epProp[ep].isHalt = 1;
    epRxStatusSet(ep, STAT_RX_STALL);
    epTxStatusSet(ep, STAT_TX_STALL);
    return 0;
}

int epHaltClear(int ep)
{
    if( (ep == 0) || (ep >= NUM_OF_EP) ) return -1;
    usbProp.epProp[ep].isHalt = 0;
    epRxStatusSet(ep, STAT_RX_NAK);
    epTxStatusSet(ep, STAT_TX_NAK);
    return 0;
}
