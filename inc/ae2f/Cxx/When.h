#ifndef	ae2f_Cxx_When_h
#define	ae2f_Cxx_When_h

#include "../LangVer.h"

/**
 * @def	ae2f_WhenC
 *
 * @brief
 *	Appears when the current language is C.
 */

/**
 * @def ae2f_WhenCXX 
 *
 * @brief
 *	Appears when the current language is C++.
 */

#ifndef	ae2f_WhenC
#	if ae2f_stdcc_v
#		define	ae2f_WhenC(a) 
#	else
#		define	ae2f_WhenC(a)	a
#	endif
#endif

#ifndef	ae2f_WhenCXX
#	if ae2f_stdcc_v
#		define	ae2f_WhenCXX(a)	a
#	else
#		define	ae2f_WhenCXX(a)
#	endif
#endif

#endif
