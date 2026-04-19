#ifndef ae2f_c90_intptr_h
#define ae2f_c90_intptr_h

#include "./filter.h"
#include <ae2f/c90/.ptrsz.h>

#ifndef	int_leastptr_t
#	if	ae2f_PTRSZ_SIZE <= 1
#	define	int_leastptr_t int_least8_t
#	elif	ae2f_PTRSZ_SIZE <= 2
#	define	int_leastptr_t int_least16_t
#	elif	ae2f_PTRSZ_SIZE <= 4
#	define	int_leastptr_t int_least32_t
#	elif	ae2f_PTRSZ_SIZE <= 8
#	define	int_leastptr_t int_least64_t
#	endif
#endif

#ifndef	uint_leastptr_t
#	if	ae2f_PTRSZ_SIZE <= 1
#	define	uint_leastptr_t uint_least8_t
#	elif	ae2f_PTRSZ_SIZE <= 2
#	define	uint_leastptr_t uint_least16_t
#	elif	ae2f_PTRSZ_SIZE <= 4
#	define	uint_leastptr_t uint_least32_t
#	elif	ae2f_PTRSZ_SIZE <= 8
#	define	uint_leastptr_t uint_least64_t
#	endif
#endif

#ifndef	intptr_t
#	if	ae2f_PTRSZ_SIZE == 1 && defined(int8_t)
#	define	intptr_t int8_t
#	elif	ae2f_PTRSZ_SIZE == 2 && defined(int16_t)
#	define	intptr_t int16_t
#	elif	ae2f_PTRSZ_SIZE == 4 && defined(int32_t)
#	define	intptr_t int32_t
#	elif	ae2f_PTRSZ_SIZE == 8 && defined(int64_t)
#	define	intptr_t int64_t
#	endif
#endif

#ifndef	uintptr_t
#	if	ae2f_PTRSZ_SIZE == 1 && defined(uint8_t)
#	define	uintptr_t uint8_t
#	elif	ae2f_PTRSZ_SIZE == 2 && defined(uint16_t)
#	define	uintptr_t uint16_t
#	elif	ae2f_PTRSZ_SIZE == 4 && defined(uint32_t)
#	define	uintptr_t uint32_t
#	elif	ae2f_PTRSZ_SIZE == 8 && defined(uint64_t)
#	define	uintptr_t uint64_t
#	endif
#endif

typedef char ae2f_CHECK[sizeof(int_leastptr_t) >= sizeof(void*) ? 1 : -1];
typedef char ae2f_CHECK[sizeof(uint_leastptr_t) >= sizeof(void*) ? 1 : -1];
#endif
