#pragma pack(1) 
typedef struct 
{
	short limit_low;
	short base_low;
	char base_mid_low;
	short attr;
	char base_mid_high;
}Seg_Desc;
#pragma pack() 

#define gdt_size 128
#define ldt_size 20

#define DA_DR	0x10		//只读数据段
#define DA_DRW	0x12		//读写数据段
#define DA_DRE	0x14		//只读向下扩展数据段
#define DA_DRWE	0x16		//读写向下扩展数据段

#define DA_C	0x18		//只执行代码段
#define DA_CR	0x1a		//可读执行代码段
#define DA_CC	0x1c		//只执行一致代码段
#define DA_CRC	0x1e		//可读一致代码段

#define DES_DPL_0	0x00		//段描述符特权级 0
#define DES_DPL_1	0x20		//段描述符特权级 1
#define DES_DPL_2	0x40		//段描述符特权级 2
#define DES_DPL_3	0x60		//段描述符特权级 3

#define SEL_DPL_0	0x00		//段选择子特权级 0
#define SEL_DPL_1	0x01		//段选择子特权级 1
#define SEL_DPL_2	0x02		//段选择子特权级 2
#define SEL_DPL_3	0x03		//段选择子特权级 3

#define TI_GDT	0x00		//GDT表
#define TI_LDT	0x04		//LDT表

#define DES_PRESENT	0x80		//存在内存中
#define DA_386TSS	0x09		//task_descriptor
#define DA_386LDT	0x02		//LDT
#define DA_32		0x4000		//代码操作数为32位
#define LIMITE_32	0x8000		//段界限单位4kb

void init_gdt();
