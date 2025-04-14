/**
 * @file: kernel/main.c
 * @author: lhxl
 * @data: 2025-4-12
 * @version: build5
 **/

#include "kernel/global.h"
#include "kernel/printk.h"

void __start_kernel()
{
    screen.Resolution.x = 1440;
	screen.Resolution.y = 900;
	screen.Position.x = 0;
	screen.Position.y = 0;
	screen.CharSize.x = 8;
	screen.CharSize.y = 16;
	screen.bufferAddress = (u32*)0xFFFF800000A00000;
	screen.bufferSize = screen.Position.x * screen.Position.y * 4;
	__printk("Hello Canalotos!\n");
	__color_printk(0x00FFFF00, 0x00000000, "Hello Canalotos!\n");
	__color_printk(0xFFFF0000, 0x00000000, "This is build: %d, %x, %o, %b\n", 5, 5, 5, 5);
    while (1)
    {
		int a = 1 / 0;
    }
}
