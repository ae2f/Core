#ifndef	ae2f_cxx03_constexprfun_h
#define ae2f_cxx03_constexprfun_h

#include <ae2f/LangVer.h>
#if	ae2f_stdcc_v >= 201100L
#	define	ae2f_constexprfun	constexpr
#else
#	include <ae2f/cc/inline.h>
#	define	ae2f_constexprfun	
#endif

#endif
