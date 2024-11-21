#ifndef ae2f_Cmp_Fun_h
#define ae2f_Cmp_Fun_h

/// @brief 
/// A predefined returning data type for @ref ae2f_fpCmp_t.
/// @see ae2f_CmpFunRet_EQUAL
/// @see ae2f_CmpFunRet_RISLESSER
/// @see ae2f_CmpFunRet_LISLESSER
typedef int ae2f_CmpFunRet_t;

/// @brief
/// It is an api for following approximate pseudo code.
/// ```c
/// *l - *r
/// ```
/// @see ae2f_CmpFunRet_t
typedef ae2f_CmpFunRet_t(*ae2f_fpCmp_t)(const void* l, const void* r);

/// @brief they are same
/// @see ae2f_CmpFunRet_t 
#define ae2f_CmpFunRet_EQUAL		0

/// @brief right is lesser
/// @see ae2f_CmpFunRet_t
#define ae2f_CmpFunRet_RISLESSER	1

/// @brief left is lesser
/// @see ae2f_CmpFunRet_t
#define ae2f_CmpFunRet_LISLESSER	-1

#endif