typedef struct
{
	short offset_low;
	short selector;
	short attr;
	short offset_high;
}GATE_DESC;

#define IDT_SIZE 128
#define NUM_IDT_DE 0
#define NUM_IDT_DB 1 
#define NUM_IDT_BP 3
#define NUM_IDT_OF 4
#define NUM_IDT_BR 5
#define NUM_IDT_UD 6
#define NUM_IDT_NM 7
#define NUM_IDT_DF 8
#define NUM_IDT_TS 10
#define NUM_IDT_NP 11
#define NUM_IDT_SS 12
#define NUM_IDT_GP 13
#define NUM_IDT_PF 14
#define NUM_IDT_MF 16
#define NUM_IDT_AC 17
#define NUM_IDT_MC 18
#define NUM_IDT_XF 19
#define NUM_IDT_TI 32
#define NUM_IDT_KY 33
#define NUM_IDT_MO 44

void  IDT_DE();
void  IDT_DB();
void  IDT_BP();
void  IDT_OF();
void  IDT_BR();
void  IDT_UD();
void  IDT_NM();
void  IDT_DF();
void  IDT_TS();
void  IDT_NP();
void  IDT_SS();
void  IDT_GP();
void  IDT_PF();
void  IDT_MF();
void  IDT_AC();
void  IDT_MC();
void  IDT_XF();

//IDT_PTR idt_ptr;
//GATE_DESC gate_desc[IDT_SIZE];

void init_idt();
void init_8259A();
void idt_not_implememt();
void idt_not_implememt_no_code();
void Keyboard_Handle();
void Timer_Handle();
