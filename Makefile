################################################################################
### CUSTOMIZE BELOW HERE #######################################################

BUILD_DIR = bin
CC = arm-none-eabi-gcc # define the compiler to use
TARGET = button.elf # define the name of the executable
PROJECT_DIR = lib/
REG_DIR		= lib/regs/
SOURCES = main.c
SOURCES += $(PROJECT_DIR)gamepad_port.c
SOURCES += $(PROJECT_DIR)gamepad.c
SOURCES += $(PROJECT_DIR)usb_core.c
SOURCES += $(PROJECT_DIR)usb_hid.c
SOURCES += $(PROJECT_DIR)usb_st_req.c
SOURCES += $(PROJECT_DIR)rcc.c
SOURCES += $(PROJECT_DIR)delay.c
SOURCES += $(REG_DIR)usb_device_regs.c

DEFINES = ARMCM3

INCLUDES   = -I$(PROJECT_DIR)
INCLUDES  += -I$(REG_DIR)

# VENDOR SPECIFIC CODE
CMSIS_INC  = lib/CMSIS_5/CMSIS/Core/Include
VENDOR_DIR = lib/STM32F103_CMSIS
SOURCES += $(VENDOR_DIR)/startup_stm32f103.c
SOURCES += $(VENDOR_DIR)/system_stm32f103.c
INCLUDES  += -I$(VENDOR_DIR)/
INCLUDES  += -I$(CMSIS_INC)/
LD_SCRIPT = $(VENDOR_DIR)/gcc_arm.ld

CFLAGS +=-ffunction-sections -fdata-sections
CFLAGS +=-Wall -Wextra -Werror -Wconversion -Wundef -Wformat=2 -Wformat-truncation
CFLAGS +=-Wdouble-promotion -Wshadow -Wimplicit-function-declaration
CFLAGS +=-fno-common -Os -ffreestanding
CFLAGS +=-mcpu=cortex-m3 -mthumb
CFLAGS +=-fstack-usage -mfloat-abi=soft -std=gnu11
#CFLAGS +=-ggdb3
CFLAGS +=-D$(DEFINES)

LFLAGS  = -T$(LD_SCRIPT) --specs=nano.specs
LFLAGS += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

################################################################################
### DO NOT EDIT THE FOLLOWING LINES ############################################

C_OBJS = $(SOURCES:.c=.o)

all: $(TARGET)

#$(BUILD_DIR):
#	@mkdir -p $(BUILD_DIR)

# Compile
$(C_OBJS): $(BUILD_DIR)/%.o: %.c
#$(C_OBJS):
	@echo "[CC] $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Link
%.elf: $(C_OBJS)
	@echo "[LD] $@"
	@$(CC) $(CFLAGS) $(LFLAGS) $(C_OBJS) -o $@

# Clean
clean:
	@rm -f $(C_OBJS) $(TARGET)



# define list of objects
#OBJSC=$(SOURCES:.c=.o)
#OBJS=$(OBJSC:.cpp=.o)

# the target is obtained linking all .o files
#all: $(SOURCES) $(TARGET)

#$(TARGET): $(OBJS)
#	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)

#purge: clean
#	rm -f $(TARGET)

#clean:
#	rm -f *.o

################################################################################
################################################################################
