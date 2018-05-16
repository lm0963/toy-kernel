%include "boot.inc"
org	LOADER_BASE_ADDR
[section code]
[bits 16]
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	mov	ss,ax
	mov	sp,LOADER_BASE_ADDR
	call Get_Men
	mov	[MEM_SIZE],eax
	lgdt [GDT_PTR]
	cli
	in	al,0x92
	or	al,00000010b
	out	0x92,al
	mov	eax,cr0
	or	eax,1
	mov	cr0,eax
	jmp	dword SelectorCode:Code32

Get_Men:
	push bp
	mov	bp,sp
	sub	sp,0x200
	mov	di,sp
	sub	sp,4
	mov	dword [bp-0x204],0
	mov	edx,0x534d4150
	xor ebx,ebx
mem_loop:
	mov eax,0xe820
	mov	ecx,20
	int	0x15
	jc	mem_failed
	inc	dword [bp-0x204]
	add	edi,ecx
	cmp	ebx,0
	jnz	mem_loop
	sub	edi,ecx
	mov	ecx,[bp-0x204]
	xor	eax,eax
mem_max:
	mov	edx,[edi]
	add	edx,[edi+8]
	cmp	eax,edx
	jge	next_one
	mov	eax,edx
next_one:
	sub	edi,20
	loop mem_max
	leave
	ret
mem_failed:
	xor	eax,eax
	leave
	ret

[bits 32]
Code32:
	mov	ax,SelectorData
	mov	ds,ax
	mov	ss,ax
	mov	es,ax
	mov	esp,LOADER_BASE_ADDR
	mov	esi,pro_mode_msg
	call print
	mov	eax,[MEM_SIZE]
	test eax,eax
	jnz	set_virtual_addr
	mov	esi,r_failed_msg
	call print
	jmp	$
set_virtual_addr:
	;mov	eax,VIRTUAL_ADDR_TABLE|ADDR_P|ADDR_RW|ADDR_US
	;mov	[VIRTUAL_DIR_TABLE],eax
	;add	eax,0x1000
	;mov	[VIRTUAL_DIR_TABLE+4],eax
	;add	eax,0x1000
	;mov	[VIRTUAL_DIR_TABLE+8],eax
	;add	eax,0x1000
	;mov	[VIRTUAL_DIR_TABLE+12],eax
	;mov	ecx,1020
	;mov	edi,VIRTUAL_DIR_TABLE+16
	mov	eax,[MEM_SIZE]
	mov	ebx,0x400000
	xor	edx,edx
	div	ebx
	mov	ecx,eax
	mov	ebx,eax
	mov	eax,VIRTUAL_ADDR_TABLE|ADDR_P|ADDR_RW|ADDR_US
	mov	edi,VIRTUAL_DIR_TABLE
set_dir:
	mov	[edi],eax
	add	eax,0x1000
	add	edi,4
	loop set_dir
	mov	ecx,1024
	sub	ecx,ebx
loop_zero:
	mov dword [edi],0
	add	edi,4
	loop loop_zero

	mov	eax,0 | ADDR_P | ADDR_RW | ADDR_US
	mov	edi,VIRTUAL_ADDR_TABLE
set_table:
	dec	ebx
	mov	ecx,1024
set_virtual_table:
	mov	[edi],eax
	add	eax,0x1000
	add	edi,4
	loop set_virtual_table
	cmp	ebx,0
	jnz	set_table
	mov	eax,VIRTUAL_DIR_TABLE
	mov	cr3,eax
	mov	eax,cr0
	or	eax,0x80000000
	mov	cr0,eax
	mov	esi,vir_addr_msg
	call print
	mov	eax,KERNEL_START_SECTOR
	mov	ebx,KERNEL_BASE_ADDR
	mov	ecx,KERNEL_LENGTH
	call rd_disk_m_32
	mov	esi,kernel_in
	call print
	call elf_mov
;	lidt [IDT_PTR]
;	call init_8259A
;	mov	al,11111110b
;	out	0x21,al
;	mov	al,0xff
;	out	0xa1,al
;	sti
	mov	esp,0x800000
	mov	eax,[KERNEL_BASE_ADDR+24]		;elf header entry
	jmp	eax								;jmp and nerver back

elf_mov:
	mov	eax,KERNEL_BASE_ADDR
	mov	cx,[eax+44]
	mov	ebx,[eax+28]					;phoff
.1:
	push ecx
	mov	esi,[eax+ebx+4]					;p_offset
	add	esi,eax
	mov	ecx,[eax+ebx+16]				;p_filesz
	mov	edi,[eax+ebx+8]					;p_vaddr
	;add	edi,eax
	rep movsb
	add	ebx,32
	pop	ecx
	loop .1
	ret

