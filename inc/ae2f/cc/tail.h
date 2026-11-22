#ifndef	ae2fcc_tail_h
#define ae2fcc_tail_h

#include "./profiles.h"
#include "./has_attr.h"

#if	(_ae2f_clang(!)0 || _ae2f_gcc(!)0) && ae2fcc_has_attr(musttail)

#	define	ae2fcc_tail_f	__attribute__((musttail))

#elif	_ae2f_msvc(!)0 && _MSC_VER >= 1950 && (defined(_M_X64) || defined(_M_AMD64))

#include <ae2f/LangVer.h>

#if	ae2f_stdc_v >= 202300L || ae2f_stdcc_v >= 201100L
#	define	ae2fcc_tail_f	[[msvc::musttail]]
#endif

#endif


#ifndef	ae2fcc_tail_f
#define	ae2fcc_tail_f
#endif

#endif
