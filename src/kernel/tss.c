/**
 * @file: kernel/tss.c
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#include <kernel/tss.h>
#include <kernel/global.h>

void set_tss(u64 rsp0, u64 rsp1, u64 rsp2, u64 ist1, u64 ist2, u64 ist3, u64 ist4, u64 ist5, u64 ist6, u64 ist7)
{
	*(u64*)(TSS + 1) = rsp0;
	*(u64*)(TSS + 3) = rsp1;
	*(u64*)(TSS + 5) = rsp2;
	*(u64*)(TSS + 9) = ist1;
	*(u64*)(TSS + 11) = ist2;
	*(u64*)(TSS + 13) = ist3;
	*(u64*)(TSS + 15) = ist4;
	*(u64*)(TSS + 17) = ist5;
	*(u64*)(TSS + 19) = ist6;
	*(u64*)(TSS + 21) = ist7;
}

void set_tss_struct(struct Tss tss)
{
	*(u64*)(TSS + 1) = tss.rsp0;
	*(u64*)(TSS + 3) = tss.rsp1;
	*(u64*)(TSS + 5) = tss.rsp2;
	*(u64*)(TSS + 9) = tss.ist1;
	*(u64*)(TSS + 11) = tss.ist2;
	*(u64*)(TSS + 13) = tss.ist3;
	*(u64*)(TSS + 15) = tss.ist4;
	*(u64*)(TSS + 17) = tss.ist5;
	*(u64*)(TSS + 19) = tss.ist6;
	*(u64*)(TSS + 21) = tss.ist7;
}