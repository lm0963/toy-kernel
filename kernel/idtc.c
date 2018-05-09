#include "idt.h"
#include "lib.h"
#include "global.h"

char idt_ptr[6];
GATE_DESC gate_desc[IDT_SIZE];

void inline idt_set_handler(int vector,void (* func)())
{
	gate_desc[vector].offset_low=(int)func & 0xffff;
	gate_desc[vector].offset_high=((int)func >> 16)& 0xffff;
	gate_desc[vector].attr=0x8e00;
	gate_desc[vector].selector=SelectorCode;
}

void init_idt()
{
	*(int *)(idt_ptr+2)=(int)gate_desc;
	*(short *)idt_ptr=sizeof(gate_desc)-1;
	idt_set_handler(NUM_IDT_DE,idt_not_implememt_no_code);
	idt_set_handler(NUM_IDT_DB,idt_not_implememt_no_code);
	idt_set_handler(NUM_IDT_BP,idt_not_implememt_no_code);
	idt_set_handler(NUM_IDT_OF,idt_not_implememt_no_code);
	idt_set_handler(NUM_IDT_BR,idt_not_implememt_no_code);
	idt_set_handler(NUM_IDT_UD,idt_not_implememt_no_code);
	idt_set_handler(NUM_IDT_NM,idt_not_implememt_no_code);
	idt_set_handler(NUM_IDT_DF,idt_not_implememt);
	idt_set_handler(NUM_IDT_TS,idt_not_implememt);
	idt_set_handler(NUM_IDT_NP,idt_not_implememt);
	idt_set_handler(NUM_IDT_SS,idt_not_implememt);
	idt_set_handler(NUM_IDT_GP,idt_not_implememt);
	idt_set_handler(NUM_IDT_PF,idt_not_implememt);
	idt_set_handler(NUM_IDT_MF,idt_not_implememt_no_code);
	idt_set_handler(NUM_IDT_AC,idt_not_implememt_no_code);
	idt_set_handler(NUM_IDT_MC,idt_not_implememt);
	idt_set_handler(NUM_IDT_XF,idt_not_implememt);
	idt_set_handler(NUM_IDT_TI,Timer_Handle);
	idt_set_handler(NUM_IDT_KY,Keyboard_Handle);
	idt_set_handler(NUM_IDT_MO,idt_not_implememt_no_code);
	init_8259A();
	toy_puts("now idt set ok\r\n");
	return ;
}


