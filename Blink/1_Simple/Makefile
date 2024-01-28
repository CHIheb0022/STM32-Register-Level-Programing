CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
BIN=arm-none-eabi-objcopy
STL=st-flash
CFLAGS= -W -nostartfiles -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
         -Wformat-truncation -fno-common -Wconversion \
         -g3 -Os -ffunction-sections -fdata-sections -I. \
         -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 $(EXTRA_CFLAGS)

ifeq ($(OS),Windows_NT)
  RM = cmd /C del /Q /F
else
  RM = rm -f
endif

all: app.bin

Startup.o: Startup.s
	$(AS) -o $@ $<

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

app.elf: Startup.o main.o
	$(LD) -T Linker.ld -o $@ $^

app.bin: app.elf
	$(BIN) -O binary $< $@

clean:
	$(RM) -f *.o *.elf *.bin

flash: app.bin
	$(STL) --reset write $< 0x8000000

erase:
	$(STL) erase