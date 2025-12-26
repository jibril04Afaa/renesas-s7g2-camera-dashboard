CROSS_COMPILE ?= arm-none-eabi-

CC      = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
SIZE    = $(CROSS_COMPILE)size

BUILD   := build
TARGET  := dk-s7g2

CFLAGS  := -mthumb -mcpu=cortex-m4 -Os -std=gnu99 -Wall -Wextra
CFLAGS  += -ffunction-sections -fdata-sections
CFLAGS  += -Iinclude

LDFLAGS := -nostartfiles -Wl,--gc-sections -T s7g2.lds

SRCS := \
  app/main.c \
  app/bringup.c \
  platform/reset.c \
  platform/vector.c

OBJS := $(patsubst %.c,$(BUILD)/%.o,$(SRCS))

all: $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: %.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@
	$(OBJDUMP) -S $< > $(BUILD)/$(TARGET).lst

clean:
	rm -rf $(BUILD)

flash: $(BUILD)/$(TARGET).elf
	JLinkExe -NoGui 1 -ExitOnError 1 -CommandFile flash.jlink
