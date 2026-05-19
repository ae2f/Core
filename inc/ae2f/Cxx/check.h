#ifndef	ae2f_cxx_check_h
#define	ae2f_cxx_check_h

#include "./is_cxx.h"

/**
 @brief
 Putting it after one condition in #if will find if the script's language considered as [C], while doxygen does not notice.
 
 For alter, see @ref ae2f_cxx_check
 */

#ifndef	ae2f_c_check
#	define ae2f_c_check && !ae2f_is_cxx
#endif

/**
 @brief
 Putting it after one condition in #if will find if the script's language considered as [C++], while doxygen does not notice.
 
 For alter, see @ref ae2f_c_check
 */

#ifndef	ae2f_cxx_check
#	define ae2f_cxx_check && ae2f_is_cxx
#endif

#endif
