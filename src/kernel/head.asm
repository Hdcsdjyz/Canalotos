;   @file: kernel/head.asm
;   @author: lhxl
;   @data: 2025-4-6
;   @version: build4

%include "macro.inc"

extern StartKernel

[section .text]
global _start
_start:
	mov     ax, 0x10
	mov     ds, ax
	mov     es, ax
	mov     fs, ax
	mov     ss, ax
	mov     esp, 0x7E0
	lgdt    [rel GDT_Pointer]
	lidt    [rel IDT_Pointer]
	mov     ax, Selector_Kernel_Data64
	mov     ds, ax
	mov     es, ax
	mov     fs, ax
	mov     gs, ax
	mov     ss, ax
	mov     rsp, 0x7E00
	mov     rax, 0x101000
	mov     cr3, rax
	mov     rax, [rel IEntry64]
	push    Selector_Kernel_Code64
	push    rax
	db      0x48
	retf
IEntry64:
	dq      Entry64
Entry64:
	mov     rax, Selector_Kernel_Data64
	mov     ds, rax
	mov     es, rax
	mov     gs, rax
	mov     ss, rax
	mov     rsp, 0xFFFF800000007E00
	mov     rax, [rel IStartKernel]
	push    Selector_Kernel_Code64
	push    rax
	db      0x48
	retf
IStartKernel:
	dq      StartKernel

	align   8
	times   0x1000 - ($ - $$) db 0
__PML4E:

	dq      0x102007
	resq    255
	dq      0x102007
	resq    255
	times   0x2000 - ($ - $$) db 0
__PDPTE:
	dq      0x103003
	resq    511
	times   0x3000 - ($ - $$) db 0
__PDE:
	dq      0x83
	dq      0x200083
	dq      0x400083
	dq      0x600083
	dq      0x800083
	dq      0xE0000083
	dq      0xE0200083
	dq      0xE0400083
	dq      0xE0600083
	dq      0xE0800083
	dq      0xE0A00083
	dq      0xE0C00083
	dq      0xE0E00083
	resq    499

[section .data]
global GDT
GDT:                Descriptor64 0
GDT_Kernel_Code64:  Descriptor64 DA_64 | DA_C
GDT_Kernel_Data64:  Descriptor64 DA_DRW
GDT_User_Code64:    Descriptor64 DA_64 | DA_C | DA_DPL3
GDT_User_Data64:    Descriptor64 DA_DRW | DA_DPL3
GDT_Kernel_Code:  Descriptor 0x00000000, 0xFFFFF, DA_32 | DA_LIMIT_4K | DA_CR
GDT_Kernel_Data:  Descriptor 0x00000000, 0xFFFFF, DA_32 | DA_LIMIT_4K | DA_DRW
	resq    10
GDT_End:
GDT_Pointer:
GDT_Limit:  dw GDT_End - GDT - 1
GDT_Base:   dq GDT
Selector_Kernel_Code64 equ GDT_Kernel_Code64 - GDT
Selector_Kernel_Data64 equ GDT_Kernel_Data64 - GDT
Selector_User_Code64   equ GDT_User_Code64 - GDT
Selector_User_Data64   equ GDT_User_Data64 - GDT
Selector_Kernel_Code equ GDT_Kernel_Code - GDT
Selector_Kernel_Data equ GDT_Kernel_Data - GDT

global IDT
IDT:
	resq    512
IDT_End:
IDT_Pointer:
IDT_Limit:  dw IDT_End - IDT - 1
IDT_Base:   dq IDT

global TSS64
TSS64:
	resq    13
TSS64_End:
TSS64_Pointer:
TSS64_Limit:    dw TSS64_End - TSS64 - 1
TSS64_Base:     dq TSS64
