/**
 * @file BitVec.hpp
 * @author ae2f
 * @brief 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "./BitVec.h"

 #if !defined(ae2f_BitVector_hpp)
 #define ae2f_BitVector_hpp
 #include <type_traits>
 
 #include "Pack/Beg.h"
 
 namespace ae2f {
	 /// @brief 
	 /// 
	 /// @tparam t 
	 /// Is the class binding for BitVec.h
	 template<typename t>
	 class rBitVec {
		 static ae2f_BitVecSizeDef(t);
		 static ae2f_BitVecFndOneDef(t);
		 
		 public:
		 using idx_t = ae2f_BitVecI_t;
 
		 /// @brief 
		 /// The actual integer.
		 t obj;
 
		 constexprmethod rBitVec(const t& obj) noexcept : obj(obj)  {
			 
			 static_assert(std::is_integral<t>::value, "t is not integer");
		 }
		 constexprmethod rBitVec(const t&& obj) noexcept : obj(obj) {
			 static_assert(std::is_integral<t>::value, "t is not integer");
		 }
 
		 template<typename T = t>
		 constexprmethod rBitVec(const rBitVec<T>& vec) noexcept : obj(vec.obj)  {
			 static_assert(std::is_integral<t>::value, "t is not integer");
			 static_assert(std::is_integral<T>::value, "T is not integer");
		 }
 
		 template<typename T = t>
		 constexprmethod rBitVec(const rBitVec<T>&& vec) noexcept : obj(vec.obj)  {
			 static_assert(std::is_integral<t>::value, "t is not integer");
			 static_assert(std::is_integral<T>::value, "T is not integer");
		 }
 
		 constexprmethod static rBitVec<t> Filled(idx_t length) noexcept {
			 return rBitVec(_ae2f_BitVecFilled(length, t));
		 }
 
		 constexprmethod bool Get(idx_t i) const noexcept {
			 return ae2f_BitVecGet(obj, i);
		 }
 
		 constexprmethod rBitVec<t> GetRangedConst(idx_t start, idx_t end) const noexcept {
			 return ae2f_BitVecGetRanged(this->obj, start, end);
		 }
		 constexprmethod rBitVec<t>& Set(idx_t i, bool val) noexcept {
			 obj = ae2f_BitVecSet(this->obj, i, val);
			 return *this;
		 }
 
		 constexprmethod rBitVec<t> SetConst(idx_t i, bool val) const noexcept {
			 return ae2f_BitVecSet(this->obj, i, val);
		 }
		 constexprmethod rBitVec<t> SetRangedConst(idx_t start, idx_t end, rBitVec<t> val) const noexcept {
			 return ae2f_BitVecSetRanged(this->obj, start, end, val.obj);
		 }
		 constexprmethod rBitVec<t>& SetRanged(idx_t start, idx_t end, rBitVec<t> val) noexcept {
			 this->obj = const_cast<const rBitVec<t>*>(this)->SetRangedConst(start, end, val).obj;
			 return *this;
		 }
 
		 constexprmethod const idx_t Size() const noexcept {
			 return ae2f_BitVecSizeDefName(t)(this->obj);
		 }
 
		 constexprmethod const rBitVec<t> FndOne() const noexcept {
			 return ae2f_BitVecFndOneDefName(t)(this->obj);
		 }
	 };
 }
 
 #include "Pack/End.h"
 
 #endif // !defined(ae2f_Macro_BitVector_hpp) && defined(__cplusplus)
 