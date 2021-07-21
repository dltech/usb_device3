#include "usb_device_regs.h"

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
