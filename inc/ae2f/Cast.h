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

#define ae2f_Cast_h

/** 
 * @brief simply merge all text inside the round bracket, 
 * counting them as a single text block. 
 * */
#define ae2f_CastMerge(...) __VA_ARGS__

#include "./Cast/CasterUnion.hpp"
#include "./LangVer.auto.h"
#include "Cxx.h"
#include "./Guide.h"

/** 
 * @def ae2f_RecordMk
 * @brief Initialiser for trivial structures / classes. 
 * */
#define ae2f_RecordMk(type, ...)                                               \
  (ae2f_WhenC((type){__VA_ARGS__}) ae2f_WhenCXX(type{__VA_ARGS__}))

/** @brief static_cast for C++ */
#define ae2f_static_cast(t, v)                                                 \
  ae2f_WhenC(((t)(v))) ae2f_WhenCXX(static_cast<t>(v))

/** @brief dynamic_cast for C++ */
#define ae2f_dynamic_cast(t, v)                                                \
  ae2f_WhenC(((t)(v))) ae2f_WhenCXX(dynamic_cast<t>(v))

/** @brief reinterpret_cast for C++ */
#define ae2f_reinterpret_cast(t, v)                                            \
  ae2f_WhenC(((t)(v))) ae2f_WhenCXX(reinterpret_cast<t>(v))

/** @brief const_cast for C++ */
#define ae2f_const_cast(t, v)                                                  \
  ae2f_WhenC(((t)(v))) ae2f_WhenCXX(const_cast<t>(v))

/**
 @brief
 Makes a union that reads a memory in two methods. \n
 `tThen` -> `tNow`
 @tparam tThen
 The existing data's type as input.

 @tparam tNow
 Wanted output datatype for casting.

 @param v
 Input value
 */
#define ae2f_union_cast(tThen, tNow, v)                                        \
  ae2f_WhenC((union {                                                          \
    tThen a;                                                                   \
    tNow b;                                                                    \
  }){v}) ae2f_WhenCXX(ae2f_UnionCaster<tThen, tNow>(v))                        \
      ._b()
#endif
