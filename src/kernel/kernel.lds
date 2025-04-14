/**
 * @file: kernel/kernel.lds
 * @author: lhxl
 * @data: 2025-4-14
 * @version: build6
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
	.bss :
	{
		_bss = .;
		*(.bss)
		_ebss = .;
	}
	_end = .;
}
