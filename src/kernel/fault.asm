; @file: kernel/fault.asm
; @author: lhxl
; @data: 2025-4-17
; @version: build7

%macro GET_CURRENT 1
	mov     %1, -32768
	and     %1, rsp
%endmacro

REG_R15     equ 0x00
REG_R14     equ 0x08
REG_R13     equ 0x10
REG_R12     equ 0x18
REG_R11     equ 0x20
REG_R10     equ 0x28
REG_R9      equ 0x30
REG_R8      equ 0x38
REG_RBX     equ 0x40
REG_RCX     equ 0x48
REG_RDX     equ 0x50
REG_RSI     equ 0x58
REG_RDI     equ 0x60
REG_RBP     equ 0x68
REG_DS      equ 0x70
REG_ES      equ 0x78
REG_RAX     equ 0x80
FUNC        equ 0x88
ERRCODE     equ 0x90
REG_RIP     equ 0x98
REG_CS      equ 0xA0
REG_RFLAGS  equ 0xA8
REG_OLDRSP  equ 0xB0
REG_OLDSS   equ 0xB8

global divide_error
global debug
global nmi
global breakpoint
global overflow
global bounds
global undefined_opcode
global device_not_available
global double_fault
global coprocessor_segment_overrun
global invalid_TSS
global segment_not_present
global stack_segment_fault
global general_protection
global page_fault
global x87_FPU_error
global alignment_check
global machine_check
global SIMD_exception
global virtualization_exception

extern do_divide_error
extern do_debug
extern do_nmi
extern do_breakpoint
extern do_overflow
extern do_bounds
extern do_undefined_opcode
extern do_device_not_available
extern do_double_fault
extern do_coprocessor_segment_overrun
extern do_invalid_TSS
extern do_segment_not_present
extern do_stack_segment_fault
extern do_general_protection
extern do_page_fault
extern do_x87_FPU_error
extern do_alignment_check
extern do_machine_check
extern do_SIMD_exception
extern do_virtualization_exception

RestoreRegister:
	pop     r15
	pop     r14
	pop     r13
	pop     r12
	pop     r11
	pop     r10
	pop     r9
	pop     r8
	pop     rbx
	pop     rcx
	pop     rdx
	pop     rsi
	pop     rdi
	pop     rbp
	pop     rax
	mov     ds, rax
	pop     rax
	mov     es, rax
	pop     rax
	add     rsp, 0x10
	iret

ret_from_exception:
ret_from_intr:
	jmp     RestoreRegister

error_code:
	push    rax
	mov     rax, es
	push    rax
	mov     rax, ds
	push    rax
	xor     rax, rax
	push    rbp
	push    rdi
	push    rsi
	push    rdx
	push    rcx
	push    rbx
	push    r8
	push    r9
	push    r10
	push    r11
	push    r12
	push    r13
	push    r14
	push    r15
	cld
	mov     rsi, [rsp + ERRCODE]
	mov     rdx, [rsp + FUNC]
	mov     rdi, 0x10
	mov     ds, rdi
	mov     es, rdi
	mov     rdi, rsp
	call    rdx
	jmp     ret_from_exception
divide_error:
	push    0
	push    rax
	lea     rax, [rel do_divide_error]
	xchg    [rsp], rax
	jmp     error_code

debug:
	push    0
	push    rax
	lea     rax, [rel do_debug]
	xchg    [rsp], rax
	jmp     error_code

nmi:
	push	rax
	cld
	push    rax
	push    rax
	mov    rax, es
	push    rax
	mov     rax, ds
	push    rax
	xor     rax, rax
	push    rbp
	push    rdi
	push    rsi
	push    rdx
	push    rcx
	push    rbx
	push    r8
	push    r9
	push    r10
	push    r11
	push    r12
	push    r13
	push    r14
	push    r15
	mov     rdx, 0x10
	mov     ds, rdx
	mov     es, rdx
	mov     rsi, 0
	mov     rdi, rsp
	call    do_nmi
	jmp     RestoreRegister

breakpoint:
	push    0
	push    rax
	lea     rax, [rel do_breakpoint]
	xchg    [rsp], rax
	jmp     error_code

overflow:
	push    0
	push    rax
	lea     rax, [rel do_overflow]
	xchg    [rsp], rax
	jmp     error_code

bounds:
	push    0
	push    rax
	lea     rax, [rel do_bounds]
	xchg    [rsp], rax
	jmp     error_code

undefined_opcode:
	push    0
	push    rax
	lea     rax, [rel do_undefined_opcode]
	xchg    [rsp], rax
	jmp     error_code

device_not_available:
	push    0
	push    rax
	lea     rax, [rel do_device_not_available]
	xchg    [rsp], rax
	jmp     error_code

double_fault:
	push    0
	push    rax
	lea     rax, [rel do_double_fault]
	xchg    [rsp], rax
	jmp     error_code

coprocessor_segment_overrun:
	push    0
	push    rax
	lea     rax, [rel do_coprocessor_segment_overrun]
	xchg    [rsp], rax
	jmp     error_code

invalid_TSS:
	push    rax
	lea     rax, [rel do_invalid_TSS]
	xchg    [rsp], rax
	jmp     error_code

segment_not_present:
	push    rax
	lea     rax, [rel do_segment_not_present]
	xchg    [rsp], rax
	jmp     error_code

stack_segment_fault:
	push    rax
	lea     rax, [rel do_stack_segment_fault]
	xchg    [rsp], rax
	jmp     error_code

general_protection:
	push    rax
	lea     rax, [rel do_general_protection]
	xchg    [rsp], rax
	jmp     error_code

page_fault:
	push    rax
	lea     rax, [rel do_page_fault]
	xchg    [rsp], rax
	jmp     error_code

x87_FPU_error:
	push    0
	push    rax
	lea     rax, [rel do_x87_FPU_error]
	xchg    [rsp], rax
	jmp     error_code

alignment_check:
	push    rax
	lea     rax, [rel do_alignment_check]
	xchg    [rsp], rax
	jmp     error_code

machine_check:
	push    0
	push    rax
	lea     rax, [rel do_machine_check]
	xchg    [rsp], rax
	jmp     error_code

SIMD_exception:
	push    0
	push    rax
	lea     rax, [rel do_SIMD_exception]
	xchg    [rsp], rax
	jmp     error_code

virtualization_exception:
	push    0
	push    rax
	lea     rax, [rel do_virtualization_exception]
	xchg    [rsp], rax
	jmp     error_code