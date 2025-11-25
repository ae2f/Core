/**
 * @file Float.h
 * @brief Custom float type
 */

#ifndef ae2f_Float_h
#define ae2f_Float_h

#include "./Float.auto.h"
#include <float.h>

typedef ae2f_float ae2f_float_t;

#if ae2f_float_WIDTH == 4
#define ae2f_float_SUF(x)	x##F
#elif ae2f_float_WIDTH == 8
#define ae2f_float_SUF(x)	x
#else
#define ae2f_float_SUF(x)	x##L
#endif

#endif
