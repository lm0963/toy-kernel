#include "lib.h"
#include "idt.h"
#include "gdt.h"
#include "keyboard.h"
#define real_variable
#include "global.h"

void pro_C()
{
	while(1)
	{
		toy_puts("c ");
		delay(1000000);
		toy_puts("3 ");
	}
}

void pro_B()
{
	while(1)
	{
		toy_puts("b ");
		delay(1000000);
		toy_puts("2 ");
	}
}

void pro_A()
{
	while(1)
	{
		toy_puts("a ");
		delay(1000000);
		toy_puts("1 ");
	}
}

int main()
{
	init_gdt();
	init_idt();
	init_tss();
	Key_Blocked=0;
	Key_Top=0;
	DPL_0_NESTED=0;
	Key_Tail=1;
	toy_puts("this is a string from kernel\r\n");
	//Create_Process(pro_A);
	//Create_Process(pro_B);
	//Create_Process(pro_C);
	Create_Process(Keyboard_Process);
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
