/**
 * @file: include/kernel/interrupt.h
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#ifndef _KERNEL_TRAPS_H_
#define _KERNEL_TRAPS_H_

void __divide_error();
void __debug();
void __nmi();
void __breakpoint();
void __overflow();
void __bounds();
void __undefined_opcode();
void __device_not_available();
void __double_fault();
void __coprocessor_segment_overrun();
void __invalid_TSS();
void __segment_not_present();
void __stack_segment_fault();
void __general_protection();
void __page_fault();
void __x87_FPU_error();
void __alignment_check();
void __machine_check();
void __SIMD_exception();
void __virtualization_exception();

void __goto_ring3();

void __irq00();
void __irq01();
void __irq02();
void __irq03();
void __irq04();
void __irq05();
void __irq06();
void __irq07();
void __irq08();
void __irq09();
void __irq10();
void __irq11();
void __irq12();
void __irq13();
void __irq14();
void __irq15();

void default_irq_handler();

#endif