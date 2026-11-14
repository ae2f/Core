/** @file fnpretty.h */

#include "./profiles.h"
#include <ae2f/LangVer.h>

/** 
 * @def ae2f_ccpure
 * @brief Keyword as `[[pure]]` on C23.
 * */
#ifndef	ae2f_ccpure
#	if	_ae2f_gnuc(!)0
#		define ae2f_ccpure	__attribute__((pure))
#	elif	ae2f_stdc_v >= (202300L) && !ae2f_stdcc_v
#		define ae2f_ccpure	[[pure]]
#	else
#		define ae2f_ccpure
#	endif
#endif


/** 
 * @def ae2f_ccconst
 * @brief Keyword as `[[const]]` on C23..
 * */
#ifndef	ae2f_ccconst
#	if	_ae2f_gnuc(!)0
#		define ae2f_ccconst	__attribute__((const))
#	elif	ae2f_stdc_v >= (202300L) && !ae2f_stdcc_v
#		define ae2f_ccconst	[[const]]
#	else
#		define ae2f_ccconst
#	endif
#endif

/**
 * @def ae2f_noexcept
 * @brief marker that this function does not throw something.
 * */
#ifndef	ae2f_noexcept
#	if	_ae2f_msvc(!)0 && ae2f_stdcc_v
#		define ae2f_noexcept	__declspec(nothrow)
#	elif	_ae2f_gnuc(!)0
#		define ae2f_noexcept	__attribute__((nothrow))
#	elif	ae2f_stdcc_v >= 201100L
#		define ae2f_noexcept	noexcept
#	else
#		define ae2f_noexcept
#	endif
#endif

/**
 * @def ae2f_retnew
 * @brief The returning pointer does not alias to existing object.
 * */
#ifndef	ae2f_retnew
#	if	_ae2f_msvc(!)0
#		define ae2f_retnew	__declspec(restrict)
#	elif	_ae2f_gnuc(!)0
#		define ae2f_retnew	__attribute__((malloc))
#	else
#		define ae2f_retnew
#	endif
#endif

#ifndef	ae2f_retnew1
#	if	_ae2f_gcc(!)0 && __GNUC__ >= 11
#		define	ae2f_retnew1(dealloc)	__attribute__((malloc(dealloc)))
#	else
#		define	ae2f_retnew1(dealloc)
#	endif
#endif

#ifndef	ae2f_retnew2
#	if	_ae2f_gcc(!)0 && __GNUC__ >= 11
#		define	ae2f_retnew2(dealloc, ptridx)	__attribute__((malloc(dealloc, ptridx)))
#	else
#		define	ae2f_retnew2(dealloc, ptridx)
#	endif
#endif

