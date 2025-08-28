/**
 * @file Cast.h
 * @author ae2f
 * @brief
 * @date 2025-02-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#if !defined(ae2f_Cast_h)

/// @brief
/// asdf
#define ae2f_Cast_h

/// @brief
/// ANSI Code for clearing the console.
/// Clearing all display, moving the cursor on the top.
#define ae2f_CastCCls "\033[2J\033[H"

/// @brief
/// simply merge all text inside the round bracket, counting them as a single
/// text block.
#define ae2f_CastMerge(...) __VA_ARGS__

#include "./Cast/CasterUnion.hpp"
#include "./Cast/Constexpr.hpp"
#include "./LangVer.auto.h"
#include "Cxx.h"
#include <stdbool.h>
#include <stddef.h>
#include "./Guide.h"

/// @brief
/// Initialiser for trivial structures / classes.
#define ae2f_RecordMk(type, ...)                                               \
  (ae2f_WhenC((type){__VA_ARGS__}) ae2f_WhenCXX(type{__VA_ARGS__}))

/// @brief
/// # static_cast
#define ae2f_static_cast(t, v)                                                 \
  ae2f_WhenC(((t)(v))) ae2f_WhenCXX(static_cast<t>(v))

/// @brief
/// # dynamic_cast
#define ae2f_dynamic_cast(t, v)                                                \
  ae2f_WhenC(((t)(v))) ae2f_WhenCXX(dynamic_cast<t>(v))

/// @brief
/// # reinterpret_cast
#define ae2f_reinterpret_cast(t, v)                                            \
  ae2f_WhenC(((t)(v))) ae2f_WhenCXX(reinterpret_cast<t>(v))

/// @brief
/// # const_cast
#define ae2f_const_cast(t, v)                                                  \
  ae2f_WhenC(((t)(v))) ae2f_WhenCXX(const_cast<t>(v))

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
#define ae2f_union_cast(tThen, tNow, v)                                        \
  ae2f_WhenC((union {                                                          \
    tThen a;                                                                   \
    tNow b;                                                                    \
  }){v}) ae2f_WhenCXX(ae2f_UnionCaster<tThen, tNow>(v))                        \
      ._b()

/// @brief
/// In C, keyword 'struct' must be written in front of the structure's name in
/// order to use as a type name. \n In C++ that keyword is not required.
///
/// This keyword resolves the difference of the rules of two.
#define ae2f_struct ae2f_WhenC(struct)

/// @brief
/// Suggests the existence of external variable or function, in naming of C.
/// [non-mangling]
#define ae2f_extern ae2f_WhenC(extern) ae2f_WhenCXX(extern "C")

/// @brief
/// Class
#define ae2f_class ae2f_WhenC(struct) ae2f_WhenCXX(class)

/// @brief
/// Makes the global variable in naming of C. [non-mangling]
#define ae2f_var ae2f_WhenCXX(extern "C")

/// @brief
/// Function definitions
#define ae2f_fdef(rtn_t, name, ...) rtn_t (*name)(__VA_ARGS__)

/** @brief Invokes when condition is `false`. */
#define unless(...) if (!(__VA_ARGS__))

#define ae2f_structdef_v(key, name, ...)                                   \
  typedef key name __VA_ARGS__;                                                    \
  key name

#define ae2f_structdef_n(key, name, ...)	ae2f_structdef_v(key, name, name, __VA_ARGS__)
#define ae2f_structdef(key, name)		ae2f_structdef_v(key, name, name)
#define ae2f_enumdef(name, ...)			typedef enum name __VA_ARGS__ name

#define ae2f_tmpldef(...) template<__VA_ARGS__>
#define ae2f_tmpluse(...) <__VA_ARGS__>

/**
 * @brief
 * Make two pair of function as [eval] and [expr]. \n
 * [expr] will just call [eval]. \n
 * You will implement the body of [eval].
 *
 * Following is an use case.
 * @code
 * ae2f_evaldef(
		template<int a>, <0>
		, consteval, constexprfun
		, int, Hello, _Hello, char v, v) 
		{ return v; }
 * */
#define ae2f_evaldef(tmpldef, tmpluse, keyeval, keyexpr, ret_t, nameeval, nameexpr, prmdef, prmuse) \
	tmpldef keyeval ret_t nameeval(prmdef); \
	tmpldef keyexpr ret_t nameexpr(prmdef) { \
		return nameeval tmpluse (prmuse); \
	} \
	tmpldef keyeval ret_t nameeval(prmdef)

#if !__ae2f_stdcheck_CC(201103L)
#undef	noexcept
#define noexcept
#endif


#undef	restrict /** First declaration */
#if ae2f_stdc_v < 199901L
#undef	restrict
#define restrict
#endif // C>=99

#if __cplusplus
#undef	restrict
#define restrict
#endif // C++

#if !__ae2f_stdcheck_CC(201103L)
/// @brief
/// Means that there will be no exception thrown written in code.
#define noexcept
#define constexpr
#endif /* C++<=11 */

#if ae2f_WhenC(!)0
#undef  noexcept
#define noexcept
#endif

#endif
