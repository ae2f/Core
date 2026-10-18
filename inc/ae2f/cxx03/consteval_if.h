#ifndef	ae2f_cxx03_consteval_if_h
#define ae2f_cxx03_consteval_if_h

#include <ae2f/LangVer.h>

#if	ae2f_stdcc_v >= 202300L
#define	ae2f_consteval_if()		if consteval
#define ae2f_consteval_otherwise()	if !consteval
#else
#include <ae2f/cc/branches/strict.h>
#define ae2f_consteval_if()		ae2f_ifnezerr_strict(0)
#define ae2f_consteval_otherwise()	ae2f_ifneznrm_strict(1)
#endif

#endif
