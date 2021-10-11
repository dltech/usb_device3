#paths
TARGET = result/button.elf
LIB_DIR = lib
REG_DIR	= $(LIB_DIR)/regs
ODIR = bin

# code is here
SOURCES = main.c
SOURCES += $(LIB_DIR)/gamepad_port.c
SOURCES += $(LIB_DIR)/gamepad.c
SOURCES += $(LIB_DIR)/usb_core.c
SOURCES += $(LIB_DIR)/usb_hid.c
SOURCES += $(LIB_DIR)/usb_st_req.c
SOURCES += $(LIB_DIR)/rcc.c
SOURCES += $(LIB_DIR)/delay.c
SOURCES += $(REG_DIR)/usb_device_regs.c

INCLUDES   = -I $(LIB_DIR)/
INCLUDES  += -I $(REG_DIR)/

# VENDOR SPECIFIC CODE
CMSIS_INC  = $(LIB_DIR)/CMSIS_5/CMSIS/Core/Include
VENDOR_DIR = $(LIB_DIR)/STM32F103_CMSIS
SOURCES += $(VENDOR_DIR)/startup_stm32f103.c
SOURCES += $(VENDOR_DIR)/system_stm32f103.c
INCLUDES  += -I $(VENDOR_DIR)
INCLUDES  += -I $(CMSIS_INC)
LD_SCRIPT = $(VENDOR_DIR)/gcc_arm.ld
DEFINES = ARMCM3

# Parameters
CFLAGS +=-ffunction-sections -fdata-sections
CFLAGS +=-Wall -Wextra -Werror -Wconversion -Wundef -Wformat=2 -Wformat-truncation
CFLAGS +=-Wdouble-promotion -Wshadow -Wimplicit-function-declaration
CFLAGS +=-Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
CFLAGS +=-fno-common -Os -ffreestanding
CFLAGS +=-mcpu=cortex-m3 -mthumb
CFLAGS +=-mfloat-abi=soft -std=gnu2x
CFLAGS +=-D$(DEFINES)
#CFLAGS +=-ggdb3
LFLAGS  = -T"$(LD_SCRIPT)" --specs=nano.specs -Wl,--gc-sections
LFLAGS += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group
#utilities
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc

### making-taking aaaa #########################################################

#object files list
OBJECTS = $(SOURCES:%.c=$(ODIR)/%.o)

#main rule
all: $(TARGET)
#compile
$(ODIR)/%.o: %.c
	@echo "[CC] $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEFS) -c $< -o $@
#link
$(TARGET): $(OBJECTS)
	@echo "[LD] $@"
	@$(LD) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $@

# Clean rule
#.PHONY:
clean:
	@rm -rf $(ODIR)
	@rm -r $(TARGET)
