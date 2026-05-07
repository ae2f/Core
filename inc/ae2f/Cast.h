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

#include <ae2f/.LangVer.h>
#include "./Cxx/When.h"
#include "./Guide.h"

/** 
 * @def ae2f_RecordMk
 * @brief Initialiser for trivial structures / classes. 
 * */
#define ae2f_RecordMk(type, v)                                               \
  (ae2f_WhenC((type){v}) ae2f_WhenCXX(type{v}))

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

#endif
