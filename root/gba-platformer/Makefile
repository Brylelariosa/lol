#-------------------------------------------------------------------------------
# GBA Platformer build
#
# Requires the devkitARM toolchain (arm-none-eabi-gcc, gbafix) on PATH.
# The CI workflow (.github/workflows/build.yml) installs this automatically
# via .github/actions/setup-devkitarm - you don't need anything installed
# locally unless you want to build on your own machine too.
#-------------------------------------------------------------------------------

TARGET    := platformer
BUILD_DIR := build
SRC_DIRS  := source source/engine source/game

CC      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
GBAFIX  := gbafix

ARCH    := -mthumb -mthumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi
CFLAGS  := -g -Wall -O2 -ffunction-sections -fdata-sections $(ARCH) \
           $(addprefix -I,$(SRC_DIRS))
LDFLAGS := -specs=gba.specs $(ARCH) -Wl,--gc-sections -Wl,-Map,$(BUILD_DIR)/$(TARGET).map

C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJS    := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_FILES))

.PHONY: all clean

all: $(TARGET).gba

$(TARGET).gba: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $(TARGET).gba
	$(GBAFIX) $(TARGET).gba

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET).gba
