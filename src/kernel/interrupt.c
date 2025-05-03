/**
 * @file: kernel/traps.c
 * @author: lhxl
 * @data: 2025-5-3
 * @version: build10
 **/

#include <kernel/types.h>
#include <kernel/global.h>
#include <kernel/printk.h>
#include <kernel/const.h>
#include <kernel/init.h>
#include <kernel/interrupt.h>

PRIVATE void init_IDT_DESC(u8 IDTIndex, u8 gateType, u8 privilege, int_handler handler);

void init_IDT()
{
	init_IDT_DESC(0x00, DA_386IGate, DA_DPL0, __divide_error);
	init_IDT_DESC(0x01, DA_386IGate, DA_DPL0, __debug);
	init_IDT_DESC(0x02, DA_386IGate, DA_DPL0, __nmi);
	init_IDT_DESC(0x03, DA_386IGate, DA_DPL3, __breakpoint);
	init_IDT_DESC(0x04, DA_386IGate, DA_DPL3, __overflow);
	init_IDT_DESC(0x05, DA_386IGate, DA_DPL0, __bounds);
	init_IDT_DESC(0x06, DA_386IGate, DA_DPL0, __undefined_opcode);
	init_IDT_DESC(0x07, DA_386IGate, DA_DPL0, __device_not_available);
	init_IDT_DESC(0x08, DA_386IGate, DA_DPL0, __double_fault);
	init_IDT_DESC(0x09, DA_386IGate, DA_DPL0, __coprocessor_segment_overrun);
	init_IDT_DESC(0x0A, DA_386IGate, DA_DPL0, __invalid_TSS);
	init_IDT_DESC(0x0B, DA_386IGate, DA_DPL0, __segment_not_present);
	init_IDT_DESC(0x0C, DA_386IGate, DA_DPL0, __stack_segment_fault);
	init_IDT_DESC(0x0D, DA_386IGate, DA_DPL0, __general_protection);
	init_IDT_DESC(0x0E, DA_386IGate, DA_DPL0, __page_fault);
	init_IDT_DESC(0x10, DA_386IGate, DA_DPL0, __x87_FPU_error);
	init_IDT_DESC(0x11, DA_386IGate, DA_DPL0, __alignment_check);
	init_IDT_DESC(0x12, DA_386IGate, DA_DPL0, __machine_check);
	init_IDT_DESC(0x13, DA_386IGate, DA_DPL0, __SIMD_exception);
	init_IDT_DESC(0x14, DA_386IGate, DA_DPL0, __irq00);
	init_IDT_DESC(0x20, DA_386IGate, DA_DPL0, __irq01);
	init_IDT_DESC(0x21, DA_386IGate, DA_DPL0, __irq02);
	init_IDT_DESC(0x22, DA_386IGate, DA_DPL0, __irq03);
	init_IDT_DESC(0x23, DA_386IGate, DA_DPL0, __irq04);
	init_IDT_DESC(0x24, DA_386IGate, DA_DPL0, __irq05);
	init_IDT_DESC(0x25, DA_386IGate, DA_DPL0, __irq06);
	init_IDT_DESC(0x26, DA_386IGate, DA_DPL0, __irq07);
	init_IDT_DESC(0x27, DA_386IGate, DA_DPL0, __irq08);
	init_IDT_DESC(0x28, DA_386IGate, DA_DPL0, __irq09);
	init_IDT_DESC(0x29, DA_386IGate, DA_DPL0, __irq10);
	init_IDT_DESC(0x2A, DA_386IGate, DA_DPL0, __irq11);
	init_IDT_DESC(0x2B, DA_386IGate, DA_DPL0, __irq12);
	init_IDT_DESC(0x2C, DA_386IGate, DA_DPL0, __irq13);
	init_IDT_DESC(0x2D, DA_386IGate, DA_DPL0, __irq14);
	init_IDT_DESC(0x2E, DA_386IGate, DA_DPL0, __irq15);
}

