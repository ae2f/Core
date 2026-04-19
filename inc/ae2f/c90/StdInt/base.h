#ifndef	ae2f_c90_stdint_base_h
#define	ae2f_c90_stdint_base_h


#include <ae2f/c90/.limits.width.h>

#ifndef int_fast8_t
typedef	signed int int_fast8_t;
#define	int_fast8_t	int_fast8_t
#endif
typedef char ae2f_CHECK[sizeof(int_fast8_t) >= 1 ? 1 : - 1];

#ifndef int_least8_t
typedef	signed char int_least8_t;
#define int_least8_t	int_least8_t
#endif
typedef char ae2f_CHECK[sizeof(int_least8_t) >= 1 ? 1 : - 1];

#if	!defined(i8) && SCHAR_WIDTH == 8
#define int8_t		int_least8_t
typedef char ae2f_CHECK[sizeof(int8_t) == 1 ? 1 : - 1];
#endif

#ifndef	uint_fast8_t
#define uint_fast8_t		unsigned int
#endif
typedef char ae2f_CHECK[sizeof(uint_fast8_t) >= 1 ? 1 : - 1];

#ifndef	uint_least8_t
#define uint_least8_t		unsigned char
#endif
typedef char ae2f_CHECK[sizeof(uint_least8_t) >= 1 ? 1 : - 1];

#if	!defined(uint8_t) && UCHAR_WIDTH == 8
#define uint8_t			uint_least8_t
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

#ifndef	uint_fast16_t
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
typedef char ae2f_CHECK[sizeof(int_least32_t) >= 4 ? 1 : -1];

#ifndef int_fast32_t
#define int_fast32_t	int_least32_t
#endif
typedef char ae2f_CHECK[sizeof(int_fast32_t) >= 4 ? 1 : -1];

#if !defined(int32_t) && INT_WIDTH == 32
#define int32_t	int_least32_t
typedef char ae2f_CHECK[sizeof(int32_t) == 4 ? 1 : -1];
#endif

#if	!defined(uint_least32_t) && UINT_WIDTH >= 32
#define	uint_least32_t	unsigned int
#elif	!defined(uint_least32_t)
#define uint_least32_t	unsigned long
#endif
typedef char ae2f_CHECK[sizeof(uint_least32_t) >= 4 ? 1 : -1];

#ifndef uint_fast32_t
#define uint_fast32_t	uint_least32_t
#endif
typedef char ae2f_CHECK[sizeof(uint_fast32_t) >= 4 ? 1 : -1];

#if !defined(uint32_t) && UINT_WIDTH == 32
#define uint32_t	uint_least32_t
typedef char ae2f_CHECK[sizeof(uint32_t) == 4 ? 1 : -1];
#endif

/** INT32 */

#if !defined(int_least64_t) &&	LONG_WIDTH >= 64
#define int_least64_t	signed long
#define INT_LEAST64_WIDTH	LONG_WIDTH
#elif				LLONG_WIDTH >= 64
#define int_least64_t	signed long long
#define INT_LEAST64_WIDTH	LLONG_WIDTH
#elif				AE2F__INT64_WIDTH >= 64
#define	int_least64_t	__int64
#define	INT_LEAST64_WIDTH	AE2F__INT64_WIDTH
#endif

#ifdef int_least64_t
typedef char ae2f_CHECK[sizeof(int_least64_t) >= 8 ? 1 : -1];
#endif

#if defined(int_least64_t) && !defined(int_fast64_t)
#define int_fast64_t	int_least64_t
typedef char ae2f_CHECK[sizeof(int_fast64_t) >= 8 ? 1 : -1];
#endif

#if defined(int_least64_t) && !defined(int64_t) && INT_LEAST64_WIDTH == 64
#define int64_t	int_least64_t
typedef char ae2f_CHECK[sizeof(int64_t) == 8 ? 1 : -1];
#endif

#if !defined(uint_least64_t) &&	ULONG_WIDTH >= 64
#define uint_least64_t	unsigned long
#define UINT_LEAST64_WIDTH	ULONG_WIDTH
#elif				ULLONG_WIDTH >= 64
#define uint_least64_t	unsigned long long
#define UINT_LEAST64_WIDTH	ULLONG_WIDTH
#elif				AE2F__UINT64_WIDTH >= 64
#define	uint_least64_t	unsigned __int64
#define	UINT_LEAST64_WIDTH	AE2F__UINT64_WIDTH
#endif
#ifdef uint_least64_t
typedef char ae2f_CHECK[sizeof(uint_least64_t) >= 8 ? 1 : -1];
#endif

#if defined(uint_least64_t) && !defined(uint_fast64_t)
#define uint_fast64_t	uint_least64_t
typedef char ae2f_CHECK[sizeof(uint_fast64_t) >= 8 ? 1 : -1];
#endif

#if defined(uint_least64_t) && !defined(uint64_t) && UINT_LEAST64_WIDTH == 64
#define uint64_t	uint_least64_t
typedef char ae2f_CHECK[sizeof(uint64_t) == 8 ? 1 : -1];
#endif
/* INT64 */

#endif

