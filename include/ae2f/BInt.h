/**
 * @file BInt.h
 * 
 * @brief
 * # Bits Int
 *
 * Operates basic calculations as unit of bits with attributes. \n
 * It is considered to use compliments of 2.
 *
 * =====================
 *
 * Attributes:
 *
 * padbi: \n
 * 	> padding bit index from the byte. \n
 * 	> must be between 0 ~ 8.
 *
 *
 * bitc: \n
 * 	> bit count. (sign bit excluded).
 *
 * sign: \n
 * 	> whether it has sign or not.
 *
 * ====================
 *
 * Structure expected be like:\n
 * [padbi | bitc | sign]
 *
 * Size will be calculated as: \n
 * sign + bitc
 *
 * */
#ifndef ae2f_BInt_h
#define ae2f_BInt_h

#include "./Cast.h"
#include "./BitVec.h"
#include "./errGlob.h"
#include "./Cmp.h"

#define ae2f_BIntBitSz(sign, bitc) ((sign) + (bitc))
#define ae2f_BIntByteSz(padbi, sign, bitc) ae2f_BitToByteCount((padbi) + (sign) + (bitc))

/** 
 * @brief
 * Comparing with 0. \n
 * Using only sign.
 * */
constexprfun ae2f_CmpFunRet_t
ae2f_BIntCmp0(
		const void*	_l
		, bool		lsign
		, size_t	lpadbi
		, size_t	lbitc
		) noexcept
{
	const uint8_t* l = ae2f_reinterpret_cast(const uint8_t*, _l);

	{
		if(!l) return ae2f_CmpFunRet_EQUAL;
		bool hassomething = 0;
	
		for(size_t _i = 0; _i < lbitc; _i++) 
		{ 
			const size_t  
			i =		_i + lpadbi 
			, chunk =	(lpadbi + i) 
			, ichunk =	chunk >> 3 
			, irest = 	chunk & 7; 
	
			if((hassomething = ae2f_BitVecGet(l[ichunk], irest))) 
				return lsign
					? ae2f_CmpFunRet_LISLESSER  
					: ae2f_CmpFunRet_RISLESSER; 
		}
		
		return ae2f_CmpFunRet_EQUAL;
	}
}

constexprfun ae2f_CmpFunRet_t
ae2f_BIntCmp(
		const void*	_l
		, bool		lsign
		, size_t	lpadbi
		, size_t	lbitc

		, const void*_r
		, bool		rsign
		, size_t	rpadbi
		, size_t	rbitc
		) noexcept
{
	const uint8_t
	*l = ae2f_reinterpret_cast(const uint8_t*, _l), 
	*r = ae2f_reinterpret_cast(const uint8_t*, _r);

	{
		/** Sign */
		const ae2f_CmpFunRet_t 
			// aka sl
			sign_global 
			= ae2f_BIntCmp0(l, lsign, lpadbi, lbitc);
	
	
		{
			const ae2f_CmpFunRet_t
				sr = ae2f_BIntCmp0(r, rsign, rpadbi, rbitc);
	
			if((sign_global ^ sr) < 0) // Are those two's sign different
				return sign_global - sr;
		}
	
		if(!l) return ae2f_CmpFunRet_EQUAL;
		if(!r) return ae2f_CmpFunRet_EQUAL;
	
		/** Content, here, sign is equal. */
	
		/** When count is not equal: */
		if(lbitc > rbitc)
		{
			const size_t
				Pad = lpadbi + rbitc
				, PadIdx = Pad >> 3
				, PadRest = Pad & 7
				;
	
			if(ae2f_BIntCmp0(l + PadIdx, 0, PadRest, lbitc - rbitc))
				return sign_global;
	
		}
	
		else if (rbitc > lbitc)
		{
			const size_t
				Pad = rpadbi + lbitc
				, PadIdx = Pad >> 3
				, PadRest = Pad & 7
				;
	
			if(ae2f_BIntCmp0(r + PadIdx, 0, PadRest, rbitc - lbitc))
				return ~sign_global; // Just to switch the sign flag.
		}
	
		for(size_t i = 0; i < rbitc; i++)
		{
			const int8_t diff = 
				  ae2f_BitVecGet(l[(lpadbi + i) >> 3], (lpadbi + i))
				  - ae2f_BitVecGet(r[(lpadbi + i) >> 3], (rpadbi + i))
				  ;
	
			if(diff)
				return diff/* l - r */ ^ sign_global /* l */;
		}
	
		return ae2f_CmpFunRet_EQUAL;
	}
}

/** @Compliment */
constexprfun ae2f_err_t
ae2f_BIntNegative() noexcept;

#endif
