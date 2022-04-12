/*
 * Part of USB VCP.
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
#include "../lib/STM32F103_CMSIS/stm32f103.h"
#include "../lib/rcc.h"
#include "../lib/delay.h"
#include "../lib/regs/usb_device_regs.h"
#include "usb_st_req.h"
#include "usb_cdc_req.h"
#include "uart.h"
#include "usb_core.h"

volatile usbPropStruct usbProp;

// init functions
// basic init
void usbGpioInit(void);
void usbClockInit(void);
void usbItInit(void);
// endpoints init
void usbControlEndpInit(void);
void usbInEndpInit(void);
void usbOutEndpInit(void);
void usbStupidEndpInit(void);
// usb states
// peripherial states
void usbReset(void);
void usbSusp(void);
void usbWkup(void);
// the core
void ctrF(void);
void controlEpRx(void);
void controlEpTx(void);
void vcpEpRx(void);
void vcpEpTx(void);
void stupidEpHandler(void);
// request handler
void reqCopy(requestTyp *request);
void reqHandler(void);
// rxTx functions
int controlRx(uint8_t *data, int size);


void usbGpioInit()
{
    RCC_APB2ENR |= IOPAEN;
    // does not affect anything
/*    GPIOA_CRH = (GPIO_CNF_OUTPUT_ALTFN_PUSHPULL << ((USBDM_PIN_INIT*4)+2)) \
              | (GPIO_CNF_OUTPUT_ALTFN_PUSHPULL << ((USBDP_PIN_INIT*4)+2)) \
              | (GPIO_MODE_OUTPUT_50_MHZ << (USBDM_PIN_INIT*4)) \
              | (GPIO_MODE_OUTPUT_50_MHZ << (USBDP_PIN_INIT*4));

    GPIOA_CRH = (GPIO_CNF_INPUT_PULL_UPDOWN << ((USBDM_PIN_INIT*4)+2)) \
              | (GPIO_CNF_INPUT_PULL_UPDOWN << ((USBDP_PIN_INIT*4)+2)) \
              | (GPIO_MODE_INPUT << (USBDM_PIN_INIT*4)) \
              | (GPIO_MODE_INPUT << (USBDP_PIN_INIT*4)); */
}

void usbClockInit()
{
    RCC_APB1ENR |= USBEN;
    // usb on
    USB_CNTR &= ~((uint32_t)PDWN);
    rough_delay_us(2);
    USB_ISTR = 0;
    // reset usb
    USB_CNTR &= ~((uint32_t)FRES);
    uint32_t timeout = 1e6;
    while( ((USB_ISTR & RESET) == 0) && (--timeout < 2) );
    USB_ISTR = 0;
    USB_CNTR &= ~((uint32_t)(LP_MODE | FSUSP));
    USB_ISTR = 0;
}

void usbItInit()
{
    // init userful interrupts
    USB_CNTR = CTRM | WKUPM | SUSPM | RESETM;
    // init unuserful interrupts
//    USB_CNTR |= ERRM | PMAOVRM | SOFM;
//    USB_CNTR |= ESOFM;
    NVIC_EnableIRQ(usb_lp_can_rx_IRQn);
    NVIC_EnableIRQ(USB_Wakeup_IRQn);
//    nvic_set_priority(NVIC_USB_LP_CAN_RX0_IRQ, 0x00);
}

void usbCoreInit(const descriptorsTyp *descr)
{
    usbGpioInit();
    usbClockInit();
    usbProp.isSusp = 0;
    usbProp.deviceState = DEFAULT;
    usbProp.reportDuration = 33;
    usbProp.desc = descr;
    usbProp.isBoot = 1;
    usbProp.overflow = 0;
    usbProp.iFace = 0;
    usbItInit();
    USB_DADDR = EF;
}

void usbControlEndpInit()
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
    // go to the control endpoint idle state
    controlDtogInit();
    epRxStatusSet(0, STAT_RX_VALID);
    epTxStatusSet(0, STAT_TX_NAK);
}

void usbOutEndpInit()
{
    // endpoint 1 tx buffer
    USB_ADDR1_RX = EP1_RX_START;
    USB_COUNT1_RX = BL_SIZE_32B | \
                    (((EP1_BUFFER_SIZE/32) << NUM_BLOCK_OFFS) & NUM_BLOCK_MASK);
    // endpoint 1 address 1, type interrupt endpoint
    USB_EP1R = EP_TYPE_BULK | (1 & EA_MASK);
    defaultDtogInit(1);
    epRxStatusSet(1, STAT_RX_VALID);
    epTxStatusSet(1, STAT_TX_DISABLED);
    usbProp.epProps[1].isHalt = 0;
}

