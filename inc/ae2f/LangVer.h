/**
 * @file LangVer.h
 * @brief Language version for C/C++
 * @details
 * - Uses `__cplusplus` and `__STDC_VERSION__` for language version.
 * - If not defined, Uses generated `ae2f_LangVer_C`, `ae2f_LangVer_CC` to detect language version.
 * - Versions will be the year as the version * 100 as `long` which used to represent the month (as minour version)
 *
 * @def ae2f_stdc_v
 * @brief Standard C version, or at least cmake intended.
 *
 * @def ae2f_stdcc_v
 * @brief 
 * Standard C++ version. \n\n
 *
 * - When it is compiled as standard C, this will be 0.
 * - When it is not compiled as standard C, this will be decided by cmake.
 *
 * @macro __ae2f_stdcheck_C
 * @brief Check if it hits over specific standard C version.
 * @param v a standard C version to check
 *
 * @macro __ae2f_stdcheck_CC
 * @brief Check if it hits over specific standard C++ version.
 * @param v a standard C++ version to check
 * */
#include "./LangVer.auto.h"


#undef	ae2f_stdcc_v
#ifdef	__cplusplus
#define	ae2f_stdcc_v	(__cplusplus)
#else	
#define ae2f_stdcc_v	0L
#endif

#undef	ae2f_stdc_v
#ifdef	__STDC_VERSION__
#define ae2f_stdc_v	(__STDC_VERSION__)
#elif	defined(__STDC__) && (__STDC__)
#define	ae2f_stdc_v	198900L
#else
#define ae2f_stdc_v	((ae2f_LangVer_C) * 100L)
#endif

#undef	__ae2f_stdcheck_C
#undef	__ae2f_stdcheck_CC

#define __ae2f_stdcheck_C(v)	(ae2f_stdc_v >= (v))
#define __ae2f_stdcheck_CC(v)	(ae2f_stdcc_v >= (v))
