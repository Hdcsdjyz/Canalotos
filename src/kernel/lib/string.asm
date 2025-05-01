; @file: kernel/lib/string.asm
; @author: lhxl
; @data: 2025-5-1
; @version: build8

global memset

[section .text]
[bits 64]
; void memset(void* p_dst, char ch, size_t size);
memset:
	push    rbp
	mov     rbp, rsp
	push    rsi
	push    rdi
	push    rcx
	mov     rcx, rdx
	mov     rdx, rsi
.1:
	cmp     rcx, 0
	jz      .2
	mov     byte [rdi], dl
	inc     rdi
	dec     rcx
	jmp     .1
.2:
	pop     rcx
	pop     rdi
	pop     rsi
	mov     rsp, rbp
	pop     rbp
	ret