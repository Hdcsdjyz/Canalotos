/**
 * @file: kernel/kernel.lds
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(__start)
SECTIONS
{
	. = 0xffff800000100000;
	.text :
	{
		_text = .;
		*(.text)
		_etext = .;
	}
	. = ALIGN(8);
	.data :
	{
		_data = .;
		*(.data)
		_edata = .;
	}
	.rodata :
	{
		_rodata = .;
		*(.rodata)
		_erodata = .;
	}
	. = ALIGN(16384);
	.data.__init :
	{
		*(.data.__init)
	}
	.bss :
	{
		_bss = .;
		*(.bss)
		_ebss = .;
	}
	_end = .;
}
