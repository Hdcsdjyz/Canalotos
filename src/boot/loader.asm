;   @file: loader.asm
;   @author: lhxl
;   @data: 2025-4-4
;   @version: build2

	org     0x10000
	mov     ax, cs
	mov     ds, ax
	mov     es, ax
	mov     ax,	0
	mov     ss, ax
	mov     sp, 0x7C00
; Print loader message
	mov     ax, 0x1301
	mov     bx, 0xF
	mov     dx, 0x200
	mov     cx, 10
	push    ax
	mov     ax, ds
	mov     es, ax
	pop     ax
	mov     bp, LoaderMessage
	int     0x10
	jmp     $

LoaderMessage:   db "Loading..."