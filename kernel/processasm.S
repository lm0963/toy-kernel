extern PROCESS_SIZE
extern process_table
global Start_Process

section text
[bits 32]
Start_Process:
	mov	al,0x20
	out	0x20,al
	mov	esp,[esp+4]
	pop	gs
	pop	fs
	pop	es
	pop	ds
	popad
	add	esp,4
	iret

