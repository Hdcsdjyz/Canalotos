/**
 * @file: kernel/lib/lib.h
 * @author: lhxl
 * @data: 2025-5-3
 * @version: build10
 **/

#include <kernel/types.h>

void __port_write_byte(u16 port, u8 data);
u8 __port_read_byte(u16 port);

void __enable_irq(int irq);
void __disable_irq(int irq);