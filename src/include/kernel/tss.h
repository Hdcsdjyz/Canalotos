/**
 * @file: include/kernel/tss.h
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#ifndef _KERNEL_TSS_H_
#define _KERNEL_TSS_H_

#include <kernel/types.h>

struct Tss
{
	u32 reserved0;
	u64 rsp0;
	u64 rsp1;
	u64 rsp2;
	u64 reserved1;
	u64 ist1;
	u64 ist2;
	u64 ist3;
	u64 ist4;
	u64 ist5;
	u64 ist6;
	u64 ist7;
	u64 reserved2;
	u16 reserved3;
	u16 iomap;
} __attribute__((packed));

void set_tss(u64 rsp0, u64 rsp1, u64 rsp2, u64 ist1, u64 ist2, u64 ist3, u64 ist4, u64 ist5, u64 ist6, u64 ist7);
void set_tss_struct(struct Tss tss);

#endif