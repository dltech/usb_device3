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

#include "../libopencm3/include/libopencm3/cm3/nvic.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "mysys.h"
#include "usb_device_regs.h"
#include "usb_st_req.h"
#include "usb_hid.h"
#include "usb_core.h"

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
void usbSusp(void);
void usbWkup(void);
// the core
void ctrF(void);
void controlEpHandler(void);
void interruptEpHandler(void);
// request handler
void reqCopy(requestTyp *request);
int isRequest(void);
void reqHandler(void);
// ep ass-tricky register, control functions
void epTxStatusSet(int ep, uint16_t status);
void epRxStatusSet(int ep, uint16_t status);
void controlDtogInit(void);
void defaultDtogInit(int nep);

void usbClockInit()
{
    RCC_AHBENR |= RCC_AHBENR_OTGFSEN;
    // usb on
    USB_CNTR &= ~PDWN;
    rough_delay_us(1);
    USB_ISTR = 0;
    // reset usb
    USB_CNTR &= ~FRES;
}

void usbItInit()
{
    USB_CNTR |= CTRM | WKUPM | SUSPM | RESETM;
    nvic_enable_irq(NVIC_USB_HP_CAN_TX_IRQ);
    nvic_set_priority(NVIC_USB_HP_CAN_TX_IRQ, 0x00);
}

void usbCoreInit()
{
    usbClockInit();
    usbHidEndpInit();
    usbReportEndpInit();
    usbProp.deviceState = DEFAULT;
    usbProp.isSusp = 0;
    usbProp.deviceState = DEFAULT;
    usbProp.reportDuration = 0;
}

void usbHidEndpInit()
{
    // buffer init
    USB_BTABLE    = USB_TABLE_ADDR;
    // endpoint 0 rx/tx buffers
    USB_ADDR0_TX  = EP0_TX_START;
    USB_ADDR0_RX  = EP0_RX_START;
    USB_COUNT0_RX = BL_SIZE_32B | \
                    (((EP0_BUFFER_SIZE/32) << NUM_BLOCK_OFFS) & NUM_BLOCK_MASK);
    // endpoint 0 address 0, type control endpoint
    USB_EP0R = EP_TYPE_CONTROL | (0 & EA_MASK);
    controlDtogInit();
    epRxStatusSet(0, STAT_RX_NAK);
    epRxStatusSet(0, STAT_TX_NAK);
    usbProp.epProps[0].isHalt = 0;
}

void usbReportEndpInit()
{
    // endpoint 1 tx buffer
    USB_ADDR1_TX  = EP1_TX_START;
    // endpoint 1 address 1, type interrupt endpoint
    USB_EP1R = EP_TYPE_INTERRUPT | (1 & EA_MASK);
    defaultDtogInit(1);
    epRxStatusSet(1, STAT_RX_DISABLED);
    epRxStatusSet(1, STAT_TX_NAK);
    usbProp.epProps[1].isHalt = 0;
}

void usbReset()
{
    usbProp.deviceState = DEV_RESET;
    USB_DADDR = EF | 0x00;
    USB_CNTR &= ~(RESETM);
    USB_CNTR |= FRES;
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
    USB_DADDR = 0;
    USB_CNTR = 0;
    USB_ISTR = 0;
    rough_delay_us(100);
    // init again
    usbHidEndpInit();
    usbReportEndpInit();
    usbItInit();
    usbProp.deviceState = DEFAULT;
}

// I don't know how it works. It's just the shadow of MCD team code.
void usbSusp()
{
    usbProp.isSusp = 1;
    // instanteous reset
    // unmask interrupts
    USB_CNTR &= ~((uint32_t)(RESETM));
    // and reset
    USB_CNTR |= FRES;
    USB_CNTR &= ~((uint32_t)(FRES));
    // wait this reaction
    uint32_t timeout = 1e5;
    while( ((USB_ISTR & RESET) == 0) && (--timeout < 2) );
    USB_ISTR = 0;
    // after which we need to restore endp registers only (why endpoints only?)
    USB_EP0R = EP_TYPE_CONTROL | (0 & EA_MASK);
    USB_EP1R = EP_TYPE_INTERRUPT | (1 & EA_MASK);
    // then we may enter suspend mode safely
    USB_CNTR |= FSUSP;
    // USB low power mode and slow clock
    USB_CNTR |= LP_MODE;
    suspSysClk();
}

void usbWkup()
{
    usbProp.isSusp = 0;
    sysClk();
    USB_CNTR &= ~((uint32_t)(LP_MODE | FSUSP));
    USB_ISTR = 0;
    USB_CNTR |= RESETM;
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
    USB_ISTR = 0;
    // I think that ACK is received, come back again in the idle state
    // Cause data sequence in my core consists of only one packet
    epRxStatusSet(0, STAT_RX_NAK);
    epRxStatusSet(0, STAT_TX_NAK);
    controlDtogInit();
}

void interruptEpHandler()
{
    USB_ISTR = 0;
    // all right, wait for the next timer interrupt
    epRxStatusSet(1, STAT_TX_NAK);
}

