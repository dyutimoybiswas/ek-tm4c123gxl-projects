TIVAWARE := $(CURDIR)/../tivaware
BUILD    := build
PROJECT_NAME := blinky

CC := arm-none-eabi-gcc
LD := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy

INCLUDES := -Iinc -I$(TIVAWARE) -I$(TIVAWARE)/inc

CFLAGS := -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 \
          -O0 -g -ffunction-sections -fdata-sections \
          -DPART_TM4C123GH6PM -DTARGET_IS_TM4C123_RB1 \
          $(INCLUDES)

LDFLAGS := -T tm4c.ld -Wl,-Map=$(BUILD)/$(PROJECT_NAME).map -Wl,--gc-sections \
		   -L$(TIVAWARE)/driverlib/gcc -ldriver -lm -lc -lnosys

# Source files
SRCS := $(wildcard src/*.c)

OBJS     := $(SRCS:src/%.c=$(BUILD)/%.o)
ELF      := $(BUILD)/$(PROJECT_NAME).elf
BIN      := $(BUILD)/$(PROJECT_NAME).bin

# Default target
all: $(BUILD) $(ELF) $(BIN)

$(BUILD):
	mkdir -p $(BUILD)

# Compile
$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(ELF): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Convert ELF → BIN
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

size: $(ELF)
	arm-none-eabi-size $(ELF)

clean:
	rm -rf $(BUILD)

.PHONY: all clean size
