; @file: boot/loader.asm
; @author: lhxl
; @data: 2025-4-12
; @version: build5

%include "macro.inc"

	org     0x10000
	jmp     __Start

%include "FAT12.inc"

BaseOfKernel        equ 0
OffsetOfKernel      equ 0x100000
TempBaseOfKernel    equ 0
TempOffsetOfKernel  equ 0x7E00
MemoryBuffer        equ 0x7E00

[section .gdt]
GDT:          Descriptor 0,          0,       0
DESC_CODE32:  Descriptor 0x00000000, 0xFFFFF, DA_32 | DA_LIMIT_4K | DA_CR
DESC_DATA32:  Descriptor 0x00000000, 0xFFFFF, DA_32 | DA_LIMIT_4K | DA_DRW

GDTLength equ $ - GDT
GDTPointer:     dw GDTLength - 1
				dd GDT

SelectorCode32 equ DESC_CODE32 - GDT
SelectorData32 equ DESC_DATA32 - GDT

[section .gdt64]
GDT64:          Descriptor64 0
DESC_CODE64:    Descriptor64 DA_64 | DA_C
DESC_DATA64:    Descriptor64 DA_DRW

Gdt64Length equ $ - GDT64
GDT64Pointer:   dw Gdt64Length - 1
				dd GDT64

SelectorCode64 equ DESC_CODE64 - GDT64
SelectorData64 equ DESC_DATA64 - GDT64

[section .text]
[bits 16]
__Start:
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
; Enter protect mode and expand fs register
	push    ax
	in      al, 0x92
	or      al, 0b00000010
	out     0x92, al
	pop     ax
	cli
	lgdt    [GDTPointer]
	mov     eax, cr0
	or      eax, 1
	mov     cr0, eax
	mov     ax, SelectorData32
	mov     fs, ax
	mov     eax, cr0
	and     al, 0b11111110
	mov     cr0, eax
	sti
	xor     ah, ah
	xor     dl, dl
	int     0x13

	mov     word [sectorNo], SectorNumOfRootDir
__SearchFile:
	cmp     word [rootDirSize], 0
	jz      .FileNotFound
	dec     word [rootDirSize]
	mov     ax, 0
	mov     es, ax
	mov     bx, 0x8000
	mov     ax, [sectorNo]
	mov     cl, 1
	call    __ReadSector
	mov     si, KernelName
	mov     di, 0x8000
	cld
	mov     dx, 0x10
.SearchKernel:
	cmp     dx, 0
	jz      .NextSector
	dec     dx
	mov     cx, 11
.CmpFileName:
	cmp     cx, 0
	jz      .FileFound
	dec     cx
	lodsb
	cmp     al, byte [es:di]
	jz      .GoOn
	jmp     .Different
.GoOn:
	inc     di
	jmp     .CmpFileName
.Different:
	and     di, 0xFFE0
	add     di, 0x20
	mov     si, KernelName
	jmp     .SearchKernel
.NextSector:
	add     word [sectorNo], 1
	jmp     __SearchFile
.FileNotFound:
	mov     ax, 0x1301
	mov     bx, 0x8C
	mov     dx, 0x300
	mov     cx, 23
	push    ax
	mov     ax, ds
	mov     es, ax
	pop     ax
	mov     bp, NoKernelMessage
	int     0x10
	jmp     $
.FileFound:
	mov     ax, RootDirSectors
	and     di, 0xFFE0
	add     di, 0x1A
	mov     cx, word [es:di]
	push    cx
	add     cx, ax
	add     cx, SectorBalance
	mov     eax, TempBaseOfKernel
	mov     es, ax
	mov     bx, TempOffsetOfKernel
	mov     ax, cx
.LoadFile:
	push    ax
	push    bx
	mov     ah, 0xE
	mov     al, '.'
	mov     bl, 0xF
	int     0x10
	pop     bx
	pop     ax
	mov     cl, 1
	call    __ReadSector
	pop     ax
; =
; use expanded fs register to move kernel to memory over 1MB
; the method may cause fault on physical machine
	push    cx
	push    eax
	push    fs
	push    edi
	push    ds
	push    esi
	mov     cx, 0x200
	mov     ax, BaseOfKernel
	mov     fs, ax
	mov     edi, dword [offsetOfKernelCount]
	mov     ax, TempBaseOfKernel
	mov     ds, ax
	mov     esi, TempOffsetOfKernel
.MoveKernel:
	mov     al, byte [ds:esi]
	mov     byte [fs:edi], al
	inc     esi
	inc     edi
	loop    .MoveKernel
	mov     eax, 0x1000
	mov     ds, eax
	mov     dword [offsetOfKernelCount], edi
	pop     esi
	pop     ds
	pop     edi
	pop     fs
	pop     eax
	pop     cx
