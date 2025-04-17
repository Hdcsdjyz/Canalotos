/**
 * @file: include/kernel/global.h
 * @author: lhxl
 * @data: 2025-4-17
 * @version: build7
 **/

#ifndef __KERNEL_GLOBAL_H_
#define __KERNEL_GLOBAL_H_

#include "kernel/screen.h"
#include "kernel/gate.h"

extern struct Screen screen;
extern char buffer[];
extern struct Gate IDT[256];

#endif