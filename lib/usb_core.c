#include "usb_device_regs.h"
#include "usb_core.h"

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



    USB_DADDR_REG |= USB_DADDR_EF;
}

void usbHidEndpInit()
{
    //buffer config
    USB_BTABLE    = USB_TABLE_ADDR;
    // endpoint 0 rx/tx buffers
    USB_ADDR0_TX  = USB_TABLE_END & ADDR_TX_MASK;
    USB_ADDR0_RX  = (USB_ADDR0_TX + EP0_BUFFER_SIZE) & ADDR_TX_MASK;
    USB_COUNT0_RX = BL_SIZE_32B | \
                    (((EP0_BUFFER_SIZE/32) << NUM_BLOCK_OFFS) & NUM_BLOCK_MASK);
    // endp
    USB_EP0R = EP_TYPE_INTERRUPT | (0 & EA_MASK);

}
