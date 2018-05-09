extern SelectorVideo
global toy_puts
toy_puts:
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
	mov	ax,[SelectorVideo]
	mov	gs,ax
	mov	ah,0xc
	mov	esi,[esp+4]
dis:
	mov	al,[esi]
	test al,al
	jz	end
	inc	esi
	cmp	al,0xd
	jz	set_line_head
	cmp	al,0xa
	jz	set_next_line
	mov	[gs:edi],ax
	add	edi,2
	jmp	dis
set_line_head:
	xor	edx,edx
	mov	eax,edi
	mov	ebx,0xa0
	div	ebx
	sub	edi,edx
	jmp	dis
set_next_line:
	add	edi,0xa0
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
	ret
