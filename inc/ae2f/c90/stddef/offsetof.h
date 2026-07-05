#ifndef	ae2fc90_stddef_offsetof_h
#define	ae2fc90_stddef_offsetof_h

#include <ae2f/Cast.h>
#include <ae2f/c90/stddef/size_t.h>

#define	ae2f_offsetof(st, m)	\
	ae2f_reinterpret_cast(size_t	\
			, ae2f_reinterpret_cast(char*, &ae2f_reinterpret_cast(st*, 0)->m)	\
			- ae2f_reinterpret_cast(char*, 0)	\
			)
#endif
