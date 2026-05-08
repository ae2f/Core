/** @file callconv.h */
#include "./profiles.h"

#ifndef	ae2f_stdcall
#	if	_ae2f_clang(!)0
#		define ae2f_stdcall	__attribute__((__stdcall__))
#	elif	_ae2f_gcc(!)0
#		define ae2f_stdcall	__attribute__((stdcall))
#	elif	_ae2f_msvc(!)0
#		define ae2f_stdcall	__stdcall
#	endif
#endif

#ifndef	ae2f_fastcall
#	if	_ae2f_clang(!)0
#		define ae2f_fastcall	__attribute__((__fastcall__))
#	elif	_ae2f_gcc(!)0
#		define ae2f_fastcall	__attribute__((fastcall))
#	elif	_ae2f_msvc(!)0
#		define ae2f_fastcall	__fastcall
#	endif
#endif

#ifndef	ae2f_cdecl
#	if	_ae2f_clang(!)0
#		define ae2f_cdecl	__attribute__((__cdecl__))
#	elif	_ae2f_gcc(!)0
#		define ae2f_cdecl	__attribute__((cdecl))
#	elif	_ae2f_msvc(!)0
#		define ae2f_cdecl	__cdecl
#	endif
#endif