void usbInEndpInit()
{
    // endpoint 1 tx buffer
    USB_ADDR2_TX = EP2_TX_START;
    // endpoint 1 address 1, type interrupt endpoint
    USB_EP2R = EP_TYPE_BULK | (2 & EA_MASK);
    defaultDtogInit(2);
    epRxStatusSet(2, STAT_RX_DISABLED);
    epTxStatusSet(2, STAT_TX_NAK);
    // interrupt properties
    usbProp.epProps[2].isHalt = 0;
}

void usbStupidEndpInit()
{
    // endpoint 1 tx buffer
    USB_ADDR3_TX = EP3_TX_START;
    // endpoint 1 address 1, type interrupt endpoint
    USB_EP3R = EP_TYPE_INTERRUPT | (3 & EA_MASK);
    defaultDtogInit(3);
    epRxStatusSet(3, STAT_RX_DISABLED);
    epTxStatusSet(3, STAT_TX_NAK);
    // interrupt properties
    usbProp.epProps[3].isHalt = 0;
}

void usbReset()
{
    usbProp.deviceState = DEV_RESET;
    USB_DADDR = EF | 0x00;
    // disable all interrupts
    USB_CNTR = 0;
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
    USB_CNTR = 0;
    USB_ISTR = 0;
    rough_delay_us(1);
    // wait this reaction
    uint32_t timeout = 1e4;
    USB_CNTR &= ~((uint32_t)(FRES));
    while( ((USB_ISTR & RESET) == 0) && (--timeout < 2) );
    USB_CNTR &= ~((uint32_t)(LP_MODE | FSUSP));
    USB_ISTR = 0;
    // init again
    usbControlEndpInit();
    usbInEndpInit();
    usbOutEndpInit();
    usbStupidEndpInit();
    usbItInit();
    usbProp.deviceState = DEFAULT;
}

// I don't know how it works. It's just the shadow of MCD team code.
void usbSusp()
{
    if(usbProp.isSusp == 1) return;
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
    USB_CNTR |= RESETM;
    suspSysClk();
}

void usbWkup()
{
    if(usbProp.isSusp == 0) return;
    usbProp.isSusp = 0;
    sysClk();
    USB_CNTR &= ~((uint32_t)(LP_MODE | FSUSP));
    USB_ISTR = 0;
    defaultDtogInit(1);
    epRxStatusSet(1, STAT_RX_DISABLED);
    epTxStatusSet(1, STAT_TX_NAK);
    controlDtogInit();
    epRxStatusSet(0, STAT_RX_VALID);
    epTxStatusSet(0, STAT_TX_NAK);
    USB_CNTR |= RESETM;
}

void ctrF()
{
    if( ((USB_ISTR & EP_ID_MASK) == 0) && (USB_EP0R & CTR_RX) ) {
        controlEpRx();
    } else if( ((USB_ISTR & EP_ID_MASK) == 0) && (USB_EP0R & CTR_TX) ) {
        controlEpTx();
    }
    if( ((USB_ISTR & EP_ID_MASK) == 1) && (USB_EP1R & CTR_RX) ) {
        vcpEpRx();
    }
    if( ((USB_ISTR & EP_ID_MASK) == 2) && (USB_EP2R & CTR_TX) ) {
        vcpEpTx();
    }
    if( ((USB_ISTR & EP_ID_MASK) == 3) && (USB_EP3R & CTR_TX) ) {
        stupidEpHandler();
    }
}

void controlEpRx()
{
    USB_ISTR = 0;
    // in case of setup packet is received call request handler
    if( usbProp.controlStage == CONTROL_DATA_OUT ) {
        uint8_t data[REQ_DATA_SIZE];
        controlRx(data, REQ_DATA_SIZE);
        lineCodingTyp setupLine;
        setupLine.dwDTERate   =  (uint32_t)data[0] +
                                ((uint32_t)data[1] << 8 ) +
                                ((uint32_t)data[2] << 16) +
                                ((uint32_t)data[3] << 24);
        setupLine.bCharFormat = data[4];
        setupLine.bParityType = data[5];
        setupLine.bDataBits   = data[6];
        uartSetLine(&setupLine);
        usbProp.controlStage = CONTROL_SETUP;
        epRxStatusSet(0, STAT_RX_STALL);
        epTxStatusSet(0, STAT_TX_STALL);
        controlDtogInit();
        return;
    }
    if(USB_EP0R & SETUP) {
        USB_EP0R = USB_EP_RESET_CTR_MASK & USB_EP0R;
        usbProp.controlStage = CONTROL_SETUP;
        reqHandler();
    }
}

