; @file: kernel/lib/lib.asm
; @author: lhxl
; @data: 2025-5-3
; @version: build10

global __port_write_byte
global __port_read_byte

[section .text]
[bits 64]
__port_write_byte:
	mov dx, di
	mov ax, si
	out dx, al
	nop
	nop
	ret

__port_read_byte:
	mov     dx, di
	xor     al, al
	in      al, dx
	nop
	nop
	ret