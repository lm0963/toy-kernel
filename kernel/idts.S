global init_8259A
global idt_not_implememt
global idt_not_implememt_no_code
global Keyboard_Handle
global Timer_Handle
global IDT_DE
global IDT_DB
global IDT_BP
global IDT_OF
global IDT_BR
global IDT_UD
global IDT_NM
global IDT_DF
global IDT_TS
global IDT_NP 
global IDT_SS
global IDT_GP
global IDT_PF
global IDT_MF
global IDT_AC
global IDT_MC
global IDT_XF

extern toy_puts
extern idt_ptr

section text
init_8259A:
	mov	al,0x11
	out	0x20,al
	out	0xa0,al

	mov	al,0x20
	out	0x21,al
	mov	al,0x28
	out	0xa1,al
	
	mov	al,0x4
	out	0x21,al
	mov	al,0x2
	out	0xa1,al
	
	mov	al,0x1
	out	0x21,al
	out	0xa1,al

	lidt [idt_ptr]
	ret

idt_not_implememt_no_code:
	push 0xffffffff
	jmp	idt_not_implememt

IDT_DE:
	push 0x0
	jmp idt_not_implememt
IDT_DB:
	push 0x1
	jmp idt_not_implememt
IDT_BP:
	push 0x3
	jmp idt_not_implememt
IDT_OF:
	push 0x4
	jmp idt_not_implememt
IDT_BR:
	push 0x5
	jmp idt_not_implememt
IDT_UD:
	push 0x6
	jmp idt_not_implememt
IDT_NM:
	push 0x7
	jmp idt_not_implememt
IDT_DF:
	push 0x8
	jmp idt_not_implememt
;IDT_MF:
;	push 0x9
;	jmp idt_not_implememt
IDT_TS:
	push 0xa
	jmp idt_not_implememt
IDT_NP:
	push 0xb
	jmp idt_not_implememt
IDT_SS:
	push 0xc
	jmp idt_not_implememt
IDT_GP:
	push 0xd
	jmp idt_not_implememt
IDT_PF:
	;push 0xe
	add	esp,4
	iret
	jmp idt_not_implememt
IDT_MF:
	push 0x10
	jmp idt_not_implememt
IDT_AC:
	push 0x11
	jmp idt_not_implememt
IDT_MC:
	push 0x12
	jmp idt_not_implememt
IDT_XF:
	push 0x13
	jmp idt_not_implememt

idt_not_implememt:
	push msg
	call toy_puts
	add	esp,8
	iret

Keyboard_Handle:
	push key
	call toy_puts
	mov	al,0x20
	out	0x20,al
	add esp,4
	iret

Timer_Handle:
	inc	byte [gs:0]
	mov	al,0x20
	out	0x20,al
	iret

section data

key db "keyboard hit",0xd,0xa,0
msg db "not implememt",0xd,0
