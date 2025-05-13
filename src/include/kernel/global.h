/**
 * @file: include/kernel/global.h
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#ifndef __KERNEL_GLOBAL_H_
#define __KERNEL_GLOBAL_H_

#include <kernel/screen.h>
#include <kernel/gate.h>
#include <kernel/memory.h>
#include <kernel/types.h>
#include <kernel/process/process.h>
#include <kernel/tss.h>

extern struct Screen screen;

// interrupt
extern struct Gate IDT[256];
extern u32 TSS[26];

// memory
extern struct MemoryDescriptor memory_desc;
extern u64 zone_unmapped_index;
extern char _text;
extern char _etext;
extern char _data;
extern char _edata;
extern char _rodata;
extern char _erodata;
extern char _bss;
extern char _ebss;
extern char _end;
extern u32 ZONE_DMA_INDEX;
extern u32 ZONE_NORMAL_INDEX;
extern u32 ZONE_UNMAPPED_INDEX;
extern u64* Global_CR3;

// irq
extern irq_handler irq_table[];

// process
extern struct Process* process_table[];
extern struct Process* p_current_process;
extern struct Tss process_tss[];

#endif