/**
 * @file cc.h
 * @brief Utility marks which could partially be available with gnu compiler.
 * */
#ifndef ae2f_cc_h
#define ae2f_cc_h

#include "./cc/gnuc.h"
#include "./LangVer.h"

/** 
 * @def ae2f_ccpure
 * @brief Keyword as [[pure]] on C23 or with GNU extension.
 * */
#if	ae2f_stdc_v >= 202300L && !defined(__cplusplus)
#define ae2f_ccpure	[[pure]]
#else
#define ae2f_ccpure	_ae2f_gnuc(__attribute__((pure)))
#endif

/** 
 * @def ae2f_ccconst
 * @brief Keyword as [[const]] on C23 or with GNU extension.
 * */
#if	ae2f_stdc_v >= 202300L && !defined(__cplusplus)
#define ae2f_ccconst	[[const]]
#else
#define ae2f_ccconst	_ae2f_gnuc(__attribute__((const)))
#endif

#endif
