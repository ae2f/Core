#ifndef	ae2f_cxx_struct_h
#define	ae2f_cxx_struct_h

#include "../LangVer.h"


/**
 * @def	ae2f_struct
 * @brief	struct referring keyword
 * */
#ifndef	ae2f_struct
#	if ae2f_stdcc_v
#		define ae2f_struct
#	else
#		define ae2f_struct	struct
#	endif
#endif

/**
 * @def	ae2f_class
 * @brief	class declaring keyword
 * */
#ifndef	ae2f_class
#	if ae2f_stdcc_v
#		define ae2f_class	class
#	else
#		define ae2f_class	struct
#	endif
#endif



#endif
