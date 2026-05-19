#include "../LangVer.h"

/** 
 * @def ae2f_NIL 
 * @brief NULL for C/C++ 
 **/
#ifndef	ae2f_NIL
#	if ae2f_stdcc_v >= 201100L
#		define	ae2f_NIL	nullptr
#	else
#		define	ae2f_NIL	NULL
#	endif
#endif
