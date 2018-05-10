#include "global.h"
#include "gdt.h"
#include "process.h"

Seg_Desc gdt[gdt_size];
Seg_Desc ldt[ldt_size];

char gdt_ptr[6];

void inline desc_set(Seg_Desc *seg_desc,int base,int limit,int attr)
{
	seg_desc->limit_low=limit & 0xffff;
	seg_desc->base_low=base & 0xffff;
	seg_desc->base_mid_low=base >> 16 & 0xff;
	seg_desc->attr=attr | ((limit & 0xf0000) >> 8);
	seg_desc->base_mid_high=base >> 24;
}

void init_gdt()
{
	*(int *)(gdt_ptr+2)=(int)gdt;
	*(short *)gdt_ptr=sizeof(gdt)-1;
	desc_set(&gdt[0],0,0,0);
	desc_set(&gdt[1],0,0xfffff,DA_C|DA_32|LIMITE_32|DES_PRESENT);
	desc_set(&gdt[2],0,0xfffff,DA_DRW|LIMITE_32|DES_PRESENT|DA_32);
	desc_set(&gdt[3],0xb8000,0x7fff,DA_DRW|DES_PRESENT|DES_DPL_3|DA_32);
	desc_set(&gdt[4],0,0xfffff,DA_C|DA_32|LIMITE_32|DES_PRESENT|DES_DPL_3);
	desc_set(&gdt[5],0,0xfffff,DA_DRW|LIMITE_32|DES_PRESENT|DES_DPL_3|DA_32);
	desc_set(&gdt[6],(int)&tss,sizeof(tss)-1,DA_386TSS|DES_PRESENT);
	desc_set(&gdt[7],(int)ldt,sizeof(ldt)-1,DA_386LDT|DES_PRESENT);
	desc_set(&ldt[0],0,0xfffff,DA_C|DA_32|LIMITE_32|DES_PRESENT|DES_DPL_3);
	SelectorCode_DPL_0=8;
	SelectorData_DPL_0=16;
	SelectorVideo_DPL_3=24+SEL_DPL_3;
	SelectorCode_DPL_3=32+SEL_DPL_3;
	SelectorData_DPL_3=40+SEL_DPL_3;
	SelectorTSS_DPL_3=48+SEL_DPL_0;
	SelectorLDT_DPL_0=56;
	asm(
		"lgdt gdt_ptr;"
		"lldt SelectorLDT_DPL_0;"
	);
}

