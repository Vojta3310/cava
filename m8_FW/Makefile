###############################################################################
# Makefile for the project
###############################################################################

## General Flags
MCU = atmega8
F_CPU=16000000UL
TARGET = LEDstrip
CC = avr-gcc

## Objects that must be built in order to link
OBJECTS = main.o uart.o 




## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU) 

## Compile options common for all C compilation units.
CFLAGS = $(COMMON) 
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DF_CPU=$(F_CPU) -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wattributes
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON) -Wl,-u,vfprintf -lprintf_flt -lm
LDFLAGS +=  -Wl,-Map=$(TARGET).map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET).hex size

## Compile
%.o: %.c
	${CC} $(INCLUDES) ${CFLAGS} -c  $< -o $@ 

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) *.elf dep/* *.hex *.eep *.lss *.map dep ${TARGET}
flash: $(TARGET)
	avrdude -p $(MCU) -P usb -c usbasp-clone -F -U flash:w:$(TARGET).hex
debug: all flash

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

