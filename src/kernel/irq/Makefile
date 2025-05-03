#	@file: kernel/irq/Makefile
#   @author: lhxl
#   @data: 2025-5-3
#	@version: build9

ObjectFile = ../../../Canalotos/obj/kernel/irq/

C_INCLUDE = ../../include

obj = $(ObjectFile)8259A.o\
	$(ObjectFile)irq.o

.PHONY: all

all: mkdir build

mkdir:
ifeq ($(wildcard $(ObjectFile)),)
	mkdir $(ObjectFile)
endif

build: $(obj)

$(ObjectFile)%.o: %.asm
	$(ASM) $< $(ASMFLAGS) -o $@

$(ObjectFile)%.o: %.c
	$(CC) $< $(CCFLAGS) -o $@