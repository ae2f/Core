#ifndef	ae2f_c90_stddef_size_t_h
#define	ae2f_c90_stddef_size_t_h

#include <ae2f/cc/profiles.h>

#if	_ae2f_gnuc(!)0 || _ae2f_clang(!)0
typedef __SIZE_TYPE__	ae2f_size_t;
#else
#include	<stddef.h>
typedef	size_t		ae2f_size_t;
#endif

#endif
