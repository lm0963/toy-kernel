typedef struct
{
	int backlink;
	int esp0;
	int ss0;
	int esp1;
	int ss1;
	int esp2;
	int ss2;
	int cr3;
	int eip;
	int eflags;
	int eax;
	int ecx;
	int edx;
	int ebx;
	int esp;
	int ebp;
	int esi;
	int edi;
	int es;
	int cs;
	int ss;
	int ds;
	int fs;
	int gs;
	int ldt;
	short reserve;
	short io_addr;
}TSS;

typedef struct
{
	int gs;
	int fs;
	int es;
	int ds;
	int edi;
	int esi;
	int ebp;
	int kernel_esp;
	int ebx;
	int edx;
	int ecx;
	int eax;
	int retaddr;
	int eip;
	int cs;
	int eflags;
	int esp;
	int ss;
}STACK;

typedef struct
{
	STACK regs;
	//short SelectorLdt;
	//Seg_Desc ldts[2];
	void * cr3_pdir;
	int pid;
	char name[20];
	int used;
	int runtime;
}PROCESS;

#define Max_Process	4
extern const int PROCESS_SIZE;

extern PROCESS process_table[Max_Process];
extern TSS tss;
void init_tss();
int Create_Process(void (* func)());
void Start_Process(int idx);
