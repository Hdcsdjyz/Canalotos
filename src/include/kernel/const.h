/**
 * @file: include/kernel/const.h
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#ifndef _KERNEL_CONST_H_
#define _KERNEL_CONST_H_

// boolean
#define TRUE 1
#define FALSE 0
#define NULL 0

// color
#define BLACK	0x00000000
#define BLUE	0x000000FF
#define GREEN	0x0000FF00
#define INDIGO	0x004B0082
#define RED		0x00FF0000
#define ORANGE	0x00FF7777
#define WHITE	0x00FFFFFF

// irq
#define NR_IRQ	16

// GDT
#define SELECTOR_KERNEL_CODE 0x8
#define SELECTOR_KERNEL_DATA 0x10

// process
#define PROCESS_STACK_SIZE 16384
#define NR_PROCESS 1
#define NR_CPUS 1

#endif