void controlEpTx()
{
    USB_ISTR = 0;
    // because set address request is completed after request
    if(usbProp.deviceState == SET_ADDRESS_REQ) {
        USB_EP0R = USB_EP_RESET_CTR_MASK & USB_EP0R;
        setAddr(usbProp.address);
        controlTxData0();
        return;
    }
    // case of multipackage response (in my case 2 packages are possible)
    if(usbProp.overflow > 0) {
        USB_EP0R = USB_EP_RESET_CTR_MASK & USB_EP0R;
        controlTxDataN((uint8_t*)usbProp.mBuffer, usbProp.overflow);
        usbProp.overflow = 0;
        return;
    }
    // status stage of control transaction
    if(usbProp.controlStage == CONTROL_DATA) {
        usbProp.controlStage = CONTROL_STATUS;
        controlTxData0();
        return;
    }
    // In all other cases, usually after TX ACK is received, come
    // back again in the idle state.
    USB_EP0R = USB_EP_RESET_CTR_MASK & USB_EP0R;
    epRxStatusSet(0, STAT_RX_VALID);
    epTxStatusSet(0, STAT_TX_NAK);
    controlDtogInit();
}

void vcpEpRx()
{
    USB_ISTR = 0;
    USB_EP1R = USB_EP_RESET_CTR_MASK & USB_EP1R;
    // loopback
    // for(int i=0 ; i<size ; ++i) ++data[i];
    // vcpTx(data,size);
    uint8_t data[64];
    int size = vcpRx(data,64);
    uartTx(data, size);
    // ignoring input data in case of loger
    epRxStatusSet(1, STAT_RX_VALID);
}

void vcpEpTx()
{
    USB_ISTR = 0;
    USB_EP2R = USB_EP_RESET_CTR_MASK & USB_EP2R;
    // wait for the next output data
    epTxStatusSet(2, STAT_TX_NAK);
}

void stupidEpHandler()
{
    USB_ISTR = 0;
    USB_EP3R = USB_EP_RESET_CTR_MASK & USB_EP3R;
    epRxStatusSet(3, STAT_TX_NAK);
}

volatile uint16_t requestss[200];
void reqHandler()
{
    requestTyp request;
    int reqStatus = -5;
    // set to NAK first, cause USB device is busy while handle requests
//    epRxStatusSet(0, STAT_RX_NAK);
//    epTxStatusSet(0, STAT_TX_NAK);
    // work with request
    reqCopy(&request);
 // static int i=0;
 // if(request.bRequest == 0x20) requestss[i++] = request.bmRequestType;
 // if(request.bRequest == 0x22) requestss[i++] = request.bmRequestType;
 // if(request.bRequest == 9) requestss[i++] = request.bmRequestType;
 // requestss[i++] = request.bRequest;
 // if(request.bRequest == 6) requestss[i++] = request.wValue;
 // if(request.bRequest == 6) requestss[i++] = request.wLength;
 // if(request.bRequest == 9) requestss[i++] = request.wValue;
 // if(request.bRequest == 9) requestss[i++] = request.wIndex;
 // if(request.bRequest == 9) requestss[i++] = request.wLength;

    if( isCdcReqTyp(&request) ) {
        reqStatus = cdcReqHandler(&request);
    } else {
        reqStatus = stReqHandler(&request);
    }
    if( reqStatus == DATA_OUT_STAGE ) {
        epRxStatusSet(0, STAT_RX_VALID);
        epTxStatusSet(0, STAT_TX_NAK);
        usbProp.controlStage = CONTROL_DATA_OUT;
    }
    if( reqStatus == DATA_STAGE ) {
        usbProp.controlStage = CONTROL_DATA;
    }
    // in case of error return to the idle state but with stall status
    if( reqStatus < 0 ) {
        epRxStatusSet(0, STAT_RX_STALL);
        epTxStatusSet(0, STAT_TX_STALL);
        controlDtogInit();
        usbProp.controlStage = CONTROL_ERROR;
    }
    // send null packet if request without data stage handled successfully
    if( reqStatus == NULL_REQ ) {
        usbProp.controlStage = CONTROL_STATUS;
        controlTxData0();
    }
 // requestss[i++] = (uint16_t)usbProp.controlStage;
 // requestss[i++] = 0xffff;
 // if(i>200) i = 0;
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

void usbCore()
{
    static int esofCnt = 0;
    if(USB_ISTR & CTR) {
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
    // unusable interrupts
    if(USB_ISTR & ERR) {
    }
    if(USB_ISTR & PMAOVR) {
    }
    if(USB_ISTR & SOF) {
    }
    if(USB_ISTR & ESOF) {
        ++esofCnt;
        if( (esofCnt > 3) && ((USB_ISTR & SUSPM) == 0) ) {
            esofCnt = 0;
//            usbReset();
        }
    }
    USB_ISTR = 0;
}

// core functions which called by requests
void setAddr(uint8_t addr)
{
    USB_DADDR = EF | (addr & ADD_MASK);
    usbProp.deviceState = ADDRESS;
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

int controlRx(uint8_t *data, int size)
{
    uint16_t *dataPtr = (uint16_t*)data;
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR0_RX*2 + USB_CAN_SRAM_BASE);
    int inSize = USB_COUNT0_RX & COUNT_RX_MASK;
    if(size < inSize) inSize = size;
    for(int i=0 ; i<(inSize/2) ; ++i) {
        *dataPtr = *bufferPtr;
        dataPtr++;
        bufferPtr += 2;
    }
    // last byte to 16 bit
    if( (inSize%2) > 0 ) {
        data[inSize-1] = (uint8_t)*bufferPtr;
    }
    return inSize;
}

// method overloading imitation for control endpoint tx functions
void controlTxData0()
{
    USB_COUNT0_TX = 0;
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR0_TX*2 + USB_CAN_SRAM_BASE);
    *bufferPtr = 0;
    controlDtogInit();
    epRxStatusSet(0, STAT_RX_VALID);
    epTxStatusSet(0, STAT_TX_VALID);
//    epTxStatusSet(0, STAT_TX_NAK);
}

void controlTxData1(uint8_t data)
{
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR0_TX*2 + USB_CAN_SRAM_BASE);
    *bufferPtr = (uint16_t)data;
    USB_COUNT0_TX = 1 & COUNT_TX_MASK;
    controlDtogInit();
    epRxStatusSet(0, STAT_RX_VALID);
    epTxStatusSet(0, STAT_TX_VALID);
}

