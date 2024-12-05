#include "./BitVec.h"

#if !defined(ae2f_BitVector_hpp)
#define ae2f_BitVector_hpp
#include <type_traits>

namespace ae2f {
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

		consteval rBitVec(const t& obj) noexcept : obj(obj)  {
			
			static_assert(std::is_integral<t>::value, "t is not integer");
		}
		consteval rBitVec(const t&& obj) noexcept : obj(obj) {
			static_assert(std::is_integral<t>::value, "t is not integer");
		}

		template<typename T = t>
		consteval rBitVec(const rBitVec<T>& vec) noexcept : obj(vec.obj)  {
			static_assert(std::is_integral<t>::value, "t is not integer");
			static_assert(std::is_integral<T>::value, "T is not integer");
		}

		template<typename T = t>
		consteval rBitVec(const rBitVec<T>&& vec) noexcept : obj(vec.obj)  {
			static_assert(std::is_integral<t>::value, "t is not integer");
			static_assert(std::is_integral<T>::value, "T is not integer");
		}

		consteval static rBitVec<t> Filled(idx_t length) noexcept {
			return rBitVec(_ae2f_BitVecFilled(length, t));
		}

		consteval bool Get(idx_t i) const noexcept {
			return ae2f_BitVecGet(obj, i);
		}

		consteval rBitVec<t> Get(idx_t start, idx_t end) const noexcept {
			return ae2f_BitVecGetRanged(this->obj, start, end);
		}
		consteval rBitVec<t>& Set(idx_t i, bool val) noexcept {
			obj = ae2f_BitVecSet(this->obj, i, val);
			return *this;
		}

		consteval rBitVec<t> Set(idx_t i, bool val) const noexcept {
			return ae2f_BitVecSet(this->obj, i, val);
		}
		consteval rBitVec<t> Set(idx_t start, idx_t end, rBitVec<t> val) const noexcept {
			return ae2f_BitVecSetRanged(this->obj, start, end, val.obj);
		}
		consteval rBitVec<t>& Set(idx_t start, idx_t end, rBitVec<t> val) noexcept {
			this->obj = const_cast<const rBitVec<t>*>(this)->Set(start, end, val);
			return *this;
		}

		consteval const idx_t Size(const t V) noexcept {
			for (idx_t i = (sizeof(t) << 3); i; i--)
				if (Get(i - 1)) return i;
			return 0;
		}
	};
}

#endif // !defined(ae2f_Macro_BitVector_hpp) && defined(__cplusplus)
