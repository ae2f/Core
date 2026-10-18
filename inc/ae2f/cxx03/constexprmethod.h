#ifndef ae2f_cxx03_constexprmethod_h
#define ae2f_cxx03_constexprmethod_h

#include <ae2f/LangVer.h>
#include <ae2f/cc/inline.h>

#if ae2f_stdcc_v >= 201100L
#define ae2f_constexprmethod		constexpr
#else
#define ae2f_constexprmethod		ae2f_inline	
#endif

#endif
