#define ae2f_Macro_Cast_Merge(...) __VA_ARGS__
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
#include <type_traits>
#define ae2f_static_cast(t, v) (static_cast<t>(v))
#define ae2f_dynamic_cast(t, v) (dynamic_cast<t>(v))
#define ae2f_reinterpret_cast(t, v) (reinterpret_cast<t>(v))
#define ae2f_const_cast(t, v) (const_cast<t>(v))
#define ae2f_struct
#define ae2f_extern extern "C"
#define ae2f_var extern "C"
#define ae2f_class class
#define ae2f_add_when_cxx(...) __VA_ARGS__
#define ae2f_add_when_c(...)
#else
#define ae2f_static_cast(t, v) ((t)(v))
#define ae2f_dynamic_cast ae2f_static_cast
#define ae2f_reinterpret_cast ae2f_static_cast
#define ae2f_const_cast ae2f_static_cast
#define ae2f_struct struct
#define ae2f_extern extern 
#define ae2f_class struct
#define ae2f_var 
#define ae2f_add_when_cxx(...)
#define ae2f_add_when_c(...) __VA_ARGS__
#endif // defined(__cplusplus)
#define ae2f_interface struct
#define ae2f_union_cast(tThen, tNow, v) (((union { tThen a; tNow b; }) { v }).b)