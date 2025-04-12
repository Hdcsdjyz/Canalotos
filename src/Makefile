# @file: Makefile
# @author: lhxl
# @data: 2025-4-12
# @version: build5

RootDir = $(shell pwd)

MAKE = make

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