/** 
 * @file	Keys.h 
 * @brief 	Non-casting keywords migrated from Cast.h
 * */
#ifndef ae2f_Keys_h
#define ae2f_Keys_h

#include "./Cxx.h"
#include "./cc.h"

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

/** @brief Invokes when condition is `false`. */
#define unless(a) if (!(a))

#define ae2f_tmpldef(a) template<a>
#define ae2f_tmpluse(a) <a>

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

#endif
