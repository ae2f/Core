#if !defined(ae2f_Macro_BitVector_h)
#define ae2f_Macro_BitVector_h

#include "Cast.h"
#include "Compare.h"

#define _ae2f_Macro_BitVector_Filled(len, vec_t) ae2f_static_cast(vec_t, (sizeof(vec_t) << 3) == (len) ? ae2f_static_cast(vec_t, -1) : (ae2f_static_cast(vec_t, ae2f_static_cast(vec_t, 1) << (len)) - 1))
#define ae2f_Macro_BitVector_Filled(len) _ae2f_Macro_BitVector_Filled(len, size_t)

#define _ae2f_Macro_BitVector_GetRanged(vector, start, end) (((vector) >> (start)) & ae2f_Macro_BitVector_Filled((end) - (start)))
#define ae2f_Macro_BitVector_GetRanged(vector, start, end) _ae2f_Macro_BitVector_GetRanged(vector, ae2f_Macro_Compare_TakeSmaller(start, end), ae2f_Macro_Compare_TakeBigger(start, end))
#define ae2f_Macro_BitVector_Get(vector, idx) ae2f_Macro_BitVector_GetRanged(vector, idx, idx + 1)

#define _ae2f_Macro_BitVector_SetRanged(vector, start, end, val) ((vector) & (~((ae2f_Macro_BitVector_Filled((end) - (start))) << start)) | ((val) << start))
#define ae2f_Macro_BitVector_SetRanged(vector, start, end, val) _ae2f_Macro_BitVector_SetRanged(vector, ae2f_Macro_Compare_TakeSmaller(start, end), ae2f_Macro_Compare_TakeBigger(start, end), (val) & ae2f_Macro_BitVector_Filled(ae2f_Macro_Compare_Diff(start, end)))
#define ae2f_Macro_BitVector_Set(vector, idx, val) ae2f_Macro_BitVector_SetRanged(vector, idx, idx + 1, val)

#endif // !defined(ae2f_Macro_BitVector_h)

#if !defined(ae2f_Macro_BitVector_hpp) && defined(__cplusplus)

#include <type_traits>

namespace ae2f {
	namespace Macro {
		template<typename t>
		struct rBitVector {
			using idx_t = unsigned char;

			t obj;
			constexpr rBitVector(const t& obj) noexcept : obj(obj)  {
				static_assert(std::__is_integer<t>::__value, "t is not integer");
			}
			constexpr rBitVector(const t&& obj) noexcept : obj(obj) {
				static_assert(std::__is_integer<t>::__value, "t is not integer");
			}

			template<typename T = t>
			constexpr rBitVector(const rBitVector<T>& vec) noexcept : obj(vec.obj)  {
				static_assert(std::__is_integer<t>::__value, "t is not integer");
				static_assert(std::__is_integer<T>::__value, "T is not integer");
			}

			template<typename T = t>
			constexpr rBitVector(const rBitVector<T>&& vec) noexcept : obj(vec.obj)  {
				static_assert(std::__is_integer<t>::__value, "t is not integer");
				static_assert(std::__is_integer<T>::__value, "T is not integer");
			}

			constexpr static rBitVector<t> Filled(idx_t length) noexcept {
				return rBitVector(_ae2f_Macro_BitVector_Filled(length, t));
			}

			constexpr bool Get(idx_t i) const noexcept {
				return ae2f_Macro_BitVector_Get(obj, i);
			}

			constexpr rBitVector<t> Get(idx_t start, idx_t end) const noexcept {
				return ae2f_Macro_BitVector_GetRanged(this->obj, start, end);
			}
			constexpr rBitVector<t>& Set(idx_t i, bool val) noexcept {
				obj = ae2f_Macro_BitVector_Set(this->obj, i, val);
				return *this;
			}

			constexpr rBitVector<t> Set(idx_t i, bool val) const noexcept {
				return ae2f_Macro_BitVector_Set(this->obj, i, val);
			}
			constexpr rBitVector<t> Set(idx_t start, idx_t end, rBitVector<t> val) const noexcept {
				return ae2f_Macro_BitVector_SetRanged(this->obj, start, end, val.obj);
			}
			constexpr rBitVector<t>& Set(idx_t start, idx_t end, rBitVector<t> val) noexcept {
				this->obj = const_cast<const rBitVector<t>*>(this)->Set(start, end, val);
				return *this;
			}

			constexpr const idx_t Size(const t V) noexcept {
				for (idx_t i = (sizeof(t) << 3); i; i--)
					if (Get(i - 1)) return i;
				return 0;
			}
		};
	}
}

#endif // !defined(ae2f_Macro_BitVector_hpp) && defined(__cplusplus)
