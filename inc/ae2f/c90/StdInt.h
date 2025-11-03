/**
 * @file StdInt.h
 * @brief stdint subset for c90
 * @warning
 * - Following types are guaranteed `at least of` that size, NOT `exact` as that size.	\n
 * - This is for convention. Do not believe its types are guaranteed as fixed.		\n
 * - This file may not contain 64 bits.
 * 
 * */
#ifndef ae2f_stdint_h
#define ae2f_stdint_h


#if __STDC_VERSION__
#include <stdint.h>
#elif __cplusplus
#include <cstdint>
#else
#include "./ptrsz.auto.h"
#include "./Limits.h"

#ifndef int_fast8_t
#define int_fast8_t	signed int
#endif
typedef char ae2f_CHECK[sizeof(int_fast8_t) >= 1 ? 1 : - 1];

#ifndef int_least8_t
#define int_least8_t	signed char
#endif
typedef char ae2f_CHECK[sizeof(int_least8_t) >= 1 ? 1 : - 1];

#if	!defined(int8_t) && SCHAR_WIDTH == 8
#define int8_t		int_least8_t
typedef char ae2f_CHECK[sizeof(int8_t) == 1 ? 1 : - 1];
#endif

#ifndef uint_fast8_t
#define uint_fast8_t	unsigned int
#endif
typedef char ae2f_CHECK[sizeof(uint_fast8_t) >= 1 ? 1 : - 1];

#ifndef uint_least8_t
#define uint_least8_t	unsigned char
#endif
typedef char ae2f_CHECK[sizeof(uint_least8_t) >= 1 ? 1 : - 1];

#if	!defined(uint8_t) && UCHAR_WIDTH == 8
#define uint8_t		uint_least8_t
typedef char ae2f_CHECK[sizeof(uint8_t) == 1 ? 1 : - 1];
#endif

/* CHAR */

#ifndef int_fast16_t
#define int_fast16_t	signed int
#endif
typedef char ae2f_CHECK[sizeof(int_fast16_t) >= 2 ? 1 : - 1];

#ifndef int_least16_t
#define int_least16_t	signed short
#endif
typedef char ae2f_CHECK[sizeof(int_least16_t) >= 2 ? 1 : - 1];

#if	!defined(int16_t) && SHRT_WIDTH == 16
#define int16_t		int_least16_t
#endif
typedef char ae2f_CHECK[sizeof(int16_t) == 2 ? 1 : - 1];

#ifndef uint_fast16_t
#define uint_fast16_t	unsigned int
#endif
typedef char ae2f_CHECK[sizeof(uint_fast16_t) >= 2 ? 1 : - 1];

#ifndef uint_least16_t
#define uint_least16_t	unsigned short
#endif
typedef char ae2f_CHECK[sizeof(uint_least16_t) >= 2 ? 1 : - 1];

#if	!defined(uint16_t) && USHRT_WIDTH == 16
#define uint16_t		uint_least16_t
typedef char ae2f_CHECK[sizeof(uint16_t) == 2 ? 1 : - 1];
#endif
/* SHRT */

#if	!defined(int_least32_t) && INT_WIDTH >= 32
#define	int_least32_t	signed int
#elif	!defined(int_least32_t)
#define int_least32_t	signed long
#endif
typedef char ae2f_CHECK[sizeof(int_least32_t) >= 4 : 1 : -1];

#ifndef int_fast32_t
#define int_fast32_t	int_least32_t
#endif
typedef char ae2f_CHECK[sizeof(int_fast32_t) >= 4 : 1 : -1];

#if !defined(int32_t) && INT_WIDTH == 32
#define int32_t	int_least32_t
typedef char ae2f_CHECK[sizeof(int32_t) == 4 : 1 : -1];
#endif

#if	!defined(uint_least32_t) && UINT_WIDTH >= 32
#define	uint_least32_t	unsigned int
#elif	!defined(uint_least32_t)
#define uint_least32_t	unsigned long
#endif
typedef char ae2f_CHECK[sizeof(uint_least32_t) >= 4 : 1 : -1];

