PROJECT = usb_device1
BUILD_DIR = bin

SHARED_DIR = ../lib
CFILES = main.c
CFILES += mystmbackend.c
CFILES += printf7.c
CFILES += tm1637.c
CFILES += freq_dr.c
CFILES += cmsis_sin.c
CFILES += ds18b20.c

DEVICE=stm32f030K6T6
OOCD_FILE = board/stm32f0discovery.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../lib/rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
