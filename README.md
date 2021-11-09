# usb_device3
USB HID gamepad.
STM32 based USB adapter for ZX spectrum joystick. You may connect gamepad
with d-pad and two buttons to PC using USB.
Tested and working.
![device](result/pcb.JPG)
![eee](result/gamepad.JPG)
![eeee](result/test.png)

Project structure:\
/result - here is all usefull files to try this project (firmware binary, schematic and pcb template)\
/lib - basic code directory\
/lib/regs - stm32 MCU registers (lowest micriocontroller API level)\
/lib/STM32F103_CMSIS/ - MCU specific part of CMSIS\
/lib/CMSIS_5 - ARM CMSIS abstraction level directly from arm, as a submodule\
fpjat - build and upload script (for xubuntu, needs gcc arm toolchain and st-link, see pdf)\
/doc - project documentation in tex\
/datasheet - all related documentation (datasheets, standards)\
/sch - KiCAD schematic project
