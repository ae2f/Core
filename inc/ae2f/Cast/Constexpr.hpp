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
#define if_constexpr if constexpr
#else
#define if_constexpr if
#endif

#if __ae2f_stdcheck_CC(202002L)
#define if_consteval if consteval
#else
#define if_consteval if (0)
#endif

#if __ae2f_stdcheck_CC(202002L)
#define constexprvirtual constexpr virtual
/** constinit */
#else
#define constexprvirtual virtual
#define constinit	/* not available */
#endif /* C++20 */

#if __ae2f_stdcheck_CC(201402L)
#define constextendedfun	constexpr
#define constextendedeval 	constexpr

#define constextendedmethod	constexpr
#define constextendedmethodeval	constexpr

#else
#define constextendedfun	inline
#define constextendedmethod	inline

#define constextendedeval	inline
#define constextendedmethodeval	inline
#endif // C++14

#if __ae2f_stdcheck_CC(201103L)
#define constexprmethod		constexpr
#define constexprfun		constexpr
#define constevalmethod		constexpr

#else
#define constexprmethod		inline
#define constexprfun		inline
#define constevalmethod		inline
#define virtual

#if !defined(__cplusplus) /* C */

#if !defined(__cplusplus) && __ae2f_lvcheck_c(2023)
/** cosntexpr variable */
#else
#define constexpr
#endif /* C23 */


#endif /* C */

#endif // C++11

#if __ae2f_stdcheck_CC(202002L)
#undef constevalmethod
#define constevalmethod consteval /* C++20 */
#elif __ae2f_stdcheck_CC(0)

#undef constevalmethod
/// @brief
/// C++ keyword for constant-time functions.
#define consteval
#define constevalmethod constexprmethod

#else

#define consteval
#endif // C++20

#endif
