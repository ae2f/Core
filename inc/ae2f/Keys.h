/** 
 * @file	Keys.h 
 * @brief 	Non-casting keywords migrated from Cast.h
 * */
#ifndef ae2f_Keys_h
#define ae2f_Keys_h

#include "./Cxx/When.h"
#include "./Cxx/extern.h"
#include "./Cxx/struct.h"
#include "./cc.h"

/** @brief Makes the global variable in naming of C. [non-mangling] */
#define ae2f_var ae2f_WhenCXX(extern "C")

/** @brief Invokes when condition is `false`. */
#define unless(a) ae2fcc_unless((a))

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
