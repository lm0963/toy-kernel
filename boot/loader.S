%include "boot.inc"
org	LOADER_BASE_ADDR
[section code]
[bits 16]
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	mov	ss,ax
	mov	sp,LOADER_BASE_ADDR

	lgdt [GDT_PTR]
	cli
	in	al,0x92
	or	al,00000010b
	out	0x92,al
	mov	eax,cr0
	or	eax,1
	mov	cr0,eax
	jmp	dword SelectorCode:Code32

[bits 32]
Code32:
	mov	ax,SelectorData
	mov	ds,ax
	mov	ax,SelectorVideo
	mov	gs,ax
	mov	edi,0xa0
	mov	ah,0xc
	mov	esi,msg
print_text:
	mov	al,[esi]
	inc	esi
	mov	[gs:edi],ax
	add	edi,2
	test al,al
	jnz	print_text
	jmp	$

[section gdt]
;gdt						base,	limit,		attribut
GDT			:Seg_Desc		0,		0,			0
CODE_DESC	:Seg_Desc		0,		0xfffff,		DA_C+DA_32+LIMITE_32+PRESENT
DATA_DESC	:Seg_Desc		0,		0xfffff,		DA_DRW+LIMITE_32+PRESENT
VIDEO_DESC	:Seg_Desc		0xb8000,0xffff,		DA_DRW+PRESENT
;gdt end
GDT_LEN		equ $-GDT
GDT_PTR		dw	GDT_LEN-1
			dd	GDT
SelectorCode	equ CODE_DESC-GDT
SelectorData	equ DATA_DESC-GDT
SelectorVideo	equ VIDEO_DESC-GDT
msg db "Now we are in protected mode",0
