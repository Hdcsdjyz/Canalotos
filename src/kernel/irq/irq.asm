; @file: kernel/irq/irq.asm
; @author: lhxl
; @data: 2025-5-13
; @version: build10

%macro irq_master 1
	call    __save
	in      al, 0x21
	or      al, (1 << %1)
	out     0x21, al
	mov     al, 0x20
	out     0x20, al
	sti
	push    %1
	lea     rax, [rel irq_table + 8 * %1]
	call    rax
	pop     rcx
	cli
	in      al, 0x21
    or      al, ~(1 << %1)
    out     0x21, al
%endmacro

%macro	irq_slave	1
	call    __save
	in      al, 0xA1
	or      al, (1 << (%1 - 8))
	out     0xA1, al
	mov     al, 0x20
	out     0x20, al
	nop
	out     0xA0, al
	sti
	push    %1
	lea     rax, [rel irq_table + 8 * %1]
	call    rax
	pop     rcx
	cli
	in      al, 0xA1
	and     al, ~(1 << (%1 - 8))
	out     0xA1, al
	ret
%endmacro

extern irq_table

global __irq00
global __irq01
global __irq02
global __irq03
global __irq04
global __irq05
global __irq06
global __irq07
global __irq08
global __irq09
global __irq10
global __irq11
global __irq12
global __irq13
global __irq14
global __irq15

[section .text]
[bits 64]
__save:
	cld
	push    rax
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
	mov     rdx, 0x10
	mov     ds, rdx
	mov     es, rdx

__irq00:  ; clock
	irq_master 0
__irq01:  ;
	irq_master 1
__irq02:  ; cascade
	irq_master 2
__irq03:  ;
	irq_master 3
__irq04:  ;
	irq_master 4
__irq05:  ;
	irq_master 5
__irq06:  ;
	irq_master 6
__irq07:  ;
	irq_master 7
__irq08:  ;
	irq_slave 8
__irq09:  ; irq 2 redirected
	irq_slave 9
__irq10:  ;
	irq_slave 10
__irq11:  ;
	irq_slave 11
__irq12:  ;
	irq_slave 12
__irq13:  ;
	irq_slave 13
__irq14:  ;
	irq_slave 14
__irq15:  ;
	irq_slave 15