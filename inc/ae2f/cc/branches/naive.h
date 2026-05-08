/** @file naive.h */

#include "./strict.h"
#include "../expect/naive.h"

#ifndef	ae2f_ifneznrm
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define	ae2f_ifneznrm(a)		if(a)	[[likely]]
#	else
#		define	ae2f_ifneznrm(a)		if(ae2f_expected(a))
#	endif
#endif

#ifndef	ae2f_ifnezerr
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define	ae2f_ifnezerr(a)		if(a)	[[unlikely]]
#	else
#		define	ae2f_ifnezerr(a)		if(ae2f_expected_not(a))
#	endif
#endif

#ifndef	ae2f_ifeznrm
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define	ae2f_ifeznrm(a)		ae2fcc_unless(a)	[[likely]]
#	else
#		define	ae2f_ifeznrm(a)		if(ae2f_expected_strict(!(a)))
#	endif
#endif

#ifndef	ae2f_ifezerr
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define	ae2f_ifezerr(a)		ae2fcc_unless(a)	[[unlikely]]
#	else
#		define	ae2f_ifezerr(a)		if(ae2f_expected_not_strict(!(a)))
#	endif
#endif


