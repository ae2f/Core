/**
 * @file CasterUnion.hpp
 * @author ae2f
 * @brief
 * @date 2025-02-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#if !defined(ae2f_Cast_CasterUnion_hpp) && defined(__cplusplus)
#define ae2f_Cast_CasterUnion_hpp
#include "./Constexpr.hpp"

/// @brief
/// C++ union definition for @ref ae2f_union_cast
/// @tparam t
/// @tparam k
/// @see
/// @ref ae2f_union_cast
template <typename t, typename k> union ae2f_UnionCaster {
  t a;
  k b;
  constexprmethod ae2f_UnionCaster(t _) : a(_) {}
  constexprmethod k _b() const { return b; }
};

#endif
