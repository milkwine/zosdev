SOURCE=boot.o main.o commona.o commonb.o monitor.o descriptor.o gdt.o interrupt.o isr.o timer.o paging.o buddy.o ini.o syscall.o task.o
ASFLAGS=-f elf
CC=i586-elf-gcc
CFLAGS=-ffreestanding
#CFLAGS=-ffreestanding -O2 -Wall -Wextra
LDFLAGS=-T link.ld -nostdlib
all: $(SOURCE) link
clean:
	rm *.o kernel

link:
	i586-elf-ld $(LDFLAGS) -o kernel $(SOURCE)

.s.o:
	nasm $(ASFLAGS) $<