; =
	call    __GetFATEntry
	cmp     ax, 0xFFF
	jz      .FileLoaded
	push    ax
	mov     dx, RootDirSectors
	add     ax, dx
	add     ax, SectorBalance
	jmp     .LoadFile
.FileLoaded:
	mov     ax, 0xB800
	mov     gs, ax
.KillMotor:
	push    dx
	mov     dx, 0x3F2
	mov     al, 0
	out     dx, al
	pop     dx
	jmp     .GetSVGAModeInfoSuccess
.SetSVGAModeFail:
	jmp	$
.GetSVGAModeInfoSuccess:
	mov     ax, 0x4F02
	mov     bx, 0x4180
	int 	0x10
	cmp     ax, 0x4F
	jnz     .SetSVGAModeFail
.EnableProtectMode:
	cli
	lgdt    [GDTPointer]
	mov     eax, cr0
	or      eax, 1
	mov     cr0, eax
	jmp     dword SelectorCode32:__TempProtectMode

[bits 32]
__TempProtectMode:
	mov     ax, SelectorData32
	mov     ds, ax
	mov     es, ax
	mov     fs, ax
	mov     ss, ax
	mov     esp, 0x7E00
	call    __QueryLongMode
	test    eax, eax
	jz      __QueryLongMode.QueryLongModeFail
; Temporary page table
	mov     dword [0x90000], 0x91007
	mov     dword [0x90800], 0x91007

	mov     dword [0x91000], 0x92007

	mov     dword [0x92000], 0x000083
	mov     dword [0x92008], 0x200083
	mov     dword [0x92010], 0x400083
	mov     dword [0x92018], 0x600083
	mov     dword [0x92020], 0x800083
	mov     dword [0x92028], 0xA00083
; Load GDT
	lgdt    [GDT64Pointer]
	mov     ax, SelectorData64
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    mov     esp, 0x7E00
; Open PAE
	mov     eax, cr4
	bts     eax, 5
	mov     cr4, eax
; Set cr3
	mov     eax, 0x90000
	mov     cr3, eax
; Enable long mode
	mov     ecx, 0xC0000080
	rdmsr
	bts     eax, 8
	wrmsr
; Enable PE
	mov     eax, cr0
	bts     eax, 0
	bts     eax, 31
	mov     cr0, eax
; Enter Kernel
	jmp     SelectorCode64:OffsetOfKernel

[section .lib16]
[bits 16]
__ReadSector:
	push    bp
	mov     bp, sp
	sub     esp, 2
	mov     byte [bp - 2], cl
	push    bx
	mov     bl, [BPB_SecPerTrk]
	div     bl
	inc     ah
	mov     cl, ah
	mov     dh, al
	shr     al, 1
	mov     ch, al
	and     dh, 1
	pop     bx
	mov     dl, [BS_DrvNum]
.Reading:
	mov     ah, 2
	mov     al, byte [bp - 2]
	int     0x13
	jc      .Reading
	add     esp, 2
	pop     bp
	ret

__GetFATEntry:
	push    es
	push    bx
	push    ax
	mov     ax, 0
	mov     es, ax
	pop     ax
	mov     byte [odd], 0
	mov     bx, 3
	mul     bx
	mov     bx, 2
	div     bx
	cmp     dx, 0
	jz      .Even
	mov     byte [odd], 1
.Even:
	xor     dx, dx
	mov     bx, [BPB_BytesPerSec]
	div     bx
	push    dx
	mov     bx, 0x8000
	add     ax, SectorNumOfFAT1
	mov     cl, 2
	call    __ReadSector
	pop     dx
	add     bx, dx
	mov     ax, [es:bx]
	cmp     byte [odd], 1
	jnz     .Even_2
	shr     ax, 4
.Even_2:
	and     ax, 0xFFF
	pop     bx
	pop     es
	ret

[section .lib32]
[bits 32]
; void __QueryLongMode()
__QueryLongMode:
	mov     eax, 0x80000000
	cpuid
	cmp     eax, 0x80000001
	setnb   al
	jb      .QueryLongModeSuccess
	mov     eax, 0x80000001
	cpuid
	bt      edx, 29
	setc    al
.QueryLongModeSuccess:
	movzx   eax, al
	ret
.QueryLongModeFail:
	jmp     $

LoaderMessage:      db "Loading..."
KernelName:         db "KERNEL  BIN", 0
NoKernelMessage:    db "Missing file kernel.bin"

rootDirSize         dw RootDirSectors
sectorNo            dw 0
odd                 db 0
offsetOfKernelCount dd OffsetOfKernel

MemStructNumber     dd 0
SVGAModeCounter     dd 0

MSG_GetMemoryError:     db "Get Memory Struct ERROR"
MSG_GetSVGAInfoError:   db "Get SVGA VBE Info ERROR"
MSG_GetSVGAModeInfoError:      db "Get SVGA Mode Info ERROR"