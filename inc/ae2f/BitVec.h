/**
 * @file BitVec.h
 * @author ae2f
 * @brief
 * @date 2025-02-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#if !defined(ae2f_BitVec_h)
#define ae2f_BitVec_h

#include "./Cast.h"
#include "./Cmp.h"
#include <stdint.h>

/** @brief
 * Calculate proper byte size with bit count
 * */
#define ae2f_BitToByteCount(bitc) (((bitc) >> 3) + !!((bitc) & 7))

/// @brief
/// The pre-defined index type for Bit vector.
typedef uint8_t ae2f_BitVecI_t;

/// @brief Generates the vector filled in `1`.
/// @param len The length of the filled vector.
/// @tparam vec_t The integer data type.
#define _ae2f_BitVecFilled(len, vec_t)                                         \
  ae2f_static_cast(                                                            \
      vec_t,                                                                   \
      (sizeof(vec_t) << 3) == (len)                                            \
          ? ae2f_static_cast(vec_t, -1)                                        \
          : (ae2f_static_cast(vec_t, ae2f_static_cast(vec_t, 1) << (len)) -    \
             1))

/// @brief Generates the vector filled in `1`.
/// @param len {ae2f_Macro_BitVecI_t} The length of the filled vector.
#define ae2f_BitVecFilled(len) _ae2f_BitVecFilled(len, size_t)

/// @brief
/// Gets the bits of [vector] between index of [start] and [end].
/// @param vector {vec_t} The target for operation.
/// @param start {ae2f_Macro_BitVecI_t} The starting index.
/// @param end {ae2f_Macro_BitVecI_t} The ending index.
/// @tparam vec_t The integer data type.
/// @warning
/// [start] greater than [end] may cause undefined behaviour.
#define _ae2f_BitVecGetRanged(vector, start, end, vec_t)                       \
  (((vector) >> (start)) & _ae2f_BitVecFilled((end) - (start), vec_t))

/// @brief
/// Gets the bits of [vector] between index of [start] and [end]. \n
/// It will normalise the values of [start] and [end] by switching them.
/// @param vector {size_t} The target for operation.
/// @param start {ae2f_Macro_BitVecI_t} The starting index.
/// @param end {ae2f_Macro_BitVecI_t} The ending index.
/// @see _ae2f_Macro_BitVec_GetRanged
#define ae2f_BitVecGetRanged(vector, start, end)                               \
  _ae2f_BitVecGetRanged(vector, ae2f_CmpGetLs(start, end),                     \
                        ae2f_CmpGetGt(start, end), size_t)

/// @brief
/// Gets a bit of [vector] from index of [idx].
/// @param vector {size_t} The target for operation.
/// @param idx {ae2f_Macro_BitVecI_t} The wanted index for searching.
/// @see ae2f_Macro_BitVec_GetRanged
#define ae2f_BitVecGet(vector, idx) ae2f_BitVecGetRanged(vector, idx, (idx) + 1)

/// @brief
/// Sets the bits of [vector] from index of [start] and [end] by [val].
/// @param vector {vec_t} The target for operation.
/// @param start {ae2f_Macro_BitVecI_t} The starting index.
/// @param end {ae2f_Macro_BitVecI_t} The ending index.
/// @param val {vec_t} The value to set.
/// @tparam vec_t The integer data type.
/// @warning
/// [start] greater than [end] may cause undefined behaviour.
#define _ae2f_BitVecSetRanged(vector, start, end, val, vec_t)                  \
  ((vector) & (~((_ae2f_BitVecFilled((end) - (start), vec_t)) << start)) |     \
   ((val) << start))

/// @brief
/// Sets the bits of [vector] from index of [start] and [end] by [val]. \n
/// It will normalise the values of [start] and [end] by switching them.
/// @param vector {vec_t} The target for operation.
/// @param start {ae2f_Macro_BitVecI_t} The starting index.
/// @param end {ae2f_Macro_BitVecI_t} The ending index.
/// @param val {size_t} The value to set.
#define ae2f_BitVecSetRanged(vector, start, end, val)                          \
  _ae2f_BitVecSetRanged(                                                       \
      vector, ae2f_CmpGetLs(start, end), ae2f_CmpGetGt(start, end),            \
      (val) & ae2f_BitVecFilled(ae2f_CmpDiff(start, end)), size_t)

/// @brief
/// Sets a bit of [vector] from index of [idx] by [val].
/// @param vector {size_t} The target for operation.
/// @param idx {bool} The wanted index for searching.
/// @see ae2f_Macro_BitVec_GetRanged
#define ae2f_BitVecSet(vector, idx, val)                                       \
  ae2f_BitVecSetRanged(vector, idx, (idx) + 1, val)

/// @brief
/// Gets the `vec`'s last index where the flag set to 1.
/// @tparam t Must be an integer type
/// @param vec {t}
#define ae2f_BitVecSizeDefName(t) ae2f_BitVecSize_##t##_func

/// @brief
/// Gets the `vec`'s last index where the flag set to 1.
/// @tparam t Must be an integer type
/// @param vec {t}
#define ae2f_BitVecSizeDef(t)                                                  \
  constextendedfun uint8_t ae2f_BitVecSizeDefName(t)(t vec) noexcept {         \
    uint8_t i;                                                                 \
    for (i = (sizeof(t) << 3); i; i--)                                         \
      if (ae2f_BitVecGet(vec, i - 1))                                          \
        break;                                                                 \
    return i == (sizeof(t) << 3) ? 0 : i;                                      \
  }

/// @brief
/// Gets the vector that `vec`'s first flag set to 1.
/// @tparam t Must be an integer type
/// @param vec {t}
#define ae2f_BitVecFndOneDefName(t) ae2f_BitVecFndOne_##t##_func

/// @brief
/// Gets the vector that `vec`'s first flag set to 1.
/// @tparam t Must be an integer type
/// @param vec {t}
#define ae2f_BitVecFndOneDef(t)                                                \
  constextendedfun t ae2f_BitVecFndOneDefName(t)(const t vec) noexcept {       \
    t i = 1;                                                                   \
    for (; i; i <<= 1) {                                                       \
      if (vec & i)                                                             \
        break;                                                                 \
    }                                                                          \
    return i;                                                                  \
  }

#endif // !defined(ae2f_Macro_BitVector_h)
