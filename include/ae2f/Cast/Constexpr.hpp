/**
 * @file Constexpr.hpp
 * @author ae2f
 * @brief
 * @date 2025-02-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef ae2f_Cast_Constexpr_hpp
#define ae2f_Cast_Constexpr_hpp

#if defined(__cplusplus)

#if __cplusplus < 202002L
/// @brief
/// C++ keyword for constant-time functions.
#define consteval constexpr
#endif

#else

#define consteval inline

#endif

#endif
