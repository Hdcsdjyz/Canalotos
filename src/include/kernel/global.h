/**
 * @file: include/kernel/global.h
 * @author: lhxl
 * @data: 2025-5-3
 * @version: build8
 **/

#ifndef __KERNEL_GLOBAL_H_
#define __KERNEL_GLOBAL_H_

#include <kernel/screen.h>
#include <kernel/gate.h>
#include <kernel/memory.h>
#include <kernel/types.h>

extern struct Screen screen;

// interrupt
extern struct Gate IDT[256];
extern u32 TSS[26];

// memory
extern struct MemoryDescriptor memory_desc;
extern u64 zone_unmapped_index;
extern char _text;
extern char _etext;
extern char _edata;
extern char _end;
extern u32 ZONE_DMA_INDEX;
extern u32 ZONE_NORMAL_INDEX;
extern u32 ZONE_UNMAPPED_INDEX;
extern u64* Global_CR3;

// irq
extern irq_handler irq_table[];

#endif