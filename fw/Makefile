PROJECT = usb_device3
BUILD_DIR = bin

SHARED_DIR = ../lib
CFILES = main.c
CFILES += mysys.c
CFILES += gamepad_port.c
CFILES += gamepad.c
CFILES += usb_core.c
CFILES += usb_hid.c
CFILES += usb_st_req.c


DEVICE=stm32f103C8T6
OOCD_FILE = board/stm32f0discovery.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../lib/rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
