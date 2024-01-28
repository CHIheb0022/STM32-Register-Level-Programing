/* ******************************************* MakeFile ******************************************** */ 

CC=arm-none-eabi-gcc  // ARM Compiler
BIN=arm-none-eabi-objcopy // Machihne Code Translator (ELF->BIN)
STL=st-flash // ST-Link utility for Flashing  

CFLAGS  ?=  -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
            -Wformat-truncation -fno-common -Wconversion \
            -g3 -Os -ffunction-sections -fdata-sections -I. \
            -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)
LDFLAGS ?= -Tlink.ld -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections -Wl,-Map=$@.map
SOURCES = main.c Startup.c 

ifeq ($(OS),Windows_NT)
  RM = cmd /C del /Q /F
else
  RM = rm -f
endif

build: firmware.bin

firmware.elf: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

firmware.bin: firmware.elf
	$(BIN) -objcopy -O binary $< $@

flash: firmware.bin
	$(STL) --reset write $< 0x8000000

clean:
	$(RM) firmware.*

