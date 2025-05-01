/**
 * @file: include/kernel/traps.h
 * @author: lhxl
 * @data: 2025-4-17
 * @version: build7
 **/

#ifndef _KERNEL_TRAPS_H_
#define _KERNEL_TRAPS_H_

void divide_error();
void debug();
void nmi();
void breakpoint();
void overflow();
void bounds();
void undefined_opcode();
void device_not_available();
void double_fault();
void coprocessor_segment_overrun();
void invalid_TSS();
void segment_not_present();
void stack_segment_fault();
void general_protection();
void page_fault();
void x87_FPU_error();
void alignment_check();
void machine_check();
void SIMD_exception();
void virtualization_exception();

void set_tss(u64 rsp0, u64 rsp1, u64 rsp2, u64 ist1, u64 ist2, u64 ist3, u64 ist4, u64 ist5, u64 ist6, u64 ist7);

#endif