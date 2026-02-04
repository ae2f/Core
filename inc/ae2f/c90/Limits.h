/** 
 * @file Limits.h
 * @brief limits.h with guaranteed width constants for C90 (Powered by cmake).
 * */
#ifndef ae2f_limits_h
#define ae2f_limits_h

#include <limits.h>
#include "../LangVer.h"

/** @brief width fetching */
#if !__ae2f_lvcheck_c(202311L)
#include "./.limits.width.h"
#endif

#endif
