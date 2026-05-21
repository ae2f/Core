/** 
 * @file	assume.h
 * */
#include "./profiles.h"

/**
 * @def		ae2f_assume_strict
 * @brief	tells the compiler that value if `a` is `false`, 
 * below this keyword is not expected to be reached.
 * @warning	this keyword is very strict and will not allow runtime evaluation (function call, etc).
 * @see	ae2f_unreachable
 * */
#ifndef	ae2f_assume_strict
#include "./branches/strict.h"
#	if	_ae2f_msvc(!)0
#		define		ae2f_assume_strict(a)	{ __assume(a); }
#	elif	_ae2f_gcc(!)0 && (__GNUC__ >= 13)
#		define		ae2f_assume_strict(a)	{ __attribute__((__assume__(a))); }
#	elif	_ae2f_clang(!)0
#		define		ae2f_assume_strict(a)	{ __builtin_assume(a); }
#	elif	ae2f_stdcc_v >= 202300L
#		define		ae2f_assume_strict(a)	{ [[assume(a)]] }
#	else
#		define		ae2f_assume_strict(a)	ae2f_ifezerr_strict(a) { ae2f_unreachable(); }
#	endif
#endif

/**
 * @def		ae2f_assume
 * @brief	tells the compiler that value if `a` is `false`, 
 * below this keyword is not expected to be reached.
 * @see	ae2f_unreachable
 * */
#ifndef	ae2f_assume
#include "./branches/naive.h"
#	if	_ae2f_gcc(!)0 && (__GNUC__ >= 13)
#		define		ae2f_assume(a)	{ __attribute__((__assume__(a))); }
#	elif	_ae2f_clang(!)0 && _ae2f_msvc(!)1
#		define		ae2f_assume(a)	{ __builtin_assume(a); }
#	elif	ae2f_stdcc_v >= 202300L
#		define		ae2f_assume(a)	{ [[assume(a)]] }
#	else
#		define		ae2f_assume(a)	ae2f_ifezerr(a) { ae2f_unreachable(); }
#	endif
#endif
