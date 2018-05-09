#define EXTERN extern

#ifdef real_variable
#undef EXTERN
#define EXTERN
#endif

EXTERN int SelectorCode;
EXTERN int SelectorVideo;
EXTERN int SelectorData;
