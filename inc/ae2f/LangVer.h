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
 * @brief Standard C++ version, or at least cmake intended.
 * */
#include "./LangVer.auto.h"

#ifdef	__cplusplus
#undef	ae2f_stdcc_v
#define	ae2f_stdcc_v	(__cplusplus)
#else
#define ae2f_stdcc_v	((ae2f_LangVer_CC) * 100L)
#endif

#ifdef	__STDC_VERSION__
#undef	ae2f_stdc_v
#define ae2f_stdc_v	(__STDC_VERSION__)
#else
#undef	ae2f_stdc_v
#define ae2f_stdc_v	((ae2f_LangVer_C) * 100L)
#endif

#undef	__ae2f_stdcheck_C
#undef	__ae2f_stdcheck_CC

#define __ae2f_stdcheck_C(v)	(ae2f_stdc_v >= (v))
#define __ae2f_stdcheck_CC(v)	(ae2f_stdcc_v >= (v))
