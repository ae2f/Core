/** @file switchctl.h */

#include "./profiles.h"

/**
 * @def		ae2f_fallthrough
 * @brief	explicitly tells compiler that fallthrough on switch is expected.
 * */
#ifndef	ae2f_fallthrough
#include "../LangVer.h"
#	if	_ae2f_gnuc(!)0 || _ae2f_clang(!)0
#		define		ae2f_fallthrough	__attribute__((fallthrough))
#	elif	ae2f_stdc_v >= 202300L || ae2f_stdcc_v
#		define		ae2f_fallthrough	[[fallthrough]]
#	else
#		define		ae2f_fallthrough
#	endif
#endif


/**
 * @def		ae2f_unreachable
 * @brief	tells the compiler that below this keyword is not expected to be reached.
 * */
#ifndef	ae2f_unreachable
#	if	_ae2f_msvc(!)0
#		define		ae2f_unreachable()	__assume(0)
#	elif	_ae2f_gnuc(!)0 || _ae2f_clang(!)0
#		define		ae2f_unreachable()	__builtin_unreachable()
#	else
#		define		ae2f_unreachable()
#	endif
#endif
