/**
 * @file Cmp.h
 * @author ae2f
 * @brief 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ae2f_Cmp_h 
#define ae2f_Cmp_h


typedef int
/// @brief 
/// A predefined returning data type for @ref ae2f_fpCmp_t.
/// @see ae2f_CmpFunRet_EQUAL
/// @see ae2f_CmpFunRet_RISLESSER
/// @see ae2f_CmpFunRet_LISLESSER
ae2f_CmpFunRet_t,

	/// @brief
	/// It is an api for following approximate pseudo code.
	/// ```c
	/// const void *l, *r;
	/// return *l - *r;
	/// ```
	/// @see ae2f_CmpFunRet_t
	(*ae2f_fpCmp_t)(const void* l, const void* r);

	/// @brief they are same
	/// @see ae2f_CmpFunRet_t 
#define ae2f_CmpFunRet_EQUAL		0

	/// @brief right is lesser
	/// @see ae2f_CmpFunRet_t
#define ae2f_CmpFunRet_RISLESSER	1

	/// @brief left is lesser
	/// @see ae2f_CmpFunRet_t
#define ae2f_CmpFunRet_LISLESSER	-1


/// @warning
/// Two parameters must be comparable with operator.
/// @return
/// One bigger.
#define ae2f_CmpGetGt(a, b)		((a) > (b) ? (a) : (b))

/// @warning
/// Two parameters must be comparable with operator.
/// @return
/// One smaller.
#define ae2f_CmpGetLs(a, b)	((a) < (b) ? (a) : (b))

/// @return
/// The absolute different of two.
#define ae2f_CmpDiff(a, b)			(ae2f_CmpGetGt(a, b) - ae2f_CmpGetLs(a, b))

/// @brief
/// Gets the member from the pointer.
/// Given nullptr, the return will be alter.
/// @param ptr The pointer for getting member.
/// @param member The valid member's name. [from the structure]
/// @param alter The alternative value when given nullptr.
#define ae2f_CmpGetMem(ptr, member, alter) ((ptr) ? ((ptr)->member) : (alter))

/// @brief
/// Returns ptr's self.
/// Given nullptr, the return will be alt.
/// @param ptr Self Referring
/// @param alt The alternative value.
#define ae2f_CmpGetSelf(ptr, alt) ((ptr) ? (ptr) : (alt))
#endif // !defined(ae2f_Macro_Compare_h)
