
void usbClockInit()
{
    RCC_AHBENR |= RCC_AHBENR_OTGFSEN;
    // usb on
    (*USB_CNTR_REG) &= ((uint32_t)(~USB_CNTR_PWDN));
    rough_delay_us(1);
    (*USB_ISTR_REG) = ((uint32_t)0);
    (*USB_CNTR_REG) &= ((uint32_t)(~USB_CNTR_FRES));
}


void usbReset()
{
    USB_DADDR_REG |= USB_DADDR_EF;

}

void usbHidEndpInit()
{
    USB_EP_REG(USB_EP0) = 
}
