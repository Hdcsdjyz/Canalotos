/**
 * @file: kernel/global.c
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#include <kernel/const.h>
#include <kernel/global.h>

struct Screen screen;

// memory
struct MemoryDescriptor memory_desc;
u64 zone_unmapped_index;
char _text;
char _etext;
char _data;
char _edata;
char _rodata;
char _erodata;
char _bss;
char _ebss;
char _end;
u32 ZONE_DMA_INDEX = 0;
u32 ZONE_NORMAL_INDEX = 0;
u32 ZONE_UNMAPPED_INDEX = 0;
u64* Global_CR3 = nullptr;

// irq
irq_handler irq_table[NR_IRQ];

// process
struct Process __init __attribute__((section(".data.__init")));
struct Process* process_table[NR_PROCESS] = { &__init };
struct Tss process_tss[NR_CPUS]           = {
	{
		.reserved0 = 0,
		.rsp0 = (u64)&__init + PROCESS_STACK_SIZE,
		.rsp1 = (u64)&__init + PROCESS_STACK_SIZE,
		.rsp2 = (u64)&__init + PROCESS_STACK_SIZE,
		.reserved1 = 0,
		.ist1 = 0xFFFF800000007C00,
		.ist2 = 0xFFFF800000007C00,
		.ist3 = 0xFFFF800000007C00,
		.ist4 = 0xFFFF800000007C00,
		.ist5 = 0xFFFF800000007C00,
		.ist6 = 0xFFFF800000007C00,
		.ist7 = 0xFFFF800000007C00,
		.reserved2 = 0,
		.reserved3 = 0,
		.iomap = 0
	}
};