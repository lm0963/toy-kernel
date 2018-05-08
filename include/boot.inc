;-------------	 loader和kernel   ----------
LOADER_BASE_ADDR	equ 0x900 
LOADER_START_SECTOR equ 0x1
LOADER_LENGTH		equ 0x9
VIRTUAL_DIR_TABLE	equ 0x7000
VIRTUAL_ADDR_TABLE	equ 0x100000
KERNEL_BASE_ADDR	equ 0x8000
KERNEL_START_SECTOR equ 0xa
KERNEL_LENGTH		equ 0x10
MEM_SIZE			equ 0x1000
;
;Seg_Desc takes 3 args:base,limit,attribute
;base:4 bytes,limit:20 bits,attribute:12 bits
;

%macro Seg_Desc 3
	dw %2 & 0xffff
	dw %1 & 0xffff
	db (%1 >> 16) & 0xff
	db %3 & 0xff
	db ((%2 >> 16) & 0xf) | ((%3 & 0xf00) >> 4)
	db (%1 >> 24) & 0xff
%endmacro ;

;
;Gate_Desc takes args:selector,offset,attribute
;selector:2 bytes,offset:4 bytes,attribute:1 byte
;
%macro	Gate_Desc 3
	dw %2 & 0xffff
	dw %1
	dw (%3 << 8)
	dw (%2 >> 16) & 0xffff
%endmacro

GATE_INT	equ 0x0e		;interupt

DA_DR		equ 0x10		;只读数据段
DA_DRW		equ 0x12		;读写数据段
DA_DRE		equ 0x14		;只读向下扩展数据段
DA_DRWE		equ 0x16		;读写向下扩展数据段

DA_C		equ 0x18		;只执行代码段
DA_CR		equ 0x1a		;可读执行代码段
DA_CC		equ 0x1c		;只执行一致代码段
DA_CRC		equ 0x1e		;可读一致代码段

DES_DPL_0		equ 0x00		;段描述符特权级 0
DES_DPL_1		equ 0x20		;段描述符特权级 1
DES_DPL_2		equ 0x40		;段描述符特权级 2
DES_DPL_3		equ 0x60		;段描述符特权级 3

SEL_DPL_0		equ 0x00		;段选择子特权级 0
SEL_DPL_1		equ 0x01		;段选择子特权级 1
SEL_DPL_2		equ 0x02		;段选择子特权级 2
SEL_DPL_3		equ 0x03		;段选择子特权级 3

TI_GDT			equ 0x00		;GDT表
TI_LDT			equ 0x04		;LDT表

DES_PRESENT		equ 0x80		;存在内存中
DA_32		equ 0x400		;代码操作数为32位
LIMITE_32	equ 0x800		;段界限单位4kb

ADDR_P		equ 0x1			;虚拟地址在内存中
ADDR_RW		equ 0x2			;虚拟地址可读可写
ADDR_US		equ 0x4			;普通用户
ADDR_PWT	equ 0x8			;write-through
ADDR_PCD	equ	0x16		;不可缓冲
ADDR_ACC	equ	0x32		;accessed
ADDR_DIR	equ	0x64		;页表被写过
ADDR_PAT	equ	0x128		;不确定，置0就好
ADDR_G		equ	0x256		;全局页，保存在TLB
