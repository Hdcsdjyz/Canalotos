/**
 * @file: kernel/main.c
 * @author: lhxl
 * @data: 2025-5-1
 * @version: build8
 **/

#include <kernel/const.h>
#include <kernel/gate.h>
#include <kernel/global.h>
#include <kernel/traps.h>
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
	__printk("memory_desc.bits_map: %lx\n", *memory_desc.bits_map);
	__printk("memory_desc.bits_map + 1: %lx\n", *(memory_desc.bits_map + 1));
	page = alloc_page(ZONE_NORMAL, 64, PAGE_TABLE_MAPPED | PAGE_ACTIVE | PAGE_KERNEL);
	for (int i = 0; i <= 64; i++)
	{
		__color_printk(
			INDIGO, BLACK,
			"page%d\tattribute:%lx\taddress:%lx\t",
			i,
			(page + i)->attribute,
			(page + i)->address
		);
		i++;
		__color_printk(INDIGO,BLACK,"page%d\tattribute:%lx\taddress:%lx\n",i,
			(page + i)->attribute,(page + i)->address);
	}
	__printk("memory_desc.bits_map: %lx\n", *memory_desc.bits_map);
	__printk("memory_desc.bits_map + 1: %lx\n", *(memory_desc.bits_map + 1));

    while (1)
    {

    }
}
