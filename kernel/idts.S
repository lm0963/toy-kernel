global init_8259A
global idt_not_implememt
global idt_not_implememt_no_code
global Keyboard_Handle
global Timer_Handle

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
	
	mov	al,0x3
	out	0x21,al
	out	0xa1,al

	lidt [idt_ptr]
	ret

idt_not_implememt_no_code:
	push 0xffffffff
	jmp	idt_not_implememt

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
	iretd

section data

key db "keyboard hit",0xd,0xa,0
msg db "not implememt",0xd,0
