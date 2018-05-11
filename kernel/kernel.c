#include "lib.h"
#include "idt.h"
#include "gdt.h"
#define real_variable
#include "global.h"

void pro_C()
{
	int i;
	while(1)
	{
		toy_puts("c");
		for(i=0;i<10000000;i++)
			;
		toy_puts("3");
	}
}

void pro_B()
{
	int i;
	while(1)
	{
		toy_puts("b");
		for(i=0;i<10000000;i++)
			;
		toy_puts("2");
	}
}

void pro_A()
{
	int i;
	while(1)
	{
		toy_puts("a");
		for(i=0;i<10000000;i++)
			;
		toy_puts("1");
	}
}

int main()
{
	init_gdt();
	init_idt();
	init_tss();
	toy_puts("this is a string from kernel\r\n");
	Create_Process(pro_A);
	Create_Process(pro_B);
	Create_Process(pro_C);
	asm(
		"movb $0xfc,%al;"
		"out %al,$0x21;"
		"movb $0xff,%al;"
		"out %al,$0xa1;"
		"movw SelectorTSS_DPL_3,%ax;"
		"ltr %ax;"
		"sti ;"
	);
	//Start_Process(i);
	while(1)
	;
}
