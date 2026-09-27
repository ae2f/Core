#ifndef	ae2f_llong_h
#define ae2f_llong_h

#include <ae2f/c90/lmts/.width.h>

#ifndef	AE2F_LLONG_WANTED
#define	AE2F_LLONG_WANTED 64
#endif

#ifndef	ae2f_llong

#if	LONG_WIDTH == AE2F_LLONG_WANTED
#	define	ae2f_llong	long
#elif	AE2F__INT64_WIDTH == AE2F_LLONG_WANTED
#	define	ae2f_llong	__int64
#endif

#endif

#ifdef	ae2f_llong
typedef signed ae2f_llong ae2f_llong_t;
typedef unsigned ae2f_llong ae2f_ullong_t;
typedef int	ae2f_llong_size[sizeof(ae2f_llong_t) == (AE2F_LLONG_WANTED >> 3) ? 1 : -1];
typedef int	ae2f_llong_size[sizeof(ae2f_ullong_t) == (AE2F_LLONG_WANTED >> 3) ? 1 : -1];

#endif

#endif
