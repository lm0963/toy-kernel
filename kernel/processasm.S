extern PROCESS_SIZE
extern process_table
global Start_Process
global pro_Asm

section text
[bits 32]
Start_Process:
	mov	eax,[esp+4]
	mov	ebx,PROCESS_SIZE
	mul bx
	lea esi,[eax+process_table]
	sub	esp,72
	mov	edi,esp
	mov	cx,18
	rep	movsd
	pop	gs
	pop	fs
	pop	es
	pop	ds
	popad
	add	esp,4
	iret

pro_Asm:
	mov	eax,ebx
	nop
	jmp $

