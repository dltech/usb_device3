# usb_device3
STM32 based USB adapter for ZX spectrum joystick. You may connect gamepad
with d-pad and two buttons to PC using USB.
Tested and working.
![device](datasheet/pcb.JPG)
![eee](datasheet/gamepad.JPG)
![eeee](datasheet/test.png)

Project structure:
button.elf - binary file to upload into board
/lib - basic code directory
/lib/regs - stm32 MCU registers (lowest micriocontroller API level)
/lib/STM32F103_CMSIS/ - MCU specific part of CMSIS
/lib/CMSIS_5 - ARM CMSIS abstraction level directly from arm, as a submodule
fpjat - build and upload script (for xubuntu, needs gcc arm toolchain and st-link, see pdf)
/doc - project documentation pdf
/datasheet - all related documentation (datasheets, standards)
/sch - KiCAD schematic project with png
