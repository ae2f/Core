/**
 * @file CasterUnion.hpp
 * @author ae2f
 * @brief 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "../Cxx.h"

#if !defined(ae2f_Cast_CasterUnion_hpp) ae2f_cxx_check
#define ae2f_Cast_CasterUnion_hpp

/// @brief 
/// C++ union definition for @ref ae2f_union_cast
/// @tparam t 
/// @tparam k 
/// @see
/// @ref ae2f_union_cast
template<typename t, typename k>
union ae2f_UnionCaster {
	t a;
	k b;
	constexpr ae2f_UnionCaster(t _) : b{0} { this->a = _; }
	constexpr k _b() const { return b; }
};

#endif
