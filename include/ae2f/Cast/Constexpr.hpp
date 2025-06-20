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

#include "../LangVer.auto.h"

#if (defined(__cplusplus))
#if __cplusplus >= 201103L
#define constexprmethod     constexpr
#define constexprfun        constexpr
#else
#define constexpr           const
#define constexprmethod     inline 
#define constexprfun        inline static
#endif


#else

#if ae2f_LangVer_C >= 123
#else
#define constexpr           const
#endif

#define constexprfun        inline static

#endif

#if defined(__cplusplus)
#if (defined(__cplusplus) && __cplusplus >= 202002L)
#define constevalmethod consteval
#else 
/// @brief
/// C++ keyword for constant-time functions.
#define consteval       constexprfun
#define constevalmethod constexprmethod
#endif

#else

#define consteval       inline static

#endif

#ifndef __cplusplus
/// @brief
/// Means that there will be no exception thrown written in code.
#define noexcept
#endif

#endif
