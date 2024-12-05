#ifndef ae2f_Cast_Constexpr_hpp
#define ae2f_Cast_Constexpr_hpp

#if __cplusplus >= 202002L
/// @brief
/// C++ keyword for constant-time functions.
#define consteval ae2f_WhenC(inline) ae2f_WhenCXX(consteval)
#else
/// @brief
/// C++ keyword for constant-time functions.
#define consteval ae2f_WhenC(inline) ae2f_WhenCXX(constexpr)
#endif

#endif 