rd_disk_m_32:	   
	mov esi,eax	   ; 备份eax
	mov di,cx		   ; 备份扇区数到di
	mov dx,0x1f2
	mov al,cl
	out dx,al            ;读取的扇区数
	mov eax,esi	   ;恢复ax
	mov dx,0x1f3                       
	out dx,al                          
	mov cl,8
	shr eax,cl
	mov dx,0x1f4
	out dx,al
	shr eax,cl
	mov dx,0x1f5
	out dx,al
	shr eax,cl
	and al,0x0f	   ;lba第24~27位
	or al,0xe0	   ; 设置7～4位为1110,表示lba模式
	mov dx,0x1f6
	out dx,al
	mov dx,0x1f7
	mov al,0x20                        
	out dx,al
.not_ready:		   ;测试0x1f7端口(status寄存器)的的BSY位
	nop
	in al,dx
	and al,0x88	   ;第4位为1表示硬盘控制器已准备好数据传输,第7位为1表示硬盘忙
	cmp al,0x08
	jnz .not_ready	   ;若未准备好,继续等。
	mov ax, di	   ;以下从硬盘端口读数据用insw指令更快捷,不过尽可能多的演示命令使用,
	mov dx, 256	   ;di为要读取的扇区数,一个扇区有512字节,每次读入一个字,共需di*512/2次,所以di*256
	mul dx
	mov cx, ax	   
	mov dx, 0x1f0
.go_on_read:
	in ax,dx		
	mov [ebx], ax
	add ebx, 2
	loop .go_on_read
	ret

print:
	xor	eax,eax
	mov	dx,0x3d4
	mov	al,0xe
	out	dx,al
	mov	dx,0x3d5
	in	al,dx
	mov	ah,al
	mov	dx,0x3d4
	mov	al,0xf
	out	dx,al
	mov	dx,0x3d5
	in	al,dx
	mov	edi,eax
	shl	edi,1
	mov	ax,SelectorVideo
	mov	gs,ax
	mov	ah,0xc
dis:
	mov	al,[esi]
	test al,al
	jz	end
	mov	[gs:edi],ax
	add	edi,2
	inc	esi
	jmp	dis
end:
	shr	edi,1
	xor	edx,edx
	mov	eax,edi
	mov	ebx,80
	div	ebx
	mov	ebx,edi
	sub	ebx,edx
	add	ebx,80
	mov	dx,0x3d4
	mov	al,0xe
	out	dx,al
	mov	dx,0x3d5
	mov	al,bh
	out	dx,al
	mov	dx,0x3d4
	mov	al,0xf
	out	dx,al
	mov	dx,0x3d5
	mov	al,bl
	out	dx,al
	ret

;init_8259A:
;	mov	al,0x11
;	out	0x20,al
;	out	0xa0,al
;
;	mov	al,0x20
;	out	0x21,al
;	mov	al,0x28
;	out	0xa1,al
;	
;	mov	al,0x4
;	out	0x21,al
;	mov	al,0x2
;	out	0xa1,al
;	
;	mov	al,0x3
;	out	0x21,al
;	out	0xa1,al
;	ret

;Time_handler:
;Time_handler_off	equ Time_handler-$$+LOADER_BASE_ADDR
;	inc	byte[gs:0]
	;mov	al,0x20
	;out	0x20,al
;	iretd

[section gdt]
;gdt						base,	limit,		attribute
GDT			:Seg_Desc		0,		0,			0
CODE_DESC	:Seg_Desc		0,		0xfffff,		DA_C+DA_32+LIMITE_32+DES_PRESENT
DATA_DESC	:Seg_Desc		0,		0xfffff,		DA_DRW+LIMITE_32+DES_PRESENT+DA_32
VIDEO_DESC	:Seg_Desc		0xb8000,0x7fff,		DA_DRW+DES_PRESENT
;gdt end
GDT_LEN		equ $-GDT
GDT_PTR		dw	GDT_LEN-1
			dd	GDT
;idt						selector,		offset,		attribute
;IDT:
;%rep 0x100
;			Gate_Desc		SelectorCode,	Time_handler_off,	DES_PRESENT+GATE_INT+DES_DPL_0
;%endrep
;idt end
;IDT_LEN		equ $-IDT
;IDT_PTR		dw	IDT_LEN-1
;			dd	IDT

SelectorCode	equ CODE_DESC-GDT
SelectorData	equ DATA_DESC-GDT
SelectorVideo	equ VIDEO_DESC-GDT
pro_mode_msg	db	"Now we are in protected mode",0
vir_addr_msg	db	"Now we are in virtual addr",0
kernel_in		db	"Now kernel is in memory",0
r_failed_msg	db	"reading failed,,,hlt",0
