SRC = *.c
OUTPUT = output.elf
CFLAGS = -Os -Wall -Wextra
CPPFLAGS = -D F_CPU=8000000UL
TARGET = atmega168

all: $(SRC)
	avr-gcc -std=c11 $(CFLAGS) $(CPPFLAGS) -mmcu=$(TARGET) \
	-o $(OUTPUT) $(SRC)
	avr-objcopy  -j .text -j .data -O ihex $(OUTPUT) $(OUTPUT:.elf=.hex)

prog: $(OUTPUT:.elf=.hex)
	sudo avrdude -p m168 -c linuxspi -P /dev/spidev0.0 -e -U \
	flash:w:$(OUTPUT)
