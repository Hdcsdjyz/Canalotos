/**
 * @file: include/kernel/process/process.h
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#ifndef _KERNEL_PROCESS_PROCESS_H_
#define _KERNEL_PROCESS_PROCESS_H_

#include <kernel/process/context.h>
#include <kernel/process/thread.h>

enum ProcessFlag : u64
{
	KERNEL = 1
};

enum ProcessState : u64
{
	RUNNING = 1
};

struct Process
{
	pid_t pid;
	char name[32];
	enum ProcessFlag flag;
	enum ProcessState state;
	struct Thread* thread;
	struct Context* context;
};

void init_process(struct Process* process, const char* name, u64 flag);
void init_process_thread(struct Process* process);
void init_process_context(struct Process* process, func fn, u64 arg);

#endif