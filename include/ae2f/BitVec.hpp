#include "./BitVec.h"

#if !defined(ae2f_BitVector_hpp)
#define ae2f_BitVector_hpp
#include <type_traits>

namespace ae2f {
	namespace Macro {
		/// @brief 
		/// 
		/// @tparam t 
		/// Is the class binding for BitVec.h
		template<typename t>
		struct rBitVec {
			using idx_t = ae2f_BitVecI_t;

			/// @brief 
			/// The actual integer.
			t obj;

			constexpr rBitVec(const t& obj) noexcept : obj(obj)  {
				
				static_assert(std::is_integral<t>::value, "t is not integer");
			}
			constexpr rBitVec(const t&& obj) noexcept : obj(obj) {
				static_assert(std::is_integral<t>::value, "t is not integer");
			}

			template<typename T = t>
			constexpr rBitVec(const rBitVec<T>& vec) noexcept : obj(vec.obj)  {
				static_assert(std::is_integral<t>::value, "t is not integer");
				static_assert(std::is_integral<T>::value, "T is not integer");
			}

			template<typename T = t>
			constexpr rBitVec(const rBitVec<T>&& vec) noexcept : obj(vec.obj)  {
				static_assert(std::is_integral<t>::value, "t is not integer");
				static_assert(std::is_integral<T>::value, "T is not integer");
			}

			constexpr static rBitVec<t> Filled(idx_t length) noexcept {
				return rBitVec(_ae2f_BitVec_Filled(length, t));
			}

			constexpr bool Get(idx_t i) const noexcept {
				return ae2f_BitVec_Get(obj, i);
			}

			constexpr rBitVec<t> Get(idx_t start, idx_t end) const noexcept {
				return ae2f_BitVec_GetRanged(this->obj, start, end);
			}
			constexpr rBitVec<t>& Set(idx_t i, bool val) noexcept {
				obj = ae2f_BitVec_Set(this->obj, i, val);
				return *this;
			}

			constexpr rBitVec<t> Set(idx_t i, bool val) const noexcept {
				return ae2f_BitVec_Set(this->obj, i, val);
			}
			constexpr rBitVec<t> Set(idx_t start, idx_t end, rBitVec<t> val) const noexcept {
				return ae2f_BitVec_SetRanged(this->obj, start, end, val.obj);
			}
			constexpr rBitVec<t>& Set(idx_t start, idx_t end, rBitVec<t> val) noexcept {
				this->obj = const_cast<const rBitVec<t>*>(this)->Set(start, end, val);
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