void usbCore()
{
    if( ((USB_ISTR & CTR) != 0) && isRequest() ) {
        USB_ISTR = 0;
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

void reportTx(uint8_t report)
{
    // get the poiner to packet buffer from table
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR1_TX*2 + USB_CAN_SRAM_BASE);
    // put data into buffer
    *bufferPtr = (uint16_t)report;
    // the size is 2 bytes because memory is word-aligned
    USB_COUNT1_TX = 2 & COUNT_TX_MASK;
    // change the endpoint state
    epTxStatusSet(1, STAT_TX_VALID);
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
    if( (USB_EP0R & (1<<STAT_RX_OFFS)) != (status & (1<<STAT_RX_OFFS)) ) {
        USB_EPNR(ep) = (1<<STAT_RX_OFFS) | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
    if( (USB_EP1R & (1<<(STAT_RX_OFFS+1))) != (status & (1<<(STAT_RX_OFFS+1))) ) {
        USB_EPNR(ep) = (1<<(STAT_RX_OFFS+1)) | USB_EP_RCWO_MASK | (USB_EPNR(ep)&EA_MASK);
    }
}

// core functions which called by requests
void setAddr(uint8_t addr)
{
    USB_DADDR &= ~ADD_MASK;
    USB_DADDR |= addr & ADD_MASK;
    usbProp.deviceState = ADDRESS;
}

void controlDtogInit()
{
    // set dtog_tx = 1, dtog_rx = 0
    if( (USB_EP0R & DTOG_TX) == 0 ) {
        USB_EP0R = DTOG_TX | USB_EP_RCWO_MASK | (USB_EP0R&EA_MASK);
    }
    if( (USB_EP0R & DTOG_RX) != 0 ) {
        USB_EP0R = DTOG_RX | USB_EP_RCWO_MASK | (USB_EP0R&EA_MASK);
    }
}

void defaultDtogInit(int nep)
{
    // set dtog_tx = 0, dtog_rx = 0
    if( (USB_EPNR(nep) & DTOG_TX) != 0 ) {
        USB_EPNR(nep) = DTOG_TX | USB_EP_RCWO_MASK | (USB_EPNR(nep)&EA_MASK);
    }
    if( (USB_EPNR(nep) & DTOG_RX) != 0 ) {
        USB_EPNR(nep) = DTOG_RX | USB_EP_RCWO_MASK | (USB_EPNR(nep)&EA_MASK);
    }
}

int epHaltSet(int ep)
{
    if( (ep == 0) || (ep >= NUM_OF_EP) ) return -1;
    usbProp.epProps[ep].isHalt = 1;
    epRxStatusSet(ep, STAT_RX_STALL);
    epTxStatusSet(ep, STAT_TX_STALL);
    return 0;
}

int epHaltClear(int ep)
{
    if( (ep == 0) || (ep >= NUM_OF_EP) ) return -1;
    usbProp.epProps[ep].isHalt = 0;
    epRxStatusSet(ep, STAT_RX_NAK);
    epTxStatusSet(ep, STAT_TX_NAK);
    return 0;
}

// Сopies request for control endpoint 0 from rx buffer
void reqCopy(requestTyp *request)
{
    union {
      uint8_t* b;
      uint16_t* w;
    } pBuf;
    pBuf.b = (uint8_t*)(USB_ADDR0_RX*2 + USB_CAN_SRAM_BASE);
    request->bmRequestType = *pBuf.b++;
    request->bRequest = *pBuf.b++;
    pBuf.w++;
    request->wValue = *pBuf.w++;
    pBuf.w++;
    request->wIndex = *pBuf.w++;
    pBuf.w++;
    request->wLength = *pBuf.w++;
}

int isRequest()
{
    if( (USB_EP0R & SETUP) > 0 ) {
        return 1;
    }
    return 0;
}

void reqHandler()
{
    requestTyp request;
    // set to NAK first, cause USB device is busy while handle requests
    epRxStatusSet(0, STAT_RX_NAK);
    epTxStatusSet(0, STAT_TX_NAK);
    // work with request
    reqCopy(&request);
    int reqStatus = stReqHandler(&request);
    if( reqStatus == NOT_ST_REQ ) {
        reqStatus = hidReqHandler(&request);
    }
    // in case of error return to the idle state but with stall status
    if( reqStatus < 0 ) {
        epRxStatusSet(0, STAT_RX_STALL);
        epTxStatusSet(0, STAT_TX_STALL);
        controlDtogInit();
    }
    // send null packet if request without data stage and handled successfully
    if( reqStatus == NULL_REQ ) {
        controlTxData0();
    }
}

// method overloading imitation for control endpoint tx functions
void controlTxData0()
{
    USB_COUNT0_TX = 0;
    epTxStatusSet(0, STAT_TX_VALID);
    epRxStatusSet(0, STAT_RX_STALL);
}

void controlTxData1(uint8_t data)
{
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR0_TX*2 + USB_CAN_SRAM_BASE);
    *bufferPtr = (uint16_t)data;
    USB_COUNT0_TX = 2 & COUNT_TX_MASK;
    epTxStatusSet(0, STAT_TX_VALID);
    epRxStatusSet(0, STAT_RX_STALL);
}

void controlTxData2(uint16_t data)
{
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR0_TX*2 + USB_CAN_SRAM_BASE);
    *bufferPtr = data;
    USB_COUNT0_TX = 2 & COUNT_TX_MASK;
    epTxStatusSet(0, STAT_TX_VALID);
    epRxStatusSet(0, STAT_RX_STALL);
}

void controlTxDataN(uint8_t *data, int size)
{
    if(size <= 2) return;
    // byte alingment
    uint16_t *input = (uint16_t*)data;
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR0_TX*2 + USB_CAN_SRAM_BASE);
    int i=0;
    for(i=0 ; i<(size/2) ; ++i) {
        bufferPtr[i] = input[i];
    }
    // last byte to 16 bit
    if( (size%2) > 0 ) {
        *(bufferPtr+i) = (uint16_t)data[size-1];
        ++size;
    }
    USB_COUNT0_TX = size & COUNT_TX_MASK;
    epTxStatusSet(0, STAT_TX_VALID);
    epRxStatusSet(0, STAT_RX_STALL);
}
