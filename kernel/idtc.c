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
	gate_desc[vector].selector=SelectorCode_DPL_0;
}

void init_idt()
{
	*(int *)(idt_ptr+2)=(int)gate_desc;
	*(short *)idt_ptr=sizeof(gate_desc)-1;
	idt_set_handler(NUM_IDT_DE,IDT_DE);
	idt_set_handler(NUM_IDT_DB,IDT_DB);
	idt_set_handler(NUM_IDT_BP,IDT_BP);
	idt_set_handler(NUM_IDT_OF,IDT_OF);
	idt_set_handler(NUM_IDT_BR,IDT_BR);
	idt_set_handler(NUM_IDT_UD,IDT_UD);
	idt_set_handler(NUM_IDT_NM,IDT_NM);
	idt_set_handler(NUM_IDT_DF,IDT_DF);
	idt_set_handler(NUM_IDT_TS,IDT_TS);
	idt_set_handler(NUM_IDT_NP,IDT_NP);
	idt_set_handler(NUM_IDT_SS,IDT_SS);
	idt_set_handler(NUM_IDT_GP,IDT_GP);
	idt_set_handler(NUM_IDT_PF,IDT_PF);
	idt_set_handler(NUM_IDT_MF,IDT_MF);
	idt_set_handler(NUM_IDT_AC,IDT_AC);
	idt_set_handler(NUM_IDT_MC,IDT_MC);
	idt_set_handler(NUM_IDT_XF,IDT_XF);
	idt_set_handler(NUM_IDT_TI,Timer_Handle);
	idt_set_handler(NUM_IDT_KY,Keyboard_Handle);
	idt_set_handler(NUM_IDT_MO,idt_not_implememt_no_code);
	init_8259A();
	toy_puts("now idt set ok\r\n");
	return ;
}


