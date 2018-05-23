#include "keyboard.h"
#include "process.h"
#include "lib.h"
#include "keymap.h"

static shift=0;

void Keyboard_Process()
{
	volatile int tail,top;
	char c[]={0,0};
	top=(Key_Top+1)%Key_Buf_Len;
	while(1)
	{
		tail=Key_Tail%Key_Buf_Len;
		while(top!=tail)
		{
			c[0]=Key_Buf[top];
			toy_puts(c);
			Key_Top=top;
			top=(top+1)%Key_Buf_Len;
		}
	}
}

void Keyboard_Handler(int key)
{
	unsigned char c=(unsigned char)key;
	if(Key_Tail%Key_Buf_Len==Key_Top)
		return ;
	if(c < 0x80)
	{
		if(c==shift_l || c==shift_r)
		{
			shift=1;
			return ;
		}
		if(c==enter)
		{
			Key_Buf[Key_Tail%Key_Buf_Len]='\r';
			Key_Buf[(Key_Tail+1)%Key_Buf_Len]='\n';
			Key_Tail=(Key_Tail+2)%Key_Buf_Len;
			return ;
		}
		Key_Buf[Key_Tail%Key_Buf_Len]=keymap[c][shift];
		Key_Tail=(Key_Tail+1)%Key_Buf_Len;
	}
	else
	{
		if(key==(shift_l | 0x80) || key==(shift_r | 0x80))
			shift=0;
	}
}
