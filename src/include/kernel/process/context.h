/**
 * @file: include/kernel/process/context.h
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#ifndef _KERNEL_PROCESS_CONTEXT_H_
#define _KERNEL_PROCESS_CONTEXT_H_

#include <kernel/types.h>

struct Context
{
	u64 r15;
	u64 r14;
	u64 r13;
	u64 r12;
	u64 r11;
	u64 r10;
	u64 r9;
	u64 r8;
	u64 rbx;
	u64 rcx;
	u64 rdx;
	u64 rsi;
	u64 rdi;
	u64 rbp;
	u64 ds;
	u64 es;
	u64 rax;
	u64 func;
	u64 error;
	u64 rip;
	u64 cs;
	u64 rflags;
	u64 rsp;
	u64 ss;
};

#endif