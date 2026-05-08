/** @file strict.h */
#include "../profiles.h"

/**
 * @def		ae2f_expected
 * @brief	expectes `a` as `true`.
 * */
#ifndef	ae2f_expected_strict
#include "../../Cast.h"
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define		ae2f_expected_strict(a)		(a) [[likely]]
#	elif	_ae2f_gnuc(!)0
#		define		ae2f_expected_strict(a)	((__builtin_expect(ae2f_static_cast(long, a), 1)))
#	else
#		define		ae2f_expected_strict(a)		((a))
#	endif
#endif

/**
 * @def		ae2f_expected_not
 * @brief	expectes `a` as `false`.
 * */
#ifndef	ae2f_expected_not_strict
#include "../../Cast.h"
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define		ae2f_expected_not_strict(a)	(a) [[unlikely]]
#	elif	_ae2f_gnuc(!)0
#		define		ae2f_expected_not_strict(a)	((__builtin_expect(ae2f_static_cast(long, a), 0)))
#	else
#		define		ae2f_expected_not_strict(a)	((a))
#	endif
#endif
