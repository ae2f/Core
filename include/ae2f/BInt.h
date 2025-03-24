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

#define ae2f_BIntBitSz(sign, bitc) ((sign) + (bitc))
#define ae2f_BIntByteSz(padbi, sign, bitc) ae2f_BitToByteCount((padbi) + (sign) + (bitc))


/** 
 * @brief
 * Comparing with 0. \n
 * Using only sign.
 * */


#if ae2f_WhenCXX(!)0
template<bool sign, size_t padbi, size_t bitc, typename T>
constexpr ae2f_CmpFunRet_t ae2f_BIntSign(const T* a);

constexprfun ae2f_CmpFunRet_t
ae2f_BIntCmp0(
		const uint8_t*	l
		, bool  	lsign
		, size_t 	lpadbi
		, size_t	lbitc
		) noexcept;

template<typename T>
constexprfun ae2f_CmpFunRet_t
ae2f_BIntCmp0(
		const T*	l
		, bool		lsign
		, size_t	lpadbi
		, size_t	lbitc
		) noexcept
{
	return ae2f_BIntCmp0(
			ae2f_reinterpret_cast(
				// const T*, 
				const void*
				, l
				)
			, lsign
			, lpadbi
			, lbitc
			);
}


template<bool sign, size_t padbi, size_t bitc, typename T>
constexpr ae2f_CmpFunRet_t ae2f_BIntCmp0(const T* a) 
{
	return ae2f_BIntCmp0(
			a,
			sign, 
			padbi, 
			bitc
			); 
}
#endif

constexprfun ae2f_CmpFunRet_t
ae2f_BIntCmp0(
		const uint8_t*	l
		, bool		lsign
		, size_t	lpadbi
		, size_t	lbitc
		) noexcept
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


#if ae2f_WhenCXX(!)0

template<
  bool lsign
, size_t lpadbi
, size_t lbitc

, bool rsign
, size_t rpadbi
, size_t rbitc
, typename T1
, typename T2
>
constexpr ae2f_CmpFunRet_t
ae2f_BIntCmp(
		const T1*	l
		, const T2*	r
		) noexcept;

constexprfun ae2f_CmpFunRet_t
ae2f_BIntCmp(
		const uint8_t*	l
		, bool		lsign
		, size_t	lpadbi
		, size_t	lbitc

		, const uint8_t*r
		, bool		rsign
		, size_t	rpadbi
		, size_t	rbitc
		) noexcept;

template<typename T0, typename T1>
constexprfun ae2f_CmpFunRet_t
ae2f_BIntCmp(
		const T0*	l
		, bool		lsign
		, size_t	lpadbi
		, size_t	lbitc

		, const T1*	r
		, bool		rsign
		, size_t	rpadbi
		, size_t	rbitc
		)
{
	return ae2f_BIntCmp(
			ae2f_reinterpret_cast(
				//const T0*, 
				const uint8_t*, l)
			, lsign, lpadbi, lbitc

			, ae2f_reinterpret_cast(
				// const T1*
				const uint8_t*, r)
			, rsign, rpadbi, rbitc
			);
}

template<
bool lsign, size_t lpadbi, size_t lbitc
, bool rsign, size_t rpadbi, size_t rbitc
, typename T1, typename T2
>
constexpr ae2f_CmpFunRet_t
ae2f_BIntCmp(
		const T1*	l
		, const T2*	r
) noexcept
{
	return ae2f_BIntCmp(
			l, lsign, lpadbi, lbitc
			, r, rsign, rpadbi, rbitc
			);
}


#endif


constexprfun ae2f_CmpFunRet_t
ae2f_BIntCmp(
		const uint8_t*	l
		, bool		lsign
		, size_t	lpadbi
		, size_t	lbitc

		, const uint8_t*r
		, bool		rsign
		, size_t	rpadbi
		, size_t	rbitc
		) noexcept
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

/** @Compliment */
constexprfun ae2f_err_t
ae2f_BIntAddOne() noexcept

#endif
