#define EXTERN extern

#ifdef real_variable
#undef EXTERN
#define EXTERN
#endif

#define Key_Buf_Len 100

EXTERN int SelectorCode_DPL_0;
EXTERN int SelectorVideo_DPL_3;
EXTERN int SelectorData_DPL_0;
EXTERN int SelectorCode_DPL_3;
EXTERN int SelectorData_DPL_3;
EXTERN int SelectorTSS_DPL_3;
EXTERN int SelectorLDT_DPL_0;
EXTERN char Key_Buf[Key_Buf_Len];
EXTERN int Key_Top;
EXTERN int Key_Tail;
EXTERN int Key_Blocked;
EXTERN int DPL_0_NESTED;
