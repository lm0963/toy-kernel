#include "keyboard.h"
#include "process.h"
#include "lib.h"

void Keyboard_Process()
{
	int tail,top;
	char c[2]={'\0','\0'};
	top=(Key_Top+1)%Key_Buf_Len;
	while(1)
	{
		tail=Key_Tail%Key_Buf_Len;
		if(tail!=top)
		{
			asm("cli");
			Key_Buf[top]=0;
			Key_Top=top;
			c[0]='a'+top;
			top=(top+1)%Key_Buf_Len;
			asm("sti");
			toy_puts(c);
			//if(Key_Blocked)
			//	asm("int $33");
		}
		else
		{
			//toy_puts("Z");
		}
	}
}
