; @file: kernel/lib/lib.asm
; @author: lhxl
; @data: 2025-5-3
; @version: build9

global port_write_byte

[section .text]
[bits 64]
port_write_byte:
	mov dx, di
	mov ax, si
	out dx, al
	nop
	nop
	ret