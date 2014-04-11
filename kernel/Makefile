SOURCE=boot.o main.o commona.o commonb.o monitor.o
ASFLAGS=-f elf
CC=i586-elf-gcc
CFLAGS=
LDFLAGS=-T link.ld
all: $(SOURCE) link
clean:
	rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCE)

.s.o:
	nasm $(ASFLAGS) $<
