#include "lib.h"
#include "process.h"
#include "global.h"

int Current_Process=0;
int Process_id=0;
TSS tss;
PROCESS process_table[Max_Process]={0};
const int PROCESS_SIZE=sizeof(PROCESS);

void init_tss()
{
	tss.ss0=SelectorData_DPL_0;
	tss.esp0=0x800000;
	tss.io_addr=sizeof(tss);
}

int Create_Process(void (* func)())
{
	if(Current_Process>Max_Process)
	{
		toy_puts("no more process");
		return ;
	}
	int i=0;
	for(i=0;i<Max_Process;i++)
	{
		if(process_table[i].used==0)
		{
			Process_id++;
			Current_Process++;
			process_table[i].pid=Process_id;
			process_table[i].regs.gs=SelectorVideo_DPL_3;
			process_table[i].regs.fs=SelectorData_DPL_3;
			process_table[i].regs.es=SelectorData_DPL_3;
			process_table[i].regs.ds=SelectorData_DPL_3;
			process_table[i].regs.eip=(int)func;
			process_table[i].regs.cs=SelectorCode_DPL_3;
			process_table[i].regs.ss=SelectorData_DPL_3;
			process_table[i].regs.esp=0xc00000+i*2048;		//
			process_table[i].regs.eflags=0x3202;
			process_table[i].used=1;
			process_table[i].runtime=10;
			return i;
		}
	}
}

void switch_process()
{
	int i=0;
run_pro:
	for(i=0;i<Max_Process;i++)
	{
		if(process_table[i].used==1 && process_table[i].runtime>0)
		{
			process_table[i].runtime--;
			//Save_Process()
			tss.esp0=(int)&(process_table[i].regs.ss)+4;
			Start_Process((int)&(process_table[i].regs));
		}
	}
	for(i=0;i<Max_Process;i++)
	{
		if(process_table[i].used==1)
			process_table[i].runtime=10;
	}
	goto run_pro;
}
