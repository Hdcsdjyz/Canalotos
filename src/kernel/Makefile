# @file: kernel/Makefile
# @author: lhxl
# @data: 2025-4-17
# @version: build7

OutputFile = ../../Canalotos/bin/kernel/
ObjectFile = ../../Canalotos/obj/kernel/
ImgFile = ../../Canalotos/img/

MAKE = make
ASM = nasm
CC = gcc
LD = ld

ASMFLAGS = -f elf64 -w-zeroing
CCFLAGS = -mcmodel=large -fno-builtin -m64 -c -I ../include -std=c23 -fno-stack-protector
LDFLAGS = -b elf64-x86-64 -T kernel.lds -s --no-warn-rwx-segments

obj = $(ObjectFile)head.o\
	$(ObjectFile)main.o\
	$(ObjectFile)printk.o\
	$(ObjectFile)global.o\
	$(ObjectFile)traps.o\
	$(ObjectFile)fault.o\
	$(ObjectFile)lib/*.o

.PHONY: all

all: mkdir build_sub build image

mkdir:
ifeq ($(wildcard $(ObjectFile)),)
	mkdir $(ObjectFile)
endif
ifeq ($(wildcard $(OutputFile)),)
	mkdir $(OutputFile)
endif

build_sub:
	cd lib && $(MAKE)

build: $(OutputFile)kernel.bin

image:
	cp -fv $(OutputFile)kernel.bin /mnt/floppy/
	sync
	umount /mnt/floppy

$(ObjectFile)%.o: %.asm
	$(ASM) $< $(ASMFLAGS) -o $@

$(ObjectFile)%.o: %.c
	$(CC) $< $(CCFLAGS) -o $@

$(OutputFile)kernel.bin : $(obj)
	$(LD) $(obj) $(LDFLAGS) -o $(ObjectFile)system
	objcopy $(ObjectFile)system -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary $(OutputFile)kernel.bin