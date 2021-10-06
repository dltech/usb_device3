################################################################################
### CUSTOMIZE BELOW HERE #######################################################

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
SOURCES += $(REG_DIR)usb_device_regs.c
SOURCES += $(PROJECT_DIR)rcc.c


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
CFLAGS +=-Wdouble-promotion -Wshadow -Wpadded -Wimplicit-function-declaration
CFLAGS +=-fno-common -Os -mcpu=cortex-m3 -mthumb -ffreestanding
CFLAGS +=-ggdb3

LFLAGS= -T$(LD_SCRIPT)

################################################################################
### DO NOT EDIT THE FOLLOWING LINES ############################################

CXX_OBJS = $(SOURCES:.c=.o)
ALL_OBJS = $(CXX_OBJS)

all: $(TARGET)

# Compile
$(CXX_OBJS): %.o: %.c
$(ALL_OBJS):
	@echo "[CC] $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Link
%.elf: $(ALL_OBJS)
	@echo "[LD] $@"
	@$(CC) $(CFLAGS) $(LFLAGS) $(ALL_OBJS) -o $@

# Clean
clean:
	@rm -f $(ALL_OBJS) $(TARGET)



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
