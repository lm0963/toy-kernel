;-------------	 loader和kernel   ----------
LOADER_BASE_ADDR equ 0x900 
LOADER_START_SECTOR equ 0x1

;
;Seg_Desc takes 3 args:base,limit,attribute
;base:4 byte,limit:20 bit,attribute:12 bit
;

%macro Seg_Desc 3
	dw %2 & 0xffff
	dw %1 & 0xffff
	db (%1 >> 16) & 0xff
	db %3 & 0xff
	db ((%2 >> 16) & 0xf) | ((%3 & 0xf00) >> 4)
	db (%1 >> 24) & 0xff
%endmacro ;

DA_DR		equ 0x10		;只读数据段
DA_DRW		equ 0x12		;读写数据段
DA_DRE		equ 0x14		;只读向下扩展数据段
DA_DRWE		equ 0x16		;读写向下扩展数据段

DA_C		equ 0x18		;只执行代码段
DA_CR		equ 0x1a		;可读执行代码段
DA_CC		equ 0x1c		;只执行一致代码段
DA_CRC		equ 0x1e		;可读一致代码段

DPL_0		equ 0x00		;特权级 0
DPL_1		equ 0x20		;特权级 1
DPL_2		equ 0x40		;特权级 2
DPL_3		equ 0x60		;特权级 3

PRESENT		equ 0x80		;存在内存中
DA_32		equ 0x400		;代码操作数为32位
LIMITE_32	equ 0x800		;段界限单位4kb

