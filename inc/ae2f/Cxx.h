/**
 * @file Cxx.h
 * @author ae2f
 * @brief 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ae2f_Cxx_h
#define ae2f_Cxx_h

/**
 * @def ae2f_NONE
 * @brief Literally nothing.
 */
#define ae2f_NONE

#ifdef __cplusplus

/**
 @def ae2f_WhenCXX 
 @brief
 Appears when the current language is C++.
 */
#define ae2f_WhenCXX(a) a

/**
 @brief
 Appears when the current language is C.
 */
#define ae2f_WhenC(a) ae2f_NONE

#else
/**
 @brief
 Appears when the current language is C++.
 */
#define ae2f_WhenC(a) a

/**
 @brief
 Appears when the current language is C.
 */
#define ae2f_WhenCXX(a) ae2f_NONE

#endif
 
#define ae2f_is_cxx ae2f_WhenC(0) ae2f_WhenCXX(1)




/**
 @brief
 Putting it after one condition in #if will find if the script's language considered as [C], while doxygen does not notice.
 
 For alter, see @ref ae2f_cxx_check
 */
#define ae2f_c_check && !ae2f_is_cxx

/**
 @brief
 Putting it after one condition in #if will find if the script's language considered as [C++], while doxygen does not notice.
 
 For alter, see @ref ae2f_c_check
 */
#define ae2f_cxx_check && ae2f_is_cxx

#include "./Cxx/Reg.h"
#include "./Cxx/Constexpr.h"
#include "./Cxx/Nil.h"

#endif
