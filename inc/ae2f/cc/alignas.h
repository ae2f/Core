#ifndef	ae2fcc_alignas_h
#define	ae2fcc_alignas_h

#include <ae2f/cc/profiles.h>
#include <ae2f/LangVer.h>

#ifndef	ae2fcc_alignas
#	if	_ae2f_gnuc(!)0 || _ae2f_gcc(!)0 || _ae2f_clang(!)0
#		define	ae2fcc_alignas(c_align)	__attribute__((aligned(c_align)))
#	elif	_ae2f_msvc(!)0
#		define	ae2fcc_alignas(c_align)	__declspec(align(c_align))
#	elif	ae2f_stdc_v >= (202300L) || ae2f_stdcc_v >= (201100L)
#		define	ae2fcc_alignas(c_align)	alignas(c_align)
#	elif	ae2f_stdc_v >= (201100L)
#		define	ae2fcc_alignas(c_align)	_Alignas(c_align)
#	endif
#endif

#endif
