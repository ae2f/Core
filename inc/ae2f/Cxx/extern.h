#ifndef	ae2f_cxx_extern_h
#define ae2f_cxx_extern_h

#include "../LangVer.h"

/**
 @brief
 Suggests the existence of external variable or function, in naming of C.
 [non-mangling]
 */
#ifndef	ae2f_extern_C
#	if ae2f_stdcc_v
#	define ae2f_extern_C	extern "C"
#	else
#	define ae2f_extern_C
#	endif
#endif

#ifndef	ae2f_extern
#	if ae2f_stdcc_v
#	define ae2f_extern	extern "C"
#	else
#	define ae2f_extern	extern
#	endif
#endif

#endif
