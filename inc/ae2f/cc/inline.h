
#include "./profiles.h"

/**
 * @def		ae2f_inline
 * @brief	`inline`
 * */

#ifndef	ae2f_inline
#include "../LangVer.h"
#	if	_ae2f_msvc(!)0
#		define		ae2f_inline	__inline
#	elif	_ae2f_gnuc(!)0
#		define		ae2f_inline	__inline__
#	elif	ae2f_stdc_v >= 199900L || ae2f_stdcc_v
#		define		ae2f_inline	inline
#	else
#		define		ae2f_inline
#	endif
#endif

#ifndef	ae2f_inline_f
#	if	_ae2f_gnuc(!)0
#		define ae2f_inline_f	ae2f_inline __attribute__((always_inline))
#	elif	_ae2f_msvc(!)0
#		define ae2f_inline_f	__forceinline
#	else
#		define ae2f_inline_f	ae2f_inline
#	endif
#endif
