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

#if __ae2f_cppcheck(202002L)
#define constexprvirtual constexpr virtual
#else
#define constexprvirtual virtual
#endif // C++20

#if __ae2f_cppcheck(201402L)
#define constextendedfun constexpr
#define constextendedmethod constexpr
#else
#define constextendedfun inline
#define constextendedmethod inline
#endif // C++14

#if __ae2f_cppcheck(201103L)
#define constexprmethod constexpr
#define constexprfun constexpr
#else
#define constexprmethod inline
#define constexprfun inline
#define virtual

#if !__ae2f_cppcheck(0) /* C */
#if __ae2f_lvcheck_c(2023)
/** cosntexpr variable */
#else
#define constexpr static const
#endif /* C23 */
#endif /* C */

#endif // C++11

#if __ae2f_cppcheck(202002L)
#define constevalmethod consteval // C++20
#elif __ae2f_cppcheck(0)
/// @brief
/// C++ keyword for constant-time functions.
#define consteval constexprfun
#define constevalmethod constexprmethod
#else
#define consteval inline
#endif // C++20

#if !__ae2f_cppcheck(201103L)
/// @brief
/// Means that there will be no exception thrown written in code.
#define noexcept
#endif // C

#endif
