;   @file: loader.asm
;   @author: lhxl
;   @data: 2025-4-4
;   @version: build3

%include "macro.inc"

	org     0x10000
	jmp     Start

%include "FAT32.inc"

BaseOfStack         equ	0x7c00
BaseOfLoader        equ 0x1000
OffsetOfLoader      equ 0
RootDirSectors      equ 14
SectorNumOfRootDir  equ 19
SectorNumOfFAT1     equ 1
SectorBalance       equ 17

BaseOfKernel        equ 0
OffsetOfKernel      equ 0x100000
TempBaseOfKernel    equ 0
TempOffsetOfKernel  equ 0x7E00
MemoryBuffer        equ 0x7E00

[segment .gdt]
GDT:          Descriptor 0,          0,       0
DESC_CODE32:  Descriptor 0x00000000, 0xFFFFF, DA_32 | DA_LIMIT_4K | DA_CR
DESC_DATA32:  Descriptor 0x00000000, 0xFFFFF, DA_32 | DA_LIMIT_4K | DA_DRW

GDTLength  equ	$ - GDT
GDTPointor:  dw	GDTLength - 1
		dd	GDT

SelectorCode32 equ DESC_CODE32 - GDT
SelectorData32 equ DESC_DATA32 - GDT

[segment .idt]
IDT:
	resb    1000
IDT_END:
IDTPointor:
	dw      IDT_END - IDT - 1
	dd      IDT

[segment .gdt64]
GDT64:          Descriptor64 0
DESC_CODE64:    Descriptor64 DA_64 | DA_C
DESC_DATA64:    Descriptor64 DA_DRW

Gdt64Length  equ $ - GDT64
GDT64Pointor:  dw Gdt64Length - 1
			   dd GDT64

SelectorCode64 equ DESC_CODE64 - GDT64
SelectorData64 equ DESC_DATA64 - GDT64

[bits 16]
Start:
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
	db      0x66
	lgdt    [GDTPointor]
	mov     eax, cr0
	or      eax, 1
	mov     cr0, eax
	mov     ax, SelectorData32
	mov     fs, ax
	mov     eax, cr0
	and     al, 0b11111110
	mov     cr0, eax

	mov     word [sectorNo], SectorNumOfRootDir
SearchFile:
	cmp     word [rootDirSize], 0
	jz      .FileNotFound
	dec     word [rootDirSize]
	mov     ax, 0
	mov     es, ax
	mov     bx, 0x8000
	mov     ax, [sectorNo]
	mov     cl, 1
	call    ReadSector
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
	jmp     SearchFile
.FileNotFound:
	mov     ax, 0x1301
	mov     bx, 0x8C
	mov     dx, 0x100
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
	call    ReadSector
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
	call    GetFATEntry
	cmp     ax, 0xFFF
	jz      .FileLoaded
	push    ax
	mov     dx, RootDirSectors
	add     ax, dx
	add     ax, SectorBalance
	add     bx, [BPB_BytesPerSec]
	jmp     .LoadFile
.FileLoaded:
.KillMotor:
	push    dx
	mov     dx, 0x3F2
	mov     al, 0
	out     dx, al
	pop     dx
	mov     ax, 0xB800
	mov     gs, ax
%ifdef CL_LOADER_DEBUG
; Get memory information
	mov     ebx, 0
	mov     ax, 0
	mov     es, ax
	mov     di, MemoryBuffer
.GetMemoryStruct:
	mov     eax, 0x0E820
	mov     ecx, 20
	mov     edx, 0x534D4150
	int     0x15
	jc      .GetMemoryFail
	add     di, 20
	cmp     ebx, 0
	jne     .GetMemoryStruct
	jmp     .GetMemorySuccess
.GetMemoryFail:
	mov     ax, 0x1301
	mov     bx, 0x8C
	mov     dx, 0x500
	mov     cx, 23
	push    ax
	mov     ax, ds
	mov     es, ax
	pop     ax
	mov     bp, MSG_GetMemoryError
	int     0x10
	jmp     $
