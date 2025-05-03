/**
 * @file: kernel/main.c
 * @author: lhxl
 * @data: 2025-5-3
 * @version: build9
 **/

#include <kernel/const.h>
#include <kernel/gate.h>
#include <kernel/global.h>
#include <kernel/interrupt.h>
#include <kernel/printk.h>
#include <kernel/init.h>
#include <kernel/memory.h>

void __kernel_main()
{
	init_screen();
	init_IDT();
	LOAD_TR(8)
	set_tss(0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00, 0xFFFF800000007C00);
	init_memory();
	struct Page* page = nullptr;
	page = alloc_page(ZONE_NORMAL, 64, PAGE_TABLE_MAPPED | PAGE_ACTIVE | PAGE_KERNEL);
	init_8259A();
    while (1)
    {

    }
}
