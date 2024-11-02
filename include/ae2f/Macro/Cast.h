#if !defined(ae2f_Macro_Cast_h)

/// @brief
/// asdf
#define ae2f_Macro_Cast_h

/// ANSI Code for clearing the console.
/// Clearing all display, moving the cursor on the top.
#define ae2f_Macro_Cast_Console_Clear_Cheat "\033[2J\033[H"

/// @brief
/// simply merge all text inside the round bracket, counting them as a single text block.
#define ae2f_Macro_Cast_Merge(...) __VA_ARGS__
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)

template<typename t, typename k>
union ae2f_union_caster {
	t a;
	k b;
};

#define ae2f_static_cast(t, v) (static_cast<t>(v))
#define ae2f_dynamic_cast(t, v) (dynamic_cast<t>(v))
#define ae2f_reinterpret_cast(t, v) (reinterpret_cast<t>(v))
#define ae2f_const_cast(t, v) (const_cast<t>(v))
#define ae2f_struct
#define ae2f_extern extern "C"
#define ae2f_var extern "C"
#define ae2f_class class
#define ae2f_record_make(type, ...) (type{ __VA_ARGS__ })

#define ae2f_add_when_cxx(...) __VA_ARGS__
#define ae2f_add_when_c(...)
#define ae2f_union_cast(tThen, tNow, v) (ae2f_union_caster<tThen, tNow>{ v }).b
#else
/// @brief
/// Initialiser for trivial structures / classes.
#define ae2f_record_make(type, ...) ((type) { __VA_ARGS__ })

#define ae2f_static_cast(t, v) ((t)(v))
#define ae2f_dynamic_cast ae2f_static_cast
#define ae2f_reinterpret_cast ae2f_static_cast
#define ae2f_const_cast ae2f_static_cast

/// @brief
/// 
#define ae2f_struct struct
#define ae2f_extern extern 
#define ae2f_class struct

/// @brief
/// Variable 
#define ae2f_var 

/// @brief
/// Appears when the current language is C++.
#define ae2f_add_when_cxx(...)

/// @brief
/// Appears when the current language is C.
#define ae2f_add_when_c(...) __VA_ARGS__

#define ae2f_union_cast(tThen, tNow, v) (((union { tThen a; tNow b; }) { v }).b)
#endif // defined(__cplusplus)
#endif