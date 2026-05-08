/** @file strict.h */

#include "../profiles.h"
#include "../expect/strict.h"
#include "../unless.h"

#ifndef	ae2f_ifneznrm_strict
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define	ae2f_ifneznrm_strict(a)		if(a)	[[likely]]
#	else
#		define	ae2f_ifneznrm_strict(a)		if(ae2f_expected_strict(a))
#	endif
#endif

#ifndef	ae2f_ifnezerr_strict
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define	ae2f_ifnezerr_strict(a)		if(a)	[[unlikely]]
#	else
#		define	ae2f_ifnezerr_strict(a)		if(ae2f_expected_not_strict(a))
#	endif
#endif

#ifndef	ae2f_ifeznrm_strict
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define	ae2f_ifeznrm_strict(a)		ae2fcc_unless(a)	[[likely]]
#	else
#		define	ae2f_ifeznrm_strict(a)		ae2fcc_unless(ae2f_expected_not_strict(a))
#	endif
#endif

#ifndef	ae2f_ifezerr_strict
#	if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#		define	ae2f_ifezerr_strict(a)		ae2fcc_unless(a)	[[unlikely]]
#	else
#		define	ae2f_ifezerr_strict(a)		ae2fcc_unless(ae2f_expected_strict(a))
#	endif
#endif
