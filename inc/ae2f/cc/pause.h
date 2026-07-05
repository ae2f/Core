#ifndef	ae2fcc_pause_h
#define	ae2fcc_pause_h

#include <ae2f/cc/profiles.h>

#ifndef	ae2fcc_pause
#	if	_ae2f_gnuc(!)0 || _ae2f_clang(!)0 || _ae2f_gcc(!)0
#		define	ae2fcc_pause()	__builtin_ia32_pause()
#	else
#		define	ae2fcc_pause()
#	endif
#endif

#endif
