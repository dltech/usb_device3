#include "usb_device_regs.h"

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
    USB_BTABLE = USB_TABLE_ADDR;
    USB_DADDR_REG |= USB_DADDR_EF;

}

void usbHidEndpInit()
{
    USB_EP_REG(USB_EP0) =
}
