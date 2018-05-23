extern SelectorVideo_DPL_3
global toy_puts

toy_puts:
	pushf
	cli
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
	mov	ax,[SelectorVideo_DPL_3]
	mov	gs,ax
	mov	ah,0xc
	mov	esi,[esp+8]
dis:
	mov	al,[esi]
	test al,al
	jz	end
	cmp	edi,0xfa0
	jb	no_roll
	push ds
	push es
	push eax
	push esi
	push ecx
	mov	ax,gs
	mov	ds,ax
	mov	es,ax
	mov	esi,0xa0
	mov	edi,0x00
	mov	ecx,0x780
	rep	movsw
	mov	esi,0xf00
set_0:
	mov	word [esi],0x720
	add	esi,2
	cmp	esi,0xfa0
	jbe set_0
	pop	ecx
	pop	esi
	pop	eax
	pop	es
	pop	ds
	mov	edi,0xf00
no_roll:
	inc	esi
	cmp	al,0xd
	jz	set_line_head
	cmp	al,0xa
	jz	set_next_line
	cmp	al,0x8
	jz	delete
	mov	[gs:edi],ax
	add	edi,2
	jmp	dis
set_line_head:
	xor	edx,edx
	mov	eax,edi
	mov	ebx,0xa0
	div	ebx
	sub	edi,edx
	mov	ah,0xc
	jmp	dis
set_next_line:
	add	edi,0xa0
	mov	word [gs:edi],0x700
	jmp	dis
delete:
	sub	edi,2
	cmp	word [gs:edi],0x720
	jnz	not_line
dele:
	cmp	word [gs:edi-2],0x720
	jnz	del_line
	sub	edi,2
	jmp	dele
del_line:
	cmp	word [gs:edi-2],0x700
	jnz	dis
	sub	edi,2
not_line:
	mov	word[gs:edi],0x720
	jmp	dis
end:
	mov	ebx,edi
	shr	ebx,1
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
	popf
	ret
