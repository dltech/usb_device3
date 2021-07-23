#include "usb_device_regs.h"

void controlDtogInit()
{
    // set dtog_tx = 1, dtog_rx = 0
    if( (USB_EP0R & DTOG_TX) == 0 ) {
        USB_EP0R = DTOG_TX | (USB_EP0R&USB_EP_RESET_CTR_MASK);
    }
    if( (USB_EP0R & DTOG_RX) != 0 ) {
        USB_EP0R = DTOG_RX | (USB_EP0R&USB_EP_RESET_CTR_MASK);
    }
}

void defaultDtogInit(int nep)
{
    // set dtog_tx = 0, dtog_rx = 0
    if( (USB_EPNR(nep) & DTOG_TX) != 0 ) {
        USB_EPNR(nep) = DTOG_TX | (USB_EPNR(nep)&USB_EP_RESET_CTR_MASK);
    }
    if( (USB_EPNR(nep) & DTOG_RX) != 0 ) {
        USB_EPNR(nep) = DTOG_RX | (USB_EPNR(nep)&USB_EP_RESET_CTR_MASK);
    }
}

// work with status bits
void epTxStatusSet(int ep, uint16_t status)
{
    // toggle bit 0, if it's nesessary
    if( (USB_EPNR(ep) & (1<<STAT_TX_OFFS)) != (status & (1<<STAT_TX_OFFS)) ) {
        USB_EPNR(ep) = (1<<STAT_TX_OFFS) | (USB_EPNR(ep)&USB_EP_RESET_CTR_MASK);
    }
    // toggle bit 1
    if( (USB_EPNR(ep) & (1<<(STAT_TX_OFFS+1))) != (status & (1<<(STAT_TX_OFFS+1))) ) {
        USB_EPNR(ep) = (1<<(STAT_TX_OFFS+1)) | (USB_EPNR(ep)&USB_EP_RESET_CTR_MASK);
    }
}

void epRxStatusSet(int ep, uint16_t status)
{
    if( (USB_EPNR(ep) & (1<<STAT_RX_OFFS)) != (status & (1<<STAT_RX_OFFS)) ) {
        USB_EPNR(ep) = (1<<STAT_RX_OFFS) | (USB_EPNR(ep)&USB_EP_RESET_CTR_MASK);
    }
    if( (USB_EPNR(ep) & (1<<(STAT_RX_OFFS+1))) != (status & (1<<(STAT_RX_OFFS+1))) ) {
        USB_EPNR(ep) = (1<<(STAT_RX_OFFS+1)) | (USB_EPNR(ep)&USB_EP_RESET_CTR_MASK);
    }
}
