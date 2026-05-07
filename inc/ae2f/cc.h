/**
 * @file cc.h
 * @brief Utility marks which could partially be available with gnu compiler.
 * @details Keys.h will utilise it to have keywords
 * */

#ifndef	ae2f_cc_h
#define ae2f_cc_h

#include "./LangVer.h"

/**
 * @def _ae2f_gnuc
 * @brief Available when compiled with gcc compiler.
 *
 * @def N_ae2f_gnuc
 * @brief Available when not compiled with gnu compiler.
 * */

#ifndef	_ae2f_gnuc
#	if	defined(__GNUC__)
#		define _ae2f_gnuc(a)	a
#	else
#		define _ae2f_gnuc(a)
#	endif
#endif

#ifndef	N_ae2f_gnuc
#	if	defined(__GNUC__)
#		define N_ae2f_gnuc(a)
#	else
#		define N_ae2f_gnuc(a)	a
#	endif
#endif

#ifndef	_ae2f_clang
#	if	defined(__clang__)
#		define	_ae2f_clang(a)	a
#	else
#		define	_ae2f_clang(a)
#	endif
#endif

#ifndef	N_ae2f_clang
#	if	defined(__clang__)
#		define	N_ae2f_clang(a)
#	else
#		define	N_ae2f_clang(a)	a
#	endif
#endif

#ifndef	_ae2f_gcc
#	if	_ae2f_clang(!)1 && _ae2f_gnuc(!)0
#		define	_ae2f_gcc(a)	a
#	else
#		define	_ae2f_gcc(a)
#	endif
#endif

#ifndef	N_ae2f_gcc
#	if	_ae2f_clang(!)1 && _ae2f_gnuc(!)0
#		define	N_ae2f_gcc(a)	a
#	else
#		define	N_ae2f_gcc(a)
#	endif
#endif


/**
 * @def _ae2f_msvc
 * @brief Available when compiled with msvc.
 *
 * @def N_ae2f_msvc
 * @brief Available when not compiled with msvc.
 * */
#undef	_ae2f_msvc
#undef	N_ae2f_msvc
#if	defined(_MSC_VER)
#define	_ae2f_msvc(a)	a
#define	N_ae2f_msvc(a)	
#else
#define _ae2f_msvc(a)
#define N_ae2f_msvc(a)	a
#endif

/** 
 * @def ae2f_ccpure
 * @brief Keyword as `[[pure]]` on C23.
 * */

#ifndef	ae2f_ccpure
#	if	_ae2f_gnuc(!)0
#		define ae2f_ccpure	__attribute__((pure))
#	elif	__ae2f_stdcheck_C(202300L) && ae2f_stdcc_v
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
#	elif	__ae2f_stdcheck_C(202300L) && ae2f_stdcc_v
#		define ae2f_ccconst	[[const]]
#	else
#		define ae2f_ccconst
#	endif
#endif

/** 
 * @def ae2f_restrict
 * @brief Keyword as `restrict` on C99.
 * */
#ifndef	ae2f_restrict
#	if	_ae2f_gnuc(!)0 || _ae2f_msvc(!)0
#		define ae2f_restrict	__restrict
#	elif	__ae2f_stdcheck_C(199900L) && ae2f_stdcc_v
#		define ae2f_restrict	restrict
#	else
#		define ae2f_restrict
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
 * @def		ae2f_inline
 * @brief	`inline`
 * */
#undef	ae2f_inline
#if	_ae2f_msvc(!)0
#define		ae2f_inline	__inline
#elif	_ae2f_gnuc(!)0
#define		ae2f_inline	__inline__
#elif	ae2f_stdc_v >= 199900L || ae2f_stdcc_v
#define		ae2f_inline	inline
#else
#define		ae2f_inline
#endif

/**
 * @def		ae2f_fallthrough
 * @brief	explicitly tells compiler that fallthrough on switch is expected.
 * */
#undef	ae2f_fallthrough
#if	_ae2f_msvc(!)0 && _MSC_VER >= 1934
#define		ae2f_fallthrough	[[fallthrough]]
#elif	_ae2f_gnuc(!)0
#define		ae2f_fallthrough	__attribute__((fallthrough))
#elif	ae2f_stdc_v >= 202300L || ae2f_stdcc_v
#define		ae2f_fallthrough	[[fallthrough]]
#else
#define		ae2f_fallthrough
#endif


/**
 * @def		ae2f_expected
 * @brief	expectes `a` as `true`.
 *
 * @def		ae2f_expected_not
 * @brief	expectes `a` as `false`.
 * */

