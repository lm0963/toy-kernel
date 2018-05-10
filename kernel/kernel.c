#include "lib.h"
#include "idt.h"
#include "gdt.h"
#define real_variable
#include "global.h"
void pro_Asm();

void pro_A()
{
	int i;
	while(1)
	{
		for(i=0;i<10000000;i++)
		;
		toy_puts("a");
	}
}

int main()
{
	init_gdt();
	char * string="123456789\r\n";
	char string2[20];
	char * string3="987654321\r\n";
	toy_memcpy(string3,string2,14);
	int i=0;
	toy_puts(string);
	toy_puts(string2);
	i=Create_Process(pro_A);
	init_idt();
	asm(
		"movb $0xfc,%al;"
		"out %al,$0x21;"
		"movb $0xff,%al;"
		"out %al,$0xa1;"
		//"sti ;"
		"movw SelectorTSS_DPL_3,%ax;"
		"ltr %ax;"
	);
	init_tss();
	Start_Process(i);
	while(1)
	;
}
