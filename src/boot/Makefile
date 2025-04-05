#	@file: boot/Makefile
#   @author: lhxl
#   @data: 2025-4-6
#	@version: build4

OutputFile = ../../Canalotos/bin/boot/
ImgFile = ../../Canalotos/img/
bin = $(OutputFile)boot.bin $(OutputFile)loader.bin

ASM = nasm

.PHONY: all

all: mkdir build image

mkdir:
ifeq ($(wildcard $(OutputFile)),)
	mkdir $(OutputFile)
endif
ifeq ($(wildcard $(ImgFile)),)
	mkdir $(ImgFile)
endif

build: $(bin)

image:
	dd if=/dev/zero of=$(ImgFile)boot.img bs=512 count=2880
	dd if=$(OutputFile)boot.bin of=$(ImgFile)boot.img bs=512 count=1 conv=notrunc
	mount $(ImgFile)boot.img /mnt/floppy -o loop
	cp -fv $(OutputFile)loader.bin /mnt/floppy/
	sync

$(OutputFile)%.bin: %.asm
	$(ASM) $< -o $@