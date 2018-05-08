# Entry point of Orange'S
# It must have the same value with 'KernelEntryPointPhyAddr' in load.inc!
ENTRYPOINT	= 0x801000

# Offset of entry point in kernel file
# It depends on ENTRYPOINT
ENTRYOFFSET	=   0x1000

# Programs, flags, etc.
ASM		= nasm
DASM	= ndisasm
CC		= gcc
LD		= ld
ASMBFLAGS	= -I include/
ASMKFLAGS	= -I include/ -f elf
CFLAGS		= -I include/ -c -fno-builtin -m32
LDFLAGS		= -s -Ttext $(ENTRYPOINT) -m elf_i386 -e main
DASMFLAGS	= -u -o $(ENTRYPOINT) -e $(ENTRYOFFSET)

# This Program
BOOT		= boot/boot boot/loader
KERNEL		= kernel/kernel
LIB			= lib/puts.o
DASMOUTPUT	= kernel.asm
OBJS		= kernel/kernel.o lib/puts.o lib/memcpy.o

# All Phony Targets
.PHONY : everything final image clean realclean disasm all buildimg

# Default starting position
everything : $(BOOT) $(LIB) $(KERNEL)

all : realclean everything

final : all clean

image : final buildimg

clean : 
	rm -f $(OBJS)

realclean :
	rm -f $(OBJS) $(BOOT) $(LIB) $(KERNEL)

disasm :
	$(DASM) $(DASMFLAGS) > $(DASMOUTPUT)

# We assume that "a.img" exists in current folder
buildimg :
	dd if=boot/boot of=lm0963.img bs=512 count=1 conv=notrunc
	dd if=boot/loader of=lm0963.img seek=1 conv=notrunc
	dd if=kernel/kernel of=lm0963.img seek=10 conv=notrunc

boot/boot : boot/boot.S include/boot.inc 
	$(ASM) $(ASMBFLAGS) -o $@ $<

boot/loader : boot/loader.S include/boot.inc
	$(ASM) $(ASMBFLAGS) -o $@ $<

lib/puts.o : lib/puts.S
	$(ASM) $(ASMKFLAGS) -o $@ $<

lib/memcpy.o : lib/memcpy.S
	$(ASM) $(ASMKFLAGS) -o $@ $<

kernel/kernel.o : kernel/kernel.c
	$(CC) $(CFLAGS) -o $@ $<

kernel/kernel : $(OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS)

