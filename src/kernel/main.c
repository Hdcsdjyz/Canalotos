/**
 * @file: kernel/main.c
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#include <kernel/gate.h>
#include <kernel/global.h>
#include <kernel/printk.h>
#include <kernel/init.h>
#include <kernel/memory.h>
#include <kernel/tss.h>

void the_first_process();

void __kernel_main()
{
	init_screen();
	init_IDT();
	LOAD_TR(7)
	set_tss(0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00);
	init_memory();
	init_8259A();
    while (1)
    {

    }
}