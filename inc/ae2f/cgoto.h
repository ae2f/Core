/**
 * @file	cgoto.h
 * @brief	[c]omputed [goto]
 *
 * @details
 * Contributor: https://github.com/dxdxffgg99
 *
 * Message:
 * I'm sorry. 
 * I shouldn't have shown Dalmuri the VM code I made. 
 * I'll gladly accept any criticism, so please contact me on Discord. 
 * 	-The person who showed Dalmurii the Computed Goto-
 * */

#ifndef	ae2f_cgoto
#define ae2f_cgoto

#include "./cc.h"
#include "./bll.h"

#ifndef	ae2f_cgoto_available
#	if	_ae2f_gnuc(!)0 || _ae2f_clang(!)0
#		define ae2f_cgoto_available	1
#	else
#		define ae2f_cgoto_available	0
#	endif
#endif

/**
 * @def		ae2f_cgoto_beg
 * @brief	Enables the cgoto. You won't be needing this.
 *
 * @def		ae2f_cgoto_end
 * @brief	Disables the cgoto. You won't be needing this.
 * */

#ifndef	ae2f_cgoto_beg
#	if	ae2f_cgoto_available
#		define	ae2f_cgoto_beg()	\
	_Pragma("GCC diagnostic push")		\
	_Pragma("GCC diagnostic ignored \"-Wpedantic\"")
#	else
#		define	ae2f_cgoto_beg()
#	endif
#endif

#ifndef	ae2f_cgoto_end
#	if	ae2f_cgoto_available
#		define	ae2f_cgoto_end() _Pragma("GCC diagnostic pop")
#	else
#		define	ae2f_cgoto_end()
#	endif
#endif

#ifndef	ae2f_cgoto2_strict
#	if	ae2f_cgoto_available
#		define	ae2f_cgoto2_strict(cond, lbl_t, lbl_f)	\
	ae2f_cgoto_beg() \
	goto *ae2f_bll_sel_ptrbool1(void*, cond, &&lbl_t, &&lbl_f);	\
	ae2f_cgoto_end()

#	else
#		define	ae2f_cgoto2_strict(cond, lbl_t, lbl_f)	if(cond) goto lbl_t; else goto lbl_f
#	endif
#endif

#ifndef	ae2f_cgoto2
#define	ae2f_cgoto2(c, t, f)	ae2f_cgoto2_strict(!(c), f, t)
#endif

#endif
