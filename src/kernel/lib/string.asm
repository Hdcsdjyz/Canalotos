; @file: kernel/lib/string.asm
; @author: lhxl
; @data: 2025-5-13
; @version: build10

global memset
global memcpy
global strlen

[section .text]
[bits 64]
; void memset(void* p_dst, char ch, size_t size);
memset:
	mov     rax, rsi
.1:
	cmp     rdx, 0
	jz      .2
	mov     byte [rdi], al
	inc     rdi
	dec     rdx
	jmp     .1
.2:
	ret

; void* memcpy(void* p_dst, void* p_src, size_t size);
memcpy:
	push    rcx
	mov     rax, rdi
.1:
	cmp     rdx, 0
	jz      .2
	mov     cl, [rsi]
	inc     rsi
	mov     byte [rdi], cl
	inc     rdi
	dec     rdx
	jmp     .1
.2:
	pop     rcx
	ret

; size_t strlen(const char* str);
strlen:
	xor rax, rax
.1:
	cmp byte [rdi], 0
	jz .2
	inc rdi
	inc rax
	jmp .1
.2:
	ret