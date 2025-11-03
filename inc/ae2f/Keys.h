/** 
 * @file	Keys.h 
 * @brief 	Non-casting keywords migrated from Cast.h
 * */
#ifndef ae2f_Keys_h
#define ae2f_Keys_h

#include "./Cxx.h"


/**
 @brief
 In C, keyword 'struct' must be written in front of the structure's name in
 order to use as a type name. \n In C++ that keyword is not required.

 This keyword resolves the difference of the rules of two.
 */
#define ae2f_struct ae2f_WhenC(struct)

/**
 @brief
 Suggests the existence of external variable or function, in naming of C.
 [non-mangling]
 */
#define ae2f_extern ae2f_WhenC(extern) ae2f_WhenCXX(extern "C")

/** @brief Class */
#define ae2f_class ae2f_WhenC(struct) ae2f_WhenCXX(class)

/** @brief Makes the global variable in naming of C. [non-mangling] */
#define ae2f_var ae2f_WhenCXX(extern "C")

/** @brief Function definitions */
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
#undef	ae2f_noexcept
#define ae2f_noexcept
#elif __cplusplus
#define ae2f_noexcept noexcept
#endif


#undef	ae2f_restrict /** First declaration */
#if ae2f_stdc_v < 199901L
#define ae2f_restrict
#else
#define ae2f_restrict restrict
#endif /* C>=99 */

#if __cplusplus
#define ae2f_restrict
#endif /* C++ */



#endif
