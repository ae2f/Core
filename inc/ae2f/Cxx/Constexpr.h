/**
 * @file consteval.hpp
 * @author ae2f
 * @brief
 * @date 2025-02-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef ae2f_Cast_consteval_hpp
#define ae2f_Cast_consteval_hpp
#include "../LangVer.h"



#if __ae2f_stdcheck_CC(201703L)
#define ae2f_if_constexpr if constexpr
#else
#define ae2f_if_constexpr if
#endif

#if __ae2f_stdcheck_CC(202002L)
#define ae2f_if_consteval	if consteval
#else
#define ae2f_if_consteval	if (0)
#endif

#if __ae2f_stdcheck_CC(202002L)
#define ae2f_constexprvirtual constexpr virtual
#define ae2f_constinit	constinit
#else
#define ae2f_constexprvirtual virtual
#define ae2f_constinit	/* not available */
#endif /* C++20 */

#if __ae2f_stdcheck_CC(201402L)
#define ae2f_constextendedfun	constexpr
#define ae2f_constextendedeval 	constexpr

#define ae2f_constextendedmethod	constexpr
#define ae2f_constextendedmethodeval	constexpr

#else
#define ae2f_constextendedfun	inline
#define ae2f_constextendedmethod	inline

#define ae2f_constextendedeval	inline
#define ae2f_constextendedmethodeval	inline
#endif /* C++14 */

#if __ae2f_stdcheck_CC(201103L)
#define ae2f_constexprmethod		constexpr
#define ae2f_constexprfun		constexpr
#define ae2f_constevalmethod		constexpr
#define ae2f_virtual		virtual
#else
#define ae2f_constexprmethod		inline
#define ae2f_constexprfun		inline
#define ae2f_constevalmethod		inline
#define ae2f_virtual		

#if !defined(__cplusplus) /* C */

#if !defined(__cplusplus) && __ae2f_lvcheck_c(2023)
/** cosntexpr variable */
#define ae2f_constexpr	constexpr
#else
#define ae2f_constexpr
#endif /* C23 */


#endif /* C */

#endif /* C++11 */

#if __ae2f_stdcheck_CC(202002L)
#undef ae2f_constevalmethod
#define ae2f_constevalmethod consteval /* C++20 */
#define ae2f_consteval	consteval
#elif __ae2f_stdcheck_CC(0)


/** @brief C++ keyword for const-time functions */
#define ae2f_consteval

#undef ae2f_constevalmethod
#define ae2f_constevalmethod ae2f_constexprmethod

#else

#define ae2f_consteval
#endif /* C++20 */

#if !__ae2f_stdcheck_CC(201103L)

/** @brief There will be no exception thrown */
#define ae2f_noexcept
#define ae2f_constexpr
#else
#define ae2f_noexcept noexcept
#define ae2f_constexpr constexpr
#endif /* C++<=11 */

#if __cplusplus
#else
#undef  ae2f_noexcept
#define ae2f_noexcept
#endif

#endif
