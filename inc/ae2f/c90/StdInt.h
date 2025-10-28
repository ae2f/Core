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
#else

#include "./ptrsz.auto.h"
#include "./Limits.h"

#ifndef int8_t
#define int8_t	char
#endif

#ifndef uint8_t
#define uint8_t	unsigned char
#endif

#ifndef int16_t
#define int16_t	short
#endif

#ifndef uint16_t
#define uint16_t unsigned short
#endif

#ifndef int32_t
#if (INT_MAX) >> 31
#define int32_t	int
#else
#define int32_t long
#endif
#endif

#ifndef uint32_t
#if (UINT_MAX) >> 31
#define uint32_t unsigned int
#else
#define uint32_t unsigned long
#endif
#endif

#ifndef int64_t
#if (LONG_WIDTH) >= 64
#define int64_t	long
#elif (LLONG_WIDTH) >= 64
#define int64_t	long long
#endif
#endif

#ifndef uint64_t
#if (ULONG_WIDTH) >= 64
#define uint64_t unsigned long
#elif (ULLONG_WIDTH) >= 64
#define uint64_t unsigned long long
#endif
#endif


#if	ae2f_PTRSZ_SIZE == 1

#ifndef intptr_t
#define intptr_t	int8_t
#endif

#ifndef uintptr_t
#define uintptr_t	uint8_t
#endif

#elif	ae2f_PTRSZ_SIZE <= 2

#ifndef intptr_t
#define intptr_t	int16_t
#endif

#ifndef uintptr_t
#define uintptr_t	uint16_t
#endif

#elif	ae2f_PTRSZ_SIZE <= 4

#ifndef intptr_t
#define intptr_t	int32_t
#endif

#ifndef uintptr_t
#define uintptr_t	uint32_t
#endif

#elif	ae2f_PTRSZ_SIZE <= 8

#ifndef intptr_t
#define intptr_t	int64_t
#endif

#ifndef uintptr_t
#define uintptr_t	uint64_t
#endif

#endif

typedef char ae2f_int8_CHECK[sizeof(int8_t) >= 1 ? 1 : -1];
typedef char ae2f_uint8_CHECK[sizeof(uint8_t) >= 1 ? 1 : -1];

typedef char ae2f_int16_CHECK[sizeof(int16_t) >= 2 ? 1 : -1];
typedef char ae2f_uint16_CHECK[sizeof(uint16_t) >= 2 ? 1 : -1];

typedef char ae2f_int32_CHECK[sizeof(int32_t) >= 4 ? 1 : -1];
typedef char ae2f_uint32_CHECK[sizeof(uint32_t) >= 4 ? 1 : -1];

typedef char ae2f_int64_CHECK[sizeof(int64_t) >= 2 ? 1 : -1];
typedef char ae2f_uint64_CHECK[sizeof(uint64_t) >= 2 ? 1 : -1];

typedef char ae2f_intptr_CHECK[sizeof(intptr_t) >= sizeof(void*) ? 1 : -1];
typedef char ae2f_uintptr_CHECK[sizeof(uintptr_t) >= sizeof(void*) ? 1 : -1];

#endif
#endif
