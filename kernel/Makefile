SOURCE=boot.o main.o commona.o commonb.o monitor.o descriptor.o gdt.o interrupt.o isr.o timer.o
ASFLAGS=-f elf
CC=i586-elf-gcc
CFLAGS=-fno-builtin
LDFLAGS=-T link.ld
all: $(SOURCE) link
clean:
	rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCE)

.s.o:
	nasm $(ASFLAGS) $<
