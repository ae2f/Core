#ifndef	ae2fcc_pause_h
#define	ae2fcc_pause_h

#include <ae2f/cc/profiles.h>
#include "./profiles.h"
#include "./has_builtin.h"

#ifndef	ae2fcc_pause
#	if	ae2fcc_has_builtin(__builtin_ia32_pause)
#		define	ae2fcc_pause()	__builtin_ia32_pause()
#	else
#		define	ae2fcc_pause()
#	endif
#endif

#endif
