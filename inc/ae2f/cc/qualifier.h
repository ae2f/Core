/** @file qualifier.h */

#include "./profiles.h"

/** 
 * @def ae2f_restrict
 * @brief Keyword as `restrict` on C99.
 * */
#ifndef	ae2f_restrict
#include "../LangVer.h"
#	if	_ae2f_gnuc(!)0 || _ae2f_msvc(!)0
#		define ae2f_restrict	__restrict
#	elif	ae2f_stdc_v >= (199900L) && !ae2f_stdcc_v
#		define ae2f_restrict	restrict
#	else
#		define ae2f_restrict
#	endif
#endif

/**
 * @def		ae2f_unused
 * @brief	Mark an element as unused.
 * @see		[[maybe_unused]]
 * */
#ifndef	ae2f_unused
#include "../LangVer.h"
#	if _ae2f_gnuc(!)0 || _ae2f_clang(!)0
#		define ae2f_unused	__attribute__((unused))
#	elif	ae2f_stdcc_v >= 201700L || ae2f_stdc_v >= 202300L
#		define ae2f_unused	[[maybe_unused]]
#	else
#		define ae2f_unused
#	endif
#endif
