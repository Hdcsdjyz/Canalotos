# @file: Makefile
# @author: lhxl
# @data: 2025-5-3
# @version: build9

RootDir = $(shell pwd)

MAKE = make
ASM = nasm
CC = gcc
LD = ld

ASMFLAGS = -f elf64 -w-zeroing
CCFLAGS = -mcmodel=large -fno-builtin -m64 -c -I$(RootDir)/include -fno-stack-protector -std=c23# -Wdiscarded-qualifiers -O0 -s
LDFLAGS = -b elf64-x86-64 -T kernel.lds -z muldefs -s --no-warn-rwx-segments

export MAKE ASM CC LD
export ASMFLAGS CCFLAGS LDFLAGS


all: mkdir build

mkdir:
	rm -rf ../Canalotos/bin
	rm -rf ../Canalotos/obj
	rm -rf ../Canalotos/img
	mkdir ../Canalotos/bin
	mkdir ../Canalotos/obj
	mkdir ../Canalotos/img

build:
	cd boot && $(MAKE)
	cd kernel && $(MAKE)