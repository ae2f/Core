/**
 * @file Cxx.h
 * @author ae2f
 * @brief 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

/// @brief
/// Literally nothing.
#define ae2f_NONE

#if __cplusplus

/// @def ae2f_WhenCXX 
/// @brief
/// Appears when the current language is C++.
#define ae2f_WhenCXX(...) __VA_ARGS__

/// @brief
/// Appears when the current language is C.
#define ae2f_WhenC(...) ae2f_NONE

#else

/// @brief
/// Appears when the current language is C++.
#define ae2f_WhenC(...) __VA_ARGS__

/// @brief
/// Appears when the current language is C.
#define ae2f_WhenCXX(...) ae2f_NONE

#endif

/// @brief
/// 
#define ae2f_is_cxx ae2f_WhenC(0) ae2f_WhenCXX(1)

/// @brief
/// Putting it after one condition in #if will find if the script's language considered as [C], while doxygen does not notice.
/// 
/// For alter, see @ref ae2f_cxx_check
#define ae2f_c_check && !ae2f_is_cxx

/// @brief
/// Putting it after one condition in #if will find if the script's language considered as [C++], while doxygen does not notice.
/// 
/// For alter, see @ref ae2f_c_check
#define ae2f_cxx_check && ae2f_is_cxx