#if !defined(ae2f_Macro_Cast_h)

/// @brief
/// asdf
#define ae2f_Macro_Cast_h

/// @brief
/// ANSI Code for clearing the console.
/// Clearing all display, moving the cursor on the top.
#define ae2f_Macro_Cast_Console_Clear_Cheat "\033[2J\033[H"

/// @brief
/// simply merge all text inside the round bracket, counting them as a single text block.
#define ae2f_Macro_Cast_Merge(...) __VA_ARGS__

#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)

#include "Cast/CasterUnion.hpp"

/// @brief
/// Appears when the current language is C++.
#define ae2f_add_when_cxx(...) __VA_ARGS__

/// @brief
/// Appears when the current language is C.
#define ae2f_add_when_c(...)

#else

/// @brief
/// Appears when the current language is C++.
#define ae2f_add_when_cxx(...)

/// @brief
/// Appears when the current language is C.
#define ae2f_add_when_c(...) __VA_ARGS__

#endif // defined(__cplusplus)

/// @brief
/// Initialiser for trivial structures / classes.
#define ae2f_record_make(type, ...) (ae2f_add_when_c((type) { __VA_ARGS__ }) ae2f_add_when_cxx(type{ __VA_ARGS__ }))

/// @brief
/// # static_cast
#define ae2f_static_cast(t, v) ae2f_add_when_c((t)(v)) ae2f_add_when_cxx(static_cast<t>(v))

/// @brief
/// # dynamic_cast
#define ae2f_dynamic_cast(t, v) ae2f_add_when_c((t)(v)) ae2f_add_when_cxx(dynamic_cast<t>(v))

/// @brief
/// # reinterpret_cast
#define ae2f_reinterpret_cast(t, v) ae2f_add_when_c((t)(v)) ae2f_add_when_cxx(reinterpret_cast<t>(v))

/// @brief
/// # const_cast
#define ae2f_const_cast(t, v) ae2f_add_when_c((t)(v)) ae2f_add_when_cxx(const_cast<t>(v))

/// @brief
/// Makes a union that reads a memory in two methods. \n
/// `tThen` -> `tNow`
/// @tparam tThen
/// The existing data's type as input.
/// 
/// @tparam tNow
/// Wanted output datatype for casting.
///
/// @param v
/// Input value
#define ae2f_union_cast(tThen, tNow, v) ae2f_add_when_c((union { tThen a; tNow b; }) { v }) ae2f_add_when_cxx(ae2f_union_caster<tThen, tNow>{ v }) .b

/// @brief
/// In C, keyword 'struct' must be written in front of the structure's name in order to use as a type name. \n
/// In C++ that keyword is not required.
/// 
/// This keyword resolves the difference of the rules of two.
#define ae2f_struct ae2f_add_when_c(struct)

/// @brief
/// Suggests the existence of external variable or function, in naming of C. [non-mangling]
#define ae2f_extern ae2f_add_when_c(extern) ae2f_add_when_cxx(extern "C")

/// @brief
/// Class 
#define ae2f_class ae2f_add_when_c(struct) ae2f_add_when_cxx(class)

/// @brief
/// Makes the global variable in naming of C. [non-mangling]
#define ae2f_var ae2f_add_when_cxx(extern "C")

/// @brief
/// Function definitions
#define ae2f_fdef(rtn_t, name, ...) rtn_t (*name)(__VA_ARGS__)

#endif