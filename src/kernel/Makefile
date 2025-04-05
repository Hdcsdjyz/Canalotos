#	@file: kernel/Makefile
#   @author: lhxl
#   @data: 2025-4-6
#	@version: build4

OutputFile = ../../Canalotos/bin/kernel/
ObjectFile = ../../Canalotos/obj/kernel/
ImgFile = ../../Canalotos/img/

ASM = nasm
CC = gcc
AS = as
LD = ld

ccAsmFlags = -E
asFlags = --64
asmFlags = -f elf64 -w-zeroing
ccFlags = -mcmodel=large -fno-builtin -m64 -c
ldFlags = -b elf64-x86-64 -T kernel.lds -s --no-warn-rwx-segments

obj = $(ObjectFile)head.o $(ObjectFile)main.o $(ObjectFile)system

.PHONY: all

all: mkdir build image

mkdir:
ifeq ($(wildcard $(ObjectFile)),)
	mkdir $(ObjectFile)
endif
ifeq ($(wildcard $(OutputFile)),)
	mkdir $(OutputFile)
endif

build: $(obj) $(bin)
	objcopy -I elf64-x86-64 -S -R ".eh_frame" -R ".comment" -O binary $(ObjectFile)system $(OutputFile)kernel.bin

image:
	cp -fv $(OutputFile)kernel.bin /mnt/floppy/
	sync
	umount /mnt/floppy

$(ObjectFile)%.o: %.asm
	$(ASM) $< $(asmFlags) -o $@

$(ObjectFile)%.o: %.c
	$(CC) $< $(ccFlags) -o $@

$(ObjectFile)system: $(obj)
	$(LD) $^ $(ldFlags) -o $@