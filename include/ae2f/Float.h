/**
 * @file Float.h
 * @brief
 * Here, float will be treated as bit vector with four attributes:
 *
 * sign: \n	
 * 	> Whether it has sign or not. \n
 *
 * exp:	\n
 * 	> Exponent. It will be considered as unsigned integer, \n
 * 	> Which is the exponent of the [frac]
 *
 * expbiasp: \n
 * 	> Exponent bias in order to be considered as zero. \n
 * 	> For handling possibly negative values of [exp] (such as 0.5) \n
 *
 * 	> Here, the value of exponent bias is limited with following rules:
 * 		- It must be (2^([expbiasp]) - 1), and you are actually setting [expbiasp].
 * 		- [expbiasp] must be between 1 and [exp].
 *
 * frac: \n
 * 	> The actual "value" for floating point.
 *
 * ==================
 *
 * Following is the expected structure as bit vector: \n
 * [frac | exp | sign]
 * 
 * Size of this will be calculated as: \n
 * [sign] + [exp] + [frac]
 */

#ifndef ae2f_Float_h
#define ae2f_Float_h

#include "./Float.auto.h"
#include "./BInt.h"

#define ae2f_FloatBitSz(sign, exp, frac) ((sign) + (exp) + (frac))

#define ae2f_FloatByteSz(sign, exp, frac) \
	ae2f_BitToByteCount(ae2f_FloatBitSz(sign, exp, frac))

typedef uint8_t ae2f_errFloat_t;
enum ae2f_errFloat {
	ae2f_errFloat_OVERFLOW,
	ae2f_errFloat_UNDERFLOW
};

/** @todo Kill this shit after debugging */
#include <stdio.h>

/**
 * @brief
 * Rearrange a number to another structure.
 * 
 * @todo
 * It does not work when exp is negative. (like less than 1) \n
 * Handling with `expbiasp` would be needed.
 * */
constexprfun
ae2f_err_t
ae2f_FloatCast(
		void* _dest
		, bool destsign
		, size_t destexp
		, size_t destexpbiasp
		, size_t destfrac

		, const void* _src
		, bool srcsign
		, size_t srcexp
		, size_t srcexpbiasp
		, size_t srcfrac

		, ae2f_errFloat_t* errret
		) noexcept
{
	uint8_t* dest = ae2f_reinterpret_cast(uint8_t*, _dest);
	const uint8_t* src = ae2f_reinterpret_cast(const uint8_t*, _src);

	{
		if(!dest)	return ae2f_errGlob_PTR_IS_NULL;
		if(!src)	return ae2f_errGlob_PTR_IS_NULL;

		if(destexp > (sizeof(size_t) << 3))
			return ae2f_errGlob_IMP_NOT_FOUND;
		if(srcexp > (sizeof(size_t) << 3))
			return ae2f_errGlob_IMP_NOT_FOUND;

		for(size_t i = 0; i < ae2f_FloatByteSz(destsign, destexp, destfrac); i++) 
			dest[i] = 0;

		printf("%d\n", ae2f_FloatByteSz(destsign, destexp, destfrac));
	
		for(size_t i = 0; i < (srcfrac) && i < (destfrac); i++) {
			const size_t 
				_dest = 	(destfrac - i)
				, desti =	_dest >> 3
				, destr = 	_dest & 7
	
				, _src =	(srcfrac - i)
				, srci =	_src >> 3
				, srcr =	_src & 7;
	
			dest[desti] |= ae2f_BitVecGet(src[srci], srcr) << destr;
		}

		for(size_t i = 0; i < srcexp && i < destexp; i++) {
			const size_t 
				_dest = 	(destfrac + destexp - i)
				, desti =	_dest >> 3
				, destr = 	_dest & 7
	
				, _src =	(srcfrac + srcexp - i)
				, srci =	_src >> 3
				, srcr =	_src & 7;
	
			dest[desti] |= ae2f_BitVecGet(src[srci], srcr) << destr;
		}

		puts("asdfsdfdddd");
	
		return ae2f_errGlob_OK;
	}
}

#endif
