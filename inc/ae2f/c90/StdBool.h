/**
 * @file StdBool.h
 * */

#ifndef ae2f_stdbool_h
#define ae2f_stdbool_h


#if	defined(__STDC_VERSION__) && (__STDC_VERSION__)
#include <stdbool.h>
#elif	defined(__cplusplus)
#else

#ifndef _Bool
#define _Bool	char
#endif

#ifndef bool
#define bool	_Bool
#endif

#ifndef true
#define true	1
#endif

#ifndef false
#define false	0
#endif

#endif
#endif
