/**
 * @file: include/kernel/process/thread.h
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#ifndef _KERNEL_PROCESS_THREAD_H_
#define _KERNEL_PROCESS_THREAD_H_

#include <kernel/types.h>

struct Thread
{
	u64 rsp0;	///< rsp of caller
	u64 rip;
	u64 rsp;
	u64 fs;
	u64 gs;
	u64 cr2;
	u64 trap;
	u64 error;
};

#endif