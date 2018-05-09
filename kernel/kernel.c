#include "lib.h"
#include "idt.h"
#define real_variable
#include "global.h"

int main()
{
	SelectorCode=8;
	SelectorVideo=24;
	char * string="123456789\r\n";
	char string2[20];
	char * string3="987654321\r\n";
	toy_memcpy(string3,string2,14);
	toy_puts(string);
	toy_puts(string2);
	init_idt();
	asm(
		"movb $0xfc,%al;"
		"out %al,$0x21;"
		"movb $0xff,%al;"
		"out %al,$0xa1;"
		"sti ;"
	);
	while(1)
	;
}
