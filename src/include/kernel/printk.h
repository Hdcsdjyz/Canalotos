/**
 * @file: include/kernel/printk.h
 * @author: lhxl
 * @data: 2025-4-12
 * @version: build5
 **/

#ifndef _KERNEL_PRINTK_H
#define _KERNEL_PRINTK_H

#include <stdarg.h>

int __printk(const char* format, ...);
int __color_printk(u32 frontColor, u32 backgroundColor, const char* format, ...);
int __vsprintf(char* buffer, const char* format, va_list args);
void __putchar(u32 frontColor, u32 backgroundColor, u8 character);

#endif
