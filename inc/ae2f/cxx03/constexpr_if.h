#ifndef	ae2f_cxx03_constexpr_if_h
#define ae2f_cxx03_constexpr_if_h

#include <ae2f/LangVer.h>

#if	ae2f_stdcc_v >= 201700L
#define	ae2f_constexpr_if(c)	if constexpr (c)
#else
#define	ae2f_constexpr_if(c)	if(c)
#endif

#endif