void do_divide_error(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "divide_error, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_debug(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "debug, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_nmi(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "nmi, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_breakpoint(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "breakpoint, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_overflow(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "overflow, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_bounds(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "bounds, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_undefined_opcode(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "undefined_opcode, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_device_not_available(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "device_not_available, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_double_fault(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "double_fault, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_coprocessor_segment_overrun(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "coprocessor_segment_overrun, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_invalid_TSS(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "invalid_tss, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	if(error_code & 0x01)
	{
		__color_printk(RED, BLACK, "The exception occurred during delivery of an event external to the program,such as an interrupt or an earlier exception.\n");
	}
	if(error_code & 0x02)
	{
		__color_printk(RED, BLACK, "Refers to a gate descriptor in the IDT;\n");
	}
	else
	{
		__color_printk(RED, BLACK, "Refers to a descriptor in the GDT or the current LDT;\n");
	}
	if((error_code & 0x02) == 0)
	{
		if(error_code & 0x04)
		{
			__color_printk(RED, BLACK, "Refers to a segment or gate descriptor in the LDT;\n");
		}
		else
		{
			__color_printk(RED, BLACK, "Refers to a descriptor in the current GDT;\n");
		}
	}
	__color_printk(RED, BLACK, "Segment Selector Index:%x\n", error_code & 0xfff8);
	while(1);
}

void do_segment_not_present(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "segment_not_present,ERROR_CODE:%12lx,RSP:%12lx,RIP:%12lx\n", error_code, rsp, *p);

	if(error_code & 0x01)
	{
		__color_printk(RED, BLACK, "The exception occurred during delivery of an event external to the program,such as an interrupt or an earlier exception.\n");
	}
	if(error_code & 0x02)
	{
		__color_printk(RED, BLACK, "Refers to a gate descriptor in the IDT;\n");
	}
	else
	{
		__color_printk(RED, BLACK, "Refers to a descriptor in the GDT or the current LDT;\n");
	}
	if((error_code & 0x02) == 0)
	{
		if(error_code & 0x04)
		{
			__color_printk(RED, BLACK, "Refers to a segment or gate descriptor in the LDT;\n");
		}
		else
		{
			__color_printk(RED, BLACK, "Refers to a descriptor in the current GDT;\n");
		}
	}
	__color_printk(RED, BLACK, "Segment Selector Index:%#010x\n",error_code & 0xfff8);
	while(1);
}

void do_stack_segment_fault(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "stack_segment_fault,ERROR_CODE:%12lx,RSP:%12lx,RIP:%12lx\n", error_code, rsp, *p);

	if(error_code & 0x01)
	{
		__color_printk(RED, BLACK, "The exception occurred during delivery of an event external to the program.\n");
	}
	if(error_code & 0x02)
	{
		__color_printk(RED, BLACK, "Refers to a gate descriptor in the IDT;\n");
	}
	else
	{
		__color_printk(RED, BLACK, "Refers to a descriptor in the GDT or the current LDT;\n");
	}

	if((error_code & 0x02) == 0)
	{
		if(error_code & 0x04)
		{
			__color_printk(RED, BLACK, "Refers to a segment or gate descriptor in the LDT;\n");
		}
		else
		{
			__color_printk(RED, BLACK, "Refers to a descriptor in the current GDT;\n");
		}
	}
	__color_printk(RED, BLACK, "Segment Selector Index:%x\n", error_code & 0xfff8);
	while(1);
}

void do_general_protection(u64 rsp,u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "general_protection, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	if(error_code & 0x01)
	{
		__color_printk(RED, BLACK, "The exception occurred during delivery of an event external to the program.\n");
	}
	if(error_code & 0x02)
	{
		__color_printk(RED, BLACK, "Refers to a gate descriptor in the IDT;\n");
	}
	else
	{
		__color_printk(RED, BLACK, "Refers to a descriptor in the GDT or the current LDT;\n");
	}
	if((error_code & 0x02) == 0)
	{
		if(error_code & 0x04)
		{
			__color_printk(RED, BLACK, "Refers to a segment or gate descriptor in the LDT;\n");
		}
		else
		{
			__color_printk(RED, BLACK, "Refers to a descriptor in the current GDT;\n");
		}
	}
	__color_printk(RED, BLACK, "Segment Selector Index:%x\n",error_code & 0xfff8);
	while(1);
}

void do_page_fault(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	u64 cr2 = 0;
	__asm__	__volatile__(
		"movq	%%cr2,	%0"
		: "=r"(cr2)
		:
		: "memory"
	);
	__color_printk(RED, BLACK, "page_fault, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	if(!(error_code & 0x01))
	{
		__color_printk(RED, BLACK, "Page Not-Present,\t");
	}
	if(error_code & 0x02)
	{
		__color_printk(RED, BLACK, "Write Cause Fault,\t");
	}
	else
	{
		__color_printk(RED, BLACK, "Read Cause Fault,\t");
	}
	if(error_code & 0x04)
	{
		__color_printk(RED, BLACK, "Fault in user(3)\t");
	}
	else
	{
		__color_printk(RED, BLACK, "Fault in supervisor(0,1,2)\t");
	}
	if(error_code & 0x08)
	{
		__color_printk(RED, BLACK, ",Reserved Bit Cause Fault\t");
	}
	if(error_code & 0x10)
	{
		__color_printk(RED, BLACK, ",Instruction fetch Cause Fault");
	}
	__color_printk(RED, BLACK, "\n");
	__color_printk(RED, BLACK, "CR2:%12lx\n",cr2);
	while(1);
}

void do_coprocessor_error(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "coprocessor_error, ERROR_CODE:%12lx, RSP:%x, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_x87_FPU_error(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "x87_FPU_error, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_alignment_check(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "alignment_check, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_machine_check(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "machine_check, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_SIMD_exception(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "SIMD_exception, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void do_virtualization_exception(u64 rsp, u64 error_code)
{
	u64* p = (u64*)(rsp + 0x98);
	__color_printk(RED, BLACK, "virtualization_exception, ERROR_CODE:%12lx, RSP:%12lx, RIP:%12lx\n", error_code, rsp, *p);
	while(1);
}

void set_tss(u64 rsp0, u64 rsp1, u64 rsp2, u64 ist1, u64 ist2, u64 ist3, u64 ist4, u64 ist5, u64 ist6, u64 ist7)
{
	*(u64*)(TSS + 1) = rsp0;
	*(u64*)(TSS + 3) = rsp1;
	*(u64*)(TSS + 5) = rsp2;
	*(u64*)(TSS + 9) = ist1;
	*(u64*)(TSS + 11) = ist2;
	*(u64*)(TSS + 13) = ist3;
	*(u64*)(TSS + 15) = ist4;
	*(u64*)(TSS + 17) = ist5;
	*(u64*)(TSS + 19) = ist6;
	*(u64*)(TSS + 21) = ist7;
}

PRIVATE void init_IDT_DESC(u8 IDTIndex, u8 gateType, u8 privilege, int_handler handler)
{
	struct Gate* p_gate = &IDT[IDTIndex];
	u64 base = (u64)handler;
	p_gate->offsetLow = base & 0xFFFF;
	p_gate->selector = 0x8;
	p_gate->paramCount = 0;
	p_gate->attribute = gateType | privilege;
	p_gate->offsetMid = base >> 16 & 0xFFFF;
	p_gate->offsetHigh = base >> 32 & 0xFFFFFFFF;
	p_gate->zero = 0;
}