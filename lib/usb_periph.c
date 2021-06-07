#include "../libopencm3/include/libopencm3/stm32/st_usbfs.h"
#include "../libopencm3/include/libopencm3/stm32/usb/dwc/otg_fs.h"


void usbInit()
{
    OTG_FS_GUSBCFG |= OTG_FS_GUSBCFG_FDMOD;
}
