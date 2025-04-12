#	@file: lib/Makefile
#   @author: lhxl
#   @data: 2025-4-12
#	@version: build5

ObjectFile = ../../../Canalotos/obj/kernel/lib/

ASM = nasm

ASMFLAGS = -f elf64 -w-zeroing

obj = $(ObjectFile)string.o

.PHONY: all

all: mkdir build

mkdir:
ifeq ($(wildcard $(ObjectFile)),)
	mkdir $(ObjectFile)
endif

build: $(obj)

$(ObjectFile)%.o: %.asm
	$(ASM) $< $(ASMFLAGS) -o $@