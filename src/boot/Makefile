#	@file: boot/Makefile
#   @author: lhxl
#   @data: 2025-4-4
#	@version: build2

OutputFile = ../../Canalotos/bin/boot/
ImgFile = ../../Canalotos/img/
bin = $(OutputFile)boot.bin $(OutputFile)loader.bin $(OutputFile)kernel.bin

ASM = nasm

.PHONY: all

all: mkdir build image

mkdir:
ifeq ($(wildcard $(OutputFile)),)
	mkdir $(OutputFile)
endif

build: $(bin)

image:
	dd if=/dev/zero of=$(ImgFile)boot.img bs=512 count=2880
	dd if=$(OutputFile)boot.bin of=$(ImgFile)boot.img bs=512 count=1 conv=notrunc
	mount $(ImgFile)boot.img /mnt/floppy -o loop
	sudo cp -fv $(OutputFile)loader.bin /mnt/floppy/
	sudo cp -fv $(OutputFile)kernel.bin /mnt/floppy/
	sync
	umount /mnt/floppy

$(OutputFile)%.bin: %.asm
	$(ASM) $< -o $@