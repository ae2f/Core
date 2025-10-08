/**
 * @file BitVec.hpp
 * @author ae2f
 * @brief 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#if !defined(ae2f_BitVector_hpp)
#define ae2f_BitVector_hpp

#include "./LangVer.h"

#if  __ae2f_stdcheck_CC(201103L)
#include <type_traits> 

#include "./BitVec.h"
#include "Pack/Beg.h"
 
namespace ae2f {
	
	/** @brief
	 * @tparam t 
	 * Is the class binding for BitVec.h
	 **/
	 template<typename t>
	 class rBitVec {
		 static ae2f_BitVecSizeDef(t);
		 static ae2f_BitVecFndOneDef(t);
		 
		 public:
		 using idx_t = ae2f_BitVecI_t;
 
		 /// @brief 
		 /// The actual integer.
		 t obj;
 
		 ae2f_constexprmethod rBitVec(const t& obj) noexcept : obj(obj)  {
			 
			 static_assert(std::is_integral<t>::value, "t is not integer");
		 }
		 ae2f_constexprmethod rBitVec(const t&& obj) noexcept : obj(obj) {
			 static_assert(std::is_integral<t>::value, "t is not integer");
		 }
 
		 template<typename T = t>
		 ae2f_constexprmethod rBitVec(const rBitVec<T>& vec) noexcept : obj(vec.obj)  {
			 static_assert(std::is_integral<t>::value, "t is not integer");
			 static_assert(std::is_integral<T>::value, "T is not integer");
		 }
 
		 template<typename T = t>
		 ae2f_constexprmethod rBitVec(const rBitVec<T>&& vec) noexcept : obj(vec.obj)  {
			 static_assert(std::is_integral<t>::value, "t is not integer");
			 static_assert(std::is_integral<T>::value, "T is not integer");
		 }
 
		 ae2f_constexprmethod static rBitVec<t> Filled(idx_t length) noexcept {
			 return rBitVec(_ae2f_BitVecFilled(length, t));
		 }
 
		 ae2f_constexprmethod bool Get(idx_t i) const noexcept {
			 return ae2f_BitVecGet(obj, i);
		 }
 
		 ae2f_constexprmethod rBitVec<t> GetRangedConst(idx_t start, idx_t end) const noexcept {
			 return ae2f_BitVecGetRanged(this->obj, start, end);
		 }
		 ae2f_constexprmethod rBitVec<t>& Set(idx_t i, bool val) noexcept {
			 obj = ae2f_BitVecSet(this->obj, i, val);
			 return *this;
		 }
 
		 ae2f_constexprmethod rBitVec<t> SetConst(idx_t i, bool val) const noexcept {
			 return ae2f_BitVecSet(this->obj, i, val);
		 }
		 ae2f_constexprmethod rBitVec<t> SetRangedConst(idx_t start, idx_t end, rBitVec<t> val) const noexcept {
			 return ae2f_BitVecSetRanged(this->obj, start, end, val.obj);
		 }
		 ae2f_constexprmethod rBitVec<t>& SetRanged(idx_t start, idx_t end, rBitVec<t> val) noexcept {
			 this->obj = const_cast<const rBitVec<t>*>(this)->SetRangedConst(start, end, val).obj;
			 return *this;
		 }
 
		 ae2f_constexprmethod const idx_t Size() const noexcept {
			 return ae2f_BitVecSizeDefName(t)(this->obj);
		 }
 
		 constextendedmethod const rBitVec<t> FndOne() const noexcept {
			 return ae2f_BitVecFndOneDefName(t)(this->obj);
		 }
	 };
 }
 
#include "Pack/End.h"
#else
#include "./BitVec.h"
#endif

#endif // !defined(ae2f_Macro_BitVector_hpp) && defined(__cplusplus)
 