.GetMemorySuccess:
; Set SVGA
	mov     ax, ds
	mov     es, ax
	mov     ax, 0
	mov     es, ax
	mov     di, 0x8000
	mov     ax, 0x4F00
	int     0x10
	cmp     ax,	0x4F
	jz      .KO
	mov     ax, 0x1301
	mov     bx, 0x8C
	mov     dx, 0x900
	mov     cx, 23
	push    ax
	mov     ax, ds
	mov     es, ax
	pop     ax
	mov     bp, MSG_GetSVGAInfoError
	int     0x10
	jmp     $
.KO:
	mov     ax, ds
	mov     es, ax
	mov     ax, 0
	mov     es, ax
	mov     si, 0x800E
	mov     esi, dword [es:si]
	mov     edi, 0x8200
.GetSVGAModeInfo:
	mov     cx, word [es:esi]
	push    ax
	mov     ax, 0
	mov     al, ch
	call    DispAL
	mov     ax, 0
	mov     al, cl
	call    DispAL
	pop     ax
	cmp     cx, 0xFFFF
	jz      .GetSVGAModeInfoSuccess
	mov     ax, 0x4F01
	int     0x10
	cmp     ax, 0x4F
	jnz     .GetSVGAModeInfoFail
	add     esi, 2
	add     edi, 0x100
	jmp     .GetSVGAModeInfo
.GetSVGAModeInfoFail:
	mov     ax, 0x1301
	mov     bx, 0x8C
	mov     dx, 0xD00
	mov     cx, 24
	push    ax
	mov     ax, ds
	mov     es, ax
	pop     ax
	mov     bp, MSG_GetSVGAModeInfoError
	int     0x10
.SetSVGAModeFail:
	jmp	$
%endif
.GetSVGAModeInfoSuccess:
	mov     ax, 0x4F02
	mov     bx, 0x4180
	int 	0x10
%ifdef
	cmp     ax, 0x4F
	jnz     .SetSVGAModeFail
%endif

.EnableProtectMode:
	cli
;	db      0x66
	lgdt    [GDTPointor]
	mov     eax, cr0
	or      eax, 1
	mov     cr0, eax
	jmp     dword SelectorCode32:TempProtectMode

[bits 32]
TempProtectMode:
	mov     ax, 0x10
	mov     ds, ax
	mov     es, ax
	mov     fs, ax
	mov     ss, ax
	mov     esp, 0x7E00
	call    QueryLongMode
	test    eax, eax
	jz      QueryLongMode.QueryLongModeFail


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

; GDT
	db      0x66
	lgdt    [GDT64Pointor]
	mov     ax, 0x10
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

; Load cr3
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

[segment .lib]
[bits 16]
ReadSector:
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

GetFATEntry:
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
	call    ReadSector
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

%ifdef CL_LOADER_DEBUG
; void DispAL(al=hexToDisplay)
DispAL:
	push    ecx
	push    edx
	push    edi
	mov     edi, [displayPosition]
	mov     ah, 0xF
	mov     dl, al
	shr     al, 4
	mov     ecx, 2
.begin:
	and     al, 0xF
	cmp     al, 9
	ja      .1
	add     al, '0'
	jmp     .2
.1:
	sub     al, 0xA
	add     al, 'A'
.2:
	mov     [gs:edi], ax
	add     edi, 2
	mov     al ,dl
	loop    .begin
	mov     [displayPosition], edi
	pop     edi
	pop     edx
	pop     ecx
	ret
%endif

[segment .lib64]
[bits 32]
; void QueryLongMode()
QueryLongMode:
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
KernelName:         db "KERNEL  BIN",0
NoKernelMessage:    db "Missing file kernel.bin"

rootDirSize         dw RootDirSectors
sectorNo            dw 0
odd                 db 0
offsetOfKernelCount dd OffsetOfKernel
displayPosition     dd	0

%ifdef CL_LOADER_DEBUG
MSG_GetMemoryError:     db "Get Memory Struct ERROR"
MSG_GetSVGAInfoError:   db "Get SVGA VBE Info ERROR"
MSG_GetSVGAModeInfoError:      db "Get SVGA Mode Info ERROR"
%endif