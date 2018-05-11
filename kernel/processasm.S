extern PROCESS_SIZE
extern process_table
global Start_Process
global pro_Asm

section text
[bits 32]
Start_Process:
	;mov	eax,[esp+4]
	;mov	ebx,[PROCESS_SIZE]
	;mul bx
	;lea esi,[eax+process_table]
	;mov	esi,[esp+4]
	;sub	esp,0x80
	;mov	edi,esp
	;mov	cx,18
	;rep	movsd
	;mov	eax,[esp+4]
	;mov	esp,eax
	mov	esp,[esp+4]
	pop	gs
	pop	fs
	pop	es
	pop	ds
	popad
	add	esp,4
	mov	al,0x20
	out	0x20,al
	iret

pro_Asm:
	mov	eax,ebx
	nop
	jmp $

