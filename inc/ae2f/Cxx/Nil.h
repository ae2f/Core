#include "../LangVer.h"


#undef	ae2f_NIL
#if __ae2f_stdcheck_CC(201100L)
/** @macro ae2f_NIL @brief NULL for C/C++ */
#define	ae2f_NIL	ae2f_WhenC(NULL)	ae2f_WhenCXX(nullptr)
#else
#define ae2f_NIL	ae2f_WhenC(NULL)	ae2f_WhenCXX(0)
#endif
