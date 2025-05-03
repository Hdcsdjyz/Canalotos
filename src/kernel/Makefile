# @file: kernel/Makefile
# @author: lhxl
# @data: 2025-5-3
# @version: build9

OutputFile = ../../Canalotos/bin/kernel/
ObjectFile = ../../Canalotos/obj/kernel/
ImgFile = ../../Canalotos/img/

C_INCLUDE = ../include

obj = $(ObjectFile)head.o\
	$(ObjectFile)main.o\
	$(ObjectFile)printk.o\
	$(ObjectFile)global.o\
	$(ObjectFile)interrupt.o\
	$(ObjectFile)fault.o\
	$(ObjectFile)memory.o\
	$(ObjectFile)lib/lib.o\
	$(ObjectFile)lib/string.o\
	$(ObjectFile)irq/irq.o\
	$(ObjectFile)irq/8259A.o

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
	cd irq && $(MAKE)

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