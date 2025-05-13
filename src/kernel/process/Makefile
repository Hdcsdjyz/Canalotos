# @file: process/Makefile
# @author: lhxl
# @data: 2025-5-13
# @version: build10

ObjectFile = ../../../Canalotos/obj/kernel/process/

C_INCLUDE = ../../include

obj = $(ObjectFile)process.o

.PHONY: all

all: mkdir build

mkdir:
ifeq ($(wildcard $(ObjectFile)),)
	mkdir $(ObjectFile)
endif

build: $(obj)

$(ObjectFile)%.o: %.c
	$(CC) $< $(CCFLAGS) -o $@