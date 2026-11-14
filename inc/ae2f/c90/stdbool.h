/**
 * @file StdBool.h
 * */

#ifndef ae2f_stdbool_h
#define ae2f_stdbool_h

#if	defined(__STDC_VERSION__) && (__STDC_VERSION__)
#include <stdbool.h>

#define	ae2f_bool	bool
#define	ae2f_true	true
#define	ae2f_false	false

#elif	defined(__cplusplus)

#define	ae2f_bool	bool
#define	ae2f_true	true
#define	ae2f_false	false

#else

#define	ae2f_bool	int
#define	ae2f_true	1	
#define	ae2f_false	0

#endif
#endif