#ifndef uint_fast32_t
#define uint_fast32_t	uint_least32_t
#endif
typedef char ae2f_CHECK[sizeof(uint_fast32_t) >= 4 : 1 : -1];

#if !defined(uint32_t) && UINT_WIDTH == 32
#define uint32_t	uint_least32_t
typedef char ae2f_CHECK[sizeof(uint32_t) == 4 : 1 : -1];
#endif

/** INT32 */


#if !defined(int_least64_t) &&	LONG_WIDTH >= 64
#define int_least64_t	signed long
#define INT_LEAST64_WIDTH	LONG_WIDTH
#elif				LLONG_WIDTH >= 64
#define int_least64_t	signed long long
#define INT_LEAST64_WIDTH	LLONG_WIDTH
#endif
#ifdef int_least64_t
typedef char ae2f_CHECK[sizeof(int_least64_t) >= 8 : 1 : -1];
#endif

#if defined(int_least64_t) && !defined(int_fast64_t)
#define int_fast64_t	int_least64_t
typedef char ae2f_CHECK[sizeof(int_fast64_t) >= 8 : 1 : -1];
#endif

#if defined(int_least64_t) && !defined(int64_t) && INT_LEAST64_WIDTH == 64
#define int64_t	int_least64_t
typedef char ae2f_CHECK[sizeof(int64_t) == 8 : 1 : -1];
#endif

#if !defined(uint_least64_t) &&	ULONG_WIDTH >= 64
#define uint_least64_t	unsigned long
#define UINT_LEAST64_WIDTH	ULONG_WIDTH
#elif				ULLONG_WIDTH >= 64
#define uint_least64_t	unsigned long long
#define UINT_LEAST64_WIDTH	ULLONG_WIDTH
#endif
#ifdef uint_least64_t
typedef char ae2f_CHECK[sizeof(uint_least64_t) >= 8 : 1 : -1];
#endif

#if defined(uint_least64_t) && !defined(uint_fast64_t)
#define uint_fast64_t	uint_least64_t
typedef char ae2f_CHECK[sizeof(uint_fast64_t) >= 8 : 1 : -1];
#endif

#if defined(uint_least64_t) && !defined(uint64_t) && UINT_LEAST64_WIDTH == 64
#define uint64_t	uint_least64_t
typedef char ae2f_CHECK[sizeof(uint64_t) == 8 : 1 : -1];
#endif
/* INT64 */

#if	ae2f_PTRSZ_SIZE == 1

#ifndef intptr_t
#define intptr_t	int_least8_t
#endif

#ifndef uintptr_t
#define uintptr_t	uint_least8_t
#endif

#elif	ae2f_PTRSZ_SIZE <= 2

#ifndef intptr_t
#define intptr_t	int_least16_t
#endif

#ifndef uintptr_t
#define uintptr_t	uint_least16_t
#endif

#elif	ae2f_PTRSZ_SIZE <= 4

#ifndef intptr_t
#define intptr_t	int_least32_t
#endif

#ifndef uintptr_t
#define uintptr_t	uint_least32_t
#endif

#elif	ae2f_PTRSZ_SIZE <= 8

#if	!defined(intptr_t) && defined(int_least64_t)
#define intptr_t	int_least64_t
#endif

#if	!defined(uintptr_t) && defined(uint_least64_t)
#define uintptr_t	uint_least64_t
#endif

#endif

typedef char ae2f_CHECK[sizeof(int_least32_t) >= 4 ? 1 : -1];
typedef char ae2f_CHECK[sizeof(uint_least32_t) >= 4 ? 1 : -1];

typedef char ae2f_CHECK[sizeof(int_least64_t) >= 8 ? 1 : -1];
typedef char ae2f_CHECK[sizeof(uint_least64_t) >= 8 ? 1 : -1];

typedef char ae2f_CHECK[sizeof(intptr_t) >= sizeof(void*) ? 1 : -1];
typedef char ae2f_CHECK[sizeof(uintptr_t) >= sizeof(void*) ? 1 : -1];


#endif
#endif