#undef	ae2f_expected_strict
#undef	ae2f_expected_not_strict
#if	_ae2f_msvc(!)0 && defined(_MSVC_LANG) && _MSVC_LANG >= 202002L || ae2f_stdcc_v >= 202002L
#	define		ae2f_expected_strict(a)		(a) [[likely]]
#	define		ae2f_expected_not_strict(a)	(a) [[unlikely]]
#elif	_ae2f_gnuc(!)0
#	define		ae2f_expected_strict(a)	(__builtin_expect((a), 1))
#	define		ae2f_expected_not_strict(a)	(__builtin_expect((a), 0))
#else
#	define		ae2f_expected_strict(a)		a
#	define		ae2f_expected_not_strict(a)	a
#endif

#undef	ae2f_expected
#undef	ae2f_expected_not
#define	ae2f_expected(a)	(!ae2f_expected_not_strict(!(a)))
#define	ae2f_expected_not(a)	(!ae2f_expected_strict(!(a)))

#undef		ae2f_unexpected
#define		ae2f_unexpected		ae2f_expected_not

#undef	ae2f_unexpected_but_if
#define	ae2f_unexpected_but_if(a)	if(ae2f_unexpected(a))

#undef	ae2f_expected_if
#define	ae2f_expected_if(a)		if(ae2f_expected(a))

#undef	ae2f_unexpected_else
#define	ae2f_unexpected_else(a)		if(ae2f_expected_strict(!(a)))

#undef	ae2f_expected_but_else
#define	ae2f_expected_but_else(a)	if(ae2f_expected_not_strict(!(a)))

#define	ae2f_ifneznrm(a)		ae2f_expected_if(a)
#define	ae2f_ifnezerr(a)		ae2f_unexpected_but_if(a)
#define ae2f_ifeznrm(a)			ae2f_unexpected_else(a)
#define	ae2f_ifezerr(a)			ae2f_expected_but_else(a)

#define	ae2f_ifneznrm_strict(a)		if(ae2f_expected_strict(a))
#define	ae2f_ifnezerr_strict(a)		if(ae2f_expected_not_strict(a))
#define	ae2f_ifeznrm_strict(a)		unless(ae2f_expected_not_strict(a))
#define	ae2f_ifezerr_strict(a)		unless(ae2f_expected_strict(a))

/**
 * @def		ae2f_unreachable
 * @brief	tells the compiler that below this keyword is not expected to be reached.
 * */
#undef	ae2f_unreachable
#if	_ae2f_msvc(!)0
#define		ae2f_unreachable()	__assume(0)
#elif	_ae2f_gnuc(!)0
#define		ae2f_unreachable()	__builtin_unreachable()
#else
#define		ae2f_unreachable()
#endif


/**
 * @def		ae2f_assume_strict
 * @brief	tells the compiler that value if `a` is `false`, 
 * below this keyword is not expected to be reached.
 * @warning	this keyword is very strict and will not allow runtime evaluation (function call, etc).
 * @see	ae2f_unreachable
 * */
#undef	ae2f_assume_strict
#if	_ae2f_msvc(!)0
#define		ae2f_assume_strict(a)	{ __assume(a); }
#elif	_ae2f_gcc(!)0 && (__GNUC__ >= 13)
#define		ae2f_assume_strict(a)	{ __attribute__((__assume__(a))); }
#elif	_ae2f_clang(!)0
#define		ae2f_assume_strict(a)	{ __builtin_assume(a); }
#elif	ae2f_stdcc_v >= 202300L
#define		ae2f_assume_strict(a)	[[assume(a)]]
#else
#define		ae2f_assume_strict(a)	ae2f_expected_but_else(a) { ae2f_unreachable(); }
#endif

/**
 * @def		ae2f_assume
 * @brief	tells the compiler that value if `a` is `false`, 
 * below this keyword is not expected to be reached.
 * @see	ae2f_unreachable
 * */
#ifndef	ae2f_assume
#	if _ae2f_gcc(!)0 && (__GNUC__ >= 13)
#		define	ae2f_assume(a)	{ __attribute__((assume(a))); }
#	else
#		define	ae2f_assume(a)	ae2f_expected_but_else(a) { ae2f_unreachable(); }
#	endif
#endif


/**
 * @def		ae2f_unused
 * @brief	Mark an element as unused.
 * @see		[[maybe_unused]]
 * */
#ifndef	ae2f_unused
#	if _ae2f_gnuc(!)0
#		define ae2f_unused	__attribute__((unused))
#	elif	ae2f_stdcc_v >= 201700L || ae2f_stdc_v >= 202300L
#		define ae2f_unused	[[maybe_unused]]
#	else
#		define ae2f_unused
#	endif
#endif

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

#ifndef	ae2f_always_inline
#	if	_ae2f_gnuc(!)0
#		define ae2f_always_inline	ae2f_inline __attribute__((always_inline))
#	elif	_ae2f_msvc(!)0
#		define ae2f_always_inline	__forceinline
#	else
#		define ae2f_always_inline	ae2f_inline
#	endif
#endif

#define	ae2f_inline_f ae2f_always_inline

#endif
