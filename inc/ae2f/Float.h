/**
 * @file Float.h
 * @brief
 * Here, float will be treated as bit vector with four attributes:
 *
 * sign: \n	
 * 	> Whether it has sign or not. \n
 *
 * exp:	\n
 * 	> Exponent. It will be considered as unsigned integer, \n
 * 	> Which is the exponent of the [frac]
 *
 * expbiasp: \n
 * 	> Exponent bias in order to be considered as zero. \n
 * 	> For handling possibly negative values of [exp] (such as 0.5) \n
 *
 * 	> Here, the value of exponent bias is limited with following rules:
 * 		- It must be (2^([expbiasp]) - 1), and you are actually setting [expbiasp].
 * 		- [expbiasp] must be between 1 and [exp].
 *
 * frac: \n
 * 	> The actual "value" for floating point.
 *
 * ==================
 *
 * Following is the expected structure as bit vector: \n
 * [frac | exp | sign]
 * 
 * Size of this will be calculated as: \n
 * [sign] + [exp] + [frac]
 */

#ifndef ae2f_Float_h
#define ae2f_Float_h

#include "./Float.auto.h"

typedef ae2f_float ae2f_float_t;

#endif
