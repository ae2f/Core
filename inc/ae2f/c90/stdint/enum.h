#ifndef	ae2f_c90_StdInt_enum_h
#define ae2f_c90_StdInt_enum_h

#include "./filter.h"
#include <ae2f/c90/lmts/.width.h>

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

#endif
