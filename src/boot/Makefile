OutputFile = ../../Canalotos/bin/boot/
ImgFile = ../../Canalotos/img/
bin = $(OutputFile)boot.bin

ASM = nasm

.PHONY: all
all: mkdir build image

mkdir:
ifeq ($(wildcard $(OutputFile)),)
	mkdir ../../Canalotos/bin/boot
endif

build: $(bin)

image:
	dd if=$(OutputFile)boot.bin of=$(ImgFile)boot.img bs=512 count=1 conv=notrunc

$(OutputFile)%.bin: %.asm
	$(ASM) $< -o $@