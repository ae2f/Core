/** @file dylink.h */
#include "./profiles.h"

/**
 * @def ae2f_decl
 * @brief Function declare for shared object
 * */
#ifndef	ae2f_decl
#	if	_ae2f_msvc(!)0
#		define ae2f_decl	__declspec(dllimport)
#	else
#		define ae2f_decl
#	endif
#endif

/**
 * @def ae2f_impl
 * @brief Function implementation for shared object
 * */
#ifndef	ae2f_impl
#	if	_ae2f_msvc(!)0
#		define ae2f_impl	__declspec(dllexport)
#	elif	_ae2f_gnuc(!)0
#		define ae2f_impl	__attribute__((visibility("default")))
#	else
#		define ae2f_impl
#	endif
#endif
