	org     0x7c00
BaseOfStack	equ	0x7c00
Start:
	mov	    ax,	cs
	mov	    ds,	ax
	mov	    es,	ax
	mov	    ss,	ax
	mov	    sp,	BaseOfStack
; clear screen
	mov     ah,	0x6
	mov     bx,	0x700
	mov     cx,	0
	mov     dx,	0x184F
	int     0x10
; set cursor
	mov     ax,	0x200
	mov     bx, 0
	mov     dx, 0
	int     0x10
; print BootMessage
	mov     ax, 0x1301
	mov     bx, 0xF
	mov     dx, 0
	mov     cx, 10
	push	ax
	mov     ax, ds
	mov     es, ax
	pop     ax
	mov     bp, BootMessage
	int     0x10
; reset floppy
	xor     ah,	ah
	xor     dl,	dl
	int     0x13
	jmp     $

BootMessage:    db  "Booting..."

	times   510 - ($ - $$)  db  0
	dw      0xaa55