void controlTxData2(uint16_t data)
{
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR0_TX*2 + USB_CAN_SRAM_BASE);
    *bufferPtr = data;
    USB_COUNT0_TX = 2 & COUNT_TX_MASK;
    controlDtogInit();
    epRxStatusSet(0, STAT_RX_VALID);
    epTxStatusSet(0, STAT_TX_VALID);
}

void controlTxDataN(uint8_t *data, int size)
{
    if(size <= 2) return;
    // a case with > 64 bytes
    if(size > EP0_BUFFER_SIZE) {
        usbProp.overflow = size - EP0_BUFFER_SIZE;
        if(usbProp.overflow > EP0_BUFFER_SIZE) usbProp.overflow = EP0_BUFFER_SIZE;
        for(int i=0 ; i<usbProp.overflow ; ++i) {
            usbProp.mBuffer[i] = data[i+EP0_BUFFER_SIZE];
        }
        size = EP0_BUFFER_SIZE;
    } else {
        usbProp.overflow = 0;
    }

    uint16_t *input = (uint16_t*)data;
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR0_TX*2 + USB_CAN_SRAM_BASE);
    for(int i=0 ; i<(size/2) ; ++i) {
        *bufferPtr = *input;
        input++;
        bufferPtr += 2;
    }
    // last byte to 16 bit
    if( (size%2) > 0 ) {
        *bufferPtr = (uint16_t)data[size-1];
    }
    USB_COUNT0_TX = size & COUNT_TX_MASK;
    epRxStatusSet(0, STAT_RX_VALID);
    epTxStatusSet(0, STAT_TX_VALID);
}

void vcpTx(uint8_t *data, int size)
{
    // get the poiner to packet buffer from table
    uint16_t *input = (uint16_t*)data;
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR2_TX*2 + USB_CAN_SRAM_BASE);
    // put data into buffer
    for(int i=0 ; i<(size/2) ; ++i) {
        *bufferPtr = *input;
        input++;
        bufferPtr += 2;
    }
    // last byte to 16 bit
    if( (size%2) > 0 ) {
        *bufferPtr = (uint16_t)data[size-1];
    }
    USB_COUNT2_TX = size & COUNT_TX_MASK;
    // change the endpoint state
    epTxStatusSet(2, STAT_TX_VALID);
}

int vcpRx(uint8_t *data, int size)
{
    uint16_t *dataPtr = (uint16_t*)data;
    uint16_t *bufferPtr = (uint16_t*)(USB_ADDR1_RX*2 + USB_CAN_SRAM_BASE);
    int inSize = USB_COUNT1_RX & COUNT_RX_MASK;
    if(size < inSize) inSize = size;
    for(int i=0 ; i<(inSize/2) ; ++i) {
        *dataPtr = *bufferPtr;
        dataPtr++;
        bufferPtr += 2;
    }
    // last byte to 16 bit
    if( (inSize%2) > 0 ) {
        data[inSize-1] = (uint8_t)*bufferPtr;
    }
    return inSize;
}

// Concatenation to make descriptors in request readable form
int descCat(const uint8_t *in, uint8_t *out, int prev, uint16_t size, uint16_t mainLen)
{
    int i = prev;
    for( ; (i<mainLen) && ((i-prev)<size) ; ++i) {
        out[i] = in[i - prev];
    }
    return i;
}

// yet another wakeup interrupt line
void USB_Wakeup_Handler()
{
    usbWkup();
}
