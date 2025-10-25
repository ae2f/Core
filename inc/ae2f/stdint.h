/**
 * @file stdint.h
 * @brief stdint for c90
 * @details 
 * This is for convention. Do not believe its types are guaranteed as fixed.	\n
 * This file may not contain 64 bits.
 * */
#ifndef ae2f_stdint_h
#define ae2f_stdint_h


#if __STDC_HOSTED__
#include <stdint.h>
#else

#include <limits.h>

#ifndef int8_t
#define int8_t	char
#endif

#ifndef int16_t
#define int16_t	short
#endif

#ifndef int32_t

#if INT_MAX >> 31
#define int32_t	int
#else
#define int32_t long
#endif
#endif

#ifndef int64_t
#if LONG_MAX >> 63
#define int64_t	long
#endif
#endif

#endif
#endif
