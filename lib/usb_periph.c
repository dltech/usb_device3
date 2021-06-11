#include "../libopencm3/include/libopencm3/stm32/st_usbfs.h"
#include "../libopencm3/include/libopencm3/stm32/usb/dwc/otg_fs.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"


void usbHwInit()
{
    RCC_AHBENR |= RCC_AHBENR_OTGFSEN;
    // usb on
    (*USB_CNTR_REG) &= ((uint32_t)(~USB_CNTR_PWDN));
    rough_delay_us(1);
    (*USB_ISTR_REG) = ((uint32_t)0);
    (*USB_CNTR_REG) &= ((uint32_t)(~USB_CNTR_FRES));
}

int usbCoreInit()
{
    // basic interrupts
    OTG_FS_GAHBCFG |= OTG_GAHBCFG_GINT | OTG_GAHBCFG_PTXFELVL;
    // force the device mode
    OTG_FS_GUSBCFG |= OTG_GUSBCFG_FDMOD;
    // timeouts
    OTG_FS_GUSBCFG |= OTG_GUSBCFG_TRDT_MASK & (0x09 << 10);
    OTG_FS_GUSBCFG |= OTG_GUSBCFG_TOCAL;
    // interrupt masks
    OTG_FS_GINTMSK |= OTG_GINTMSK_OTGINT | OTG_GINTMSK_MMISM;
    // check if receive mode
    if( (OTG_FS_GINTSTS & OTG_GINTSTS_CMOD) > 0 ) {
        return -1;
    }
    return 0;
}

int usbHostInit()
{
    uint32_t timeout = 1e7;
    // usb 1.1 full spd
    OTG_FS_DCFG |= OTG_DCFG_DSPD;
    // stall on
    OTG_FS_DCFG |= OTG_DCFG_NZLSOHSK;
    // choose interrupts
    OTG_FS_GINTMSK |= OTG_GINTMSK_USBRST | OTG_GINTMSK_ENUMDNEM;
    OTG_FS_GINTMSK |= OTG_GINTMSK_ESUSPM | OTG_GINTMSK_USBSUSPM;
    OTG_FS_GINTMSK |= OTG_GINTMSK_SOFM;
    // usb power detecting not used
    OTG_FS_GCCFG = 0;
    // wait for usb reset procedure will done
    uint32_t timeout = 1e7;
    while( ((OTG_FS_GINTSTS & OTG_GINTSTS_USBRST) == 0) && (--timeout > 0) );
    if(timeout < 5) return -1;
    // wait for enumeration will done
    timeout = 1e7;
    while( ((OTG_FS_GINTSTS & OTG_GINTSTS_ENUMDNE) == 0) && (--timeout > 0) );
    if(timeout < 5) return -1;
    return 0;
}

int usbHostEndpointInit()
{
    OTG_FS_DIEPCTL0 |= OTG_DIEPCTL0_SNAK;

}

void usbInit()
{
    OTG_FS_GUSBCFG |= OTG_GUSBCFG_FDMOD;

}
