/**
 * @file: include/kernel/init.h
 * @author: lhxl
 * @data: 2025-5-3
 * @version: build10
 **/

#ifndef _KERNEL_INIT_H
#define _KERNEL_INIT_H

void init_screen();
void init_IDT();
void init_memory();
void init_8259A();
void init_keyboard();

#endif