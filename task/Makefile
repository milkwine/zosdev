ASFLAGS=-f elf
CC=i586-elf-gcc
CFLAGS=-ffreestanding -fno-common
LD=i586-elf-ld
LDFLAGS=-T link.ld -nostdlib -s
OBJ=ini.o api.o
TARGET=ini taska
all: $(OBJ) $(TARGET)
clean:
	rm $(OBJ) $(TARGET)
.s.o:
	nasm $(ASFLAGS) $<
ini: ini.o api.o
	$(LD) $(LDFLAGS) -o ini $^
taska: taska.o api.o
	$(LD) $(LDFLAGS) -o taska $^
