#include "gamepad.h"

#include "usb_device_regs.h"
volatile uint32_t reg1 = 0, reg2 = 0;

int main(void) {
	gamepadInit();
	while(1){
		reg1 = USB_ISTR;
		reg2 = USB_CNTR;
	}
}
