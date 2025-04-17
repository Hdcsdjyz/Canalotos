/**
 * @file: kernel/main.c
 * @author: lhxl
 * @data: 2025-4-17
 * @version: build7
 **/

#include "kernel/global.h"
#include "kernel/printk.h"
#include "kernel/init.h"

void __kernel_main()
{
	init_screen();
	init_IDT();
	__printk("Hello Canalotos!\n");
	__color_printk(0x00FF0000, 0x00000000, "This is build: %d, %x, %o, %b\n", 5, 5, 5, 5);
    while (1)
    {
		int a = 1 / 0;
    }
}
