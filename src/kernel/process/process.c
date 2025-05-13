/**
 * @file: kernel/process/process.c
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#include <kernel/lib/string.h>
#include <kernel/process/process.h>
#include <kernel/tss.h>
#include <kernel/memory.h>
#include <kernel/const.h>
#include <kernel/printk.h>
#include <kernel/interrupt.h>

void do_process();
u64 the_first_process(u64 arg);

void init_process(struct Process* process, const char* name, u64 flag)
{
	struct Page* page = alloc_page(ZONE_NORMAL, 1, PAGE_TABLE_MAPPED | PAGE_ACTIVE | PAGE_KERNEL);
	process = (struct Process*)phy2vir(page->address);
	memset(process, 0, sizeof(*process));
	process->pid = 0;
	process->flag = flag;
	memcpy(process->name, name, strlen(name) + 1);
	init_process_context(process, the_first_process, 0);
	init_process_thread(process);
	process->state = RUNNING;
}

void init_process_thread(struct Process* process)
{
	struct Thread* thread = (struct Thread*)(process + 1);
	memset(thread, 0, sizeof(*thread));
	thread->rsp0 = (u64)process + PROCESS_STACK_SIZE;
	if (!(process->flag & KERNEL))
	{
		thread->rip = process->context->rip = (u64)__goto_ring3;
	}
	else
	{
		thread->rip = process->context->rip;
	}
	thread->rsp = (u64)process + PROCESS_STACK_SIZE - sizeof(struct Context);
	thread->fs = SELECTOR_KERNEL_DATA;
	thread->gs = SELECTOR_KERNEL_DATA;
	thread->cr2 = 0;
	thread->error = 0;
	thread->trap = 0;
}

void init_process_context(struct Process* process, func fn, u64 arg)
{
	struct Context* context = (struct Context*)(process + PROCESS_STACK_SIZE - sizeof(struct Context));
	memset(context, 0, sizeof(*context));
	context->ds = SELECTOR_KERNEL_DATA;
	context->es = SELECTOR_KERNEL_DATA;
	context->cs = SELECTOR_KERNEL_CODE;
	context->ss = SELECTOR_KERNEL_DATA;
	context->rflags = 1 << 9;
	context->rip = (u64)do_process;
	context->rdx = arg;
	context->rbx = (u64)fn;
}

void do_process()
{

}

u64 the_first_process(u64 arg)
{
	while (true)
	{
		__printk("the_first_process\n");
	}
}