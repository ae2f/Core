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

#include "./stdint-def.h"

#ifndef	i8_fast
#define	i8_fast		int_fast8_t
#endif

#ifndef	i16_fast
#define	i16_fast	int_fast16_t
#endif

#ifndef	i32_fast
#define	i32_fast	int_fast32_t
#endif

#ifndef	i64_fast
#define	i64_fast	int_fast64_t
#endif

#ifndef	u8_fast
#define	u8_fast		uint_fast8_t
#endif

#ifndef	u16_fast
#define	u16_fast	uint_fast16_t
#endif

#ifndef	u32_fast
#define	u32_fast	uint_fast32_t
#endif

#ifndef	u64_fast
#define	u64_fast	uint_fast64_t
#endif

#ifndef	i8_least
#define	i8_least	int_least8_t
#endif

#ifndef	i16_least
#define	i16_least	int_least16_t
#endif

#ifndef	i32_least
#define	i32_least	int_least32_t
#endif

#ifndef	i64_least
#define	i64_least	int_least64_t
#endif

#ifndef	u8_least
#define	u8_least	uint_least8_t
#endif

#ifndef	u16_least
#define	u16_least	uint_least16_t
#endif

#ifndef	u32_least
#define	u32_least	uint_least32_t
#endif

#ifndef	u64_least
#define	u64_least	uint_least64_t
#endif

#ifndef	i8
#define	i8		int8_t
#endif

#ifndef	i16
#define	i16		int16_t
#endif

#ifndef	i32
#define	i32		int32_t
#endif

#ifndef	i64
#define	i64		int64_t
#endif

#ifndef	u8
#define	u8		uint8_t
#endif

#ifndef	u16
#define	u16		uint16_t
#endif

#ifndef	u32
#define	u32		uint32_t
#endif

#ifndef	u64
#define	u64		uint64_t
#endif

#ifndef	imax
#define	imax		intmax_t
#endif

#ifndef	umax
#define	umax		uintmax_t
#endif

#ifndef	iptr
#define	iptr		intptr_t
#endif

#ifndef	uptr
#define	uptr		uintptr_t
#endif

#if	AE2F_ENUM_WIDTH == 8

/** enum: 8 **/
#define	int_leastenum_t		int_least8_t
#define int_fastenum_t		int_fast8_t
#define uint_leastenum_t	uint_least8_t
#define uint_fastenum_t		uint_fast8_t

#ifdef	int8_t
#define	intenum_t		int8_t
#endif

#ifdef	uint8_t
#define	uintenum_t		uint8_t
#endif
/** enum: 8 **/

#elif AE2F_ENUM_WIDTH <= 16

/** enum: 16 **/
#define	int_leastenum_t		int_least16_t
#define int_fastenum_t		int_fast16_t
#define uint_leastenum_t	uint_least16_t
#define uint_fastenum_t		uint_fast16_t

#ifdef	int16_t
#define	intenum_t		int16_t
#endif

#ifdef	uint16_t
#define	uintenum_t		uint16_t
#endif

/** enum: 16 **/

#elif	AE2F_ENUM_WIDTH <= 32

/** enum: 32 **/
#define	int_leastenum_t		int_least32_t
#define int_fastenum_t		int_fast32_t
#define uint_leastenum_t	uint_least32_t
#define uint_fastenum_t		uint_fast32_t

#ifdef	int32_t
#define	intenum_t		int32_t
#endif

#ifdef	uint32_t
#define	uintenum_t		uint32_t
#endif
/** enum: 32 **/

#elif AE2F_ENUM_WIDTH <= 64

/** enum: 64 **/
#define	int_leastenum_t		int_least64_t
#define int_fastenum_t		int_fast64_t
#define uint_leastenum_t	uint_least64_t
#define uint_fastenum_t		uint_fast64_t

#ifdef	int64_t
#define	intenum_t		int64_t
#endif

#ifdef	uint64_t
#define	uintenum_t		uint64_t
#endif
/** enum: 64 **/

#endif	/** enumint, 64 */



#endif	/** stdint */

