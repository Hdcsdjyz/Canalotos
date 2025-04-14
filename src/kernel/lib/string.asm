; @file: kernel/lib/string.asm
; @author: lhxl
; @data: 2025-4-14
; @version: build6

global  strlen
global	memcpy
global	memset
global  strcpy

[section .text]
[bits 64]

; size_t strlen(const char* str);
strlen:
	push    rsi
	mov		rsi, rdi
	cld
	xor		rax, rax
	mov		rcx, 0xFFFFFFFFFFFFFFFF
	rep		scasb
	not		rcx
	dec		rcx
	mov		rax, rcx
	pop     rsi
	ret

; void* memcpy(void* p_dst, void* p_src, size_t size);
memcpy:
	push	r8
	push	r9
	push	rcx
	mov		r8, rdi
	mov		r9, rsi
	mov		rcx, rdx
.1:
	cmp		rcx, 0
	jz		.2
	mov		al, [r9]
	inc     r9
	mov     byte [r8], al
	dec     ecx
	jmp     .1
.2:
	mov     rax, rdi
	pop     rcx
	pop     r9
	pop     r8
	ret

; void memset(void* p_dst, char ch, int size);
memset:
	push    r8
	push    r9
	push    rcx
	mov     r8, rdi
	mov     r9, rsi
	mov     rcx, rdx
.1:
	cmp     rcx, 0
	jz      .2
	mov     byte [r8], r9b
	inc     r8
	dec     rcx
	jmp     .1
.2:
	pop     rcx
	pop     r9
	pop     r8
	ret

; char* strcpy(char* p_dst, char* p_src);
strcpy:
	mov     r8, rdi
	mov     r9, rsi
.1:
	mov     al, [r9]
	inc     rsi
	mov     byte [r8], al
	inc     r8
	cmp     al, 0
	jnz     .1
	mov     rax, rdi
	ret