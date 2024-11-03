#if !defined(ae2f_Macro_BitVector_h)
#define ae2f_Macro_BitVector_h

#include "Cast.h"
#include "Compare.h"

/// @brief Generates the vector filled in `1`.
/// @param len The length of the filled vector.
/// @tparam vec_t The type of the bit vector.
#define _ae2f_Macro_BitVec_Filled(len, vec_t) ae2f_static_cast(vec_t, (sizeof(vec_t) << 3) == (len) ? ae2f_static_cast(vec_t, -1) : (ae2f_static_cast(vec_t, ae2f_static_cast(vec_t, 1) << (len)) - 1))

/// @brief Generates the vector filled in `1`.
/// @param len The length of the filled vector.
#define ae2f_Macro_BitVec_Filled(len) _ae2f_Macro_BitVec_Filled(len, size_t)

/// @brief
#define _ae2f_Macro_BitVec_GetRanged(vector, start, end, vec_t) (((vector) >> (start)) & _ae2f_Macro_BitVec_Filled((end) - (start), vec_t))
#define ae2f_Macro_BitVec_GetRanged(vector, start, end) _ae2f_Macro_BitVec_GetRanged(vector, ae2f_Macro_Compare_TakeSmaller(start, end), ae2f_Macro_Compare_TakeBigger(start, end), size_t)
#define ae2f_Macro_BitVec_Get(vector, idx) ae2f_Macro_BitVec_GetRanged(vector, idx, (idx) + 1)

#define _ae2f_Macro_BitVec_SetRanged(vector, start, end, val, vec_t) ((vector) & (~((_ae2f_Macro_BitVec_Filled((end) - (start), vec_t)) << start)) | ((val) << start))
#define ae2f_Macro_BitVec_SetRanged(vector, start, end, val) _ae2f_Macro_BitVec_SetRanged(vector, ae2f_Macro_Compare_TakeSmaller(start, end), ae2f_Macro_Compare_TakeBigger(start, end), (val) & ae2f_Macro_BitVec_Filled(ae2f_Macro_Compare_Diff(start, end)), size_t)
#define ae2f_Macro_BitVec_Set(vector, idx, val) ae2f_Macro_BitVec_SetRanged(vector, idx, (idx) + 1, val)

#endif // !defined(ae2f_Macro_BitVector_h)