; @file: kernel/entry.asm
; @author: lhxl
; @data: 2025-5-13
; @version: build10

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

global __divide_error
global __debug
global __nmi
global __breakpoint
global __overflow
global __bounds
global __undefined_opcode
global __device_not_available
global __double_fault
global __coprocessor_segment_overrun
global __invalid_TSS
global __segment_not_present
global __stack_segment_fault
global __general_protection
global __page_fault
global __x87_FPU_error
global __alignment_check
global __machine_check
global __SIMD_exception
global __virtualization_exception

global __goto_ring3

extern __do_divide_error
extern __do_debug
extern __do_nmi
extern __do_breakpoint
extern __do_overflow
extern __do_bounds
extern __do_undefined_opcode
extern __do_device_not_available
extern __do_double_fault
extern __do_coprocessor_segment_overrun
extern __do_invalid_TSS
extern __do_segment_not_present
extern __do_stack_segment_fault
extern __do_general_protection
extern __do_page_fault
extern __do_x87_FPU_error
extern __do_alignment_check
extern __do_machine_check
extern __do_SIMD_exception
extern __do_virtualization_exception

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

__divide_error:
	push    0
	push    rax
	lea     rax, [rel __do_divide_error]
	xchg    [rsp], rax
	jmp     error_code

__debug:
	push    0
	push    rax
	lea     rax, [rel __do_debug]
	xchg    [rsp], rax
	jmp     error_code

__nmi:
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
	call    __do_nmi
	jmp     RestoreRegister

__breakpoint:
	push    0
	push    rax
	lea     rax, [rel __do_breakpoint]
	xchg    [rsp], rax
	jmp     error_code

__overflow:
	push    0
	push    rax
	lea     rax, [rel __do_overflow]
	xchg    [rsp], rax
	jmp     error_code

__bounds:
	push    0
	push    rax
	lea     rax, [rel __do_bounds]
	xchg    [rsp], rax
	jmp     error_code

__undefined_opcode:
	push    0
	push    rax
	lea     rax, [rel __do_undefined_opcode]
	xchg    [rsp], rax
	jmp     error_code

__device_not_available:
	push    0
	push    rax
	lea     rax, [rel __do_device_not_available]
	xchg    [rsp], rax
	jmp     error_code

__double_fault:
	push    0
	push    rax
	lea     rax, [rel __do_double_fault]
	xchg    [rsp], rax
	jmp     error_code

__coprocessor_segment_overrun:
	push    0
	push    rax
	lea     rax, [rel __do_coprocessor_segment_overrun]
	xchg    [rsp], rax
	jmp     error_code

__invalid_TSS:
	push    rax
	lea     rax, [rel __do_invalid_TSS]
	xchg    [rsp], rax
	jmp     error_code

__segment_not_present:
	push    rax
	lea     rax, [rel __do_segment_not_present]
	xchg    [rsp], rax
	jmp     error_code

__stack_segment_fault:
	push    rax
	lea     rax, [rel __do_stack_segment_fault]
	xchg    [rsp], rax
	jmp     error_code

__general_protection:
	push    rax
	lea     rax, [rel __do_general_protection]
	xchg    [rsp], rax
	jmp     error_code

__page_fault:
	push    rax
	lea     rax, [rel __do_page_fault]
	xchg    [rsp], rax
	jmp     error_code

__x87_FPU_error:
	push    0
	push    rax
	lea     rax, [rel __do_x87_FPU_error]
	xchg    [rsp], rax
	jmp     error_code

__alignment_check:
	push    rax
	lea     rax, [rel __do_alignment_check]
	xchg    [rsp], rax
	jmp     error_code

__machine_check:
	push    0
	push    rax
	lea     rax, [rel __do_machine_check]
	xchg    [rsp], rax
	jmp     error_code

__SIMD_exception:
	push    0
	push    rax
	lea     rax, [rel __do_SIMD_exception]
	xchg    [rsp], rax
	jmp     error_code

__virtualization_exception:
	push    0
	push    rax
	lea     rax, [rel __do_virtualization_exception]
	xchg    [rsp], rax
	jmp     error_code

; void __enter_ring3();
;
__goto_ring3:
	mov     [rsp + 0x80], rax
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
	add     rsp, 0x38
	db      0x48
	sysexit