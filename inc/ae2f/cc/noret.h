#ifndef	ae2fcc_noret_h
#define ae2fcc_noret_h

#include <ae2f/cc/profiles.h>
#include <ae2f/LangVer.h>

#ifndef	ae2fcc_noret
#	if	_ae2f_msvc(!)0
#		define ae2fcc_noret __declspec(noreturn)
#	elif	_ae2f_gnuc(!)0 || _ae2f_clang(!)0
#		define ae2fcc_noret __attribute__((noreturn))
#	elif	ae2f_stdcc_v >= 201100L || ae2f_stdc_v >= 202300L
#		define ae2fcc_noret [[noreturn]]
#	elif	ae2f_stdc_v >= 201100L
#		define ae2fcc_noret _Noreturn
#	endif
#endif

#endif
