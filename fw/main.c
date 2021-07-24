#include "gamepad.h"

#include "usb_device_regs.h"
#include "../libopencm3/include/libopencm3/stm32/gpio.h"
volatile uint32_t reg1, reg2, reg3, reg4, reg5, reg7, reg6, reg8;

int main(void) {
	gamepadInit();
	while(1){
		reg1 = USB_ISTR;
		reg2 = USB_CNTR;
		reg3 = USB_EP0R;
		reg4 = GPIOA_CRH;
		reg5 = USB_COUNT0_RX;
		reg6 = USB_ADDR0_TX;
		reg7 = USB_ADDR0_RX;
		reg8 = USB_ADDR1_TX;
	}
}
