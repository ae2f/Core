#if !defined(ae2f_Macro_Cast_CasterUnion_hpp)
#define ae2f_Macro_Cast_CasterUnion_hpp

/// @brief 
/// C++ union definition for @ref ae2f_union_cast
/// @tparam t 
/// @tparam k 
/// @see
/// @ref ae2f_union_cast
template<typename t, typename k>
union ae2f_union_caster {
	t a;
	k b;
};

#endif