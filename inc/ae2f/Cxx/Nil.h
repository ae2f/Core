#include "../LangVer.h"
#include "../Cast.h"


/** 
 * @macro ae2f_NIL 
 * @brief NULL for C/C++ 
 **/

#undef	ae2f_NIL
#if __ae2f_stdcheck_CC(201100L)
#define	ae2f_NIL	ae2f_WhenC(NULL)	ae2f_WhenCXX(nullptr)
#else
#define ae2f_NIL	ae2f_reinterpret_cast(void*, 0x0)
#endif
