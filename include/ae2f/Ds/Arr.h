#if !defined(ae2f_ds_Arr_h)
#define ae2f_ds_Arr_h
#include "Alloc.h"


typedef int ae2f_ds_Arr_Compared_t;

/// @returns
///	Negative: l < r
/// 
///	0: l == r
/// 
///	Positive: l > r
typedef ae2f_ds_Arr_Compared_t(*ae2f_ds_Arr_fpElCmp_t)(const void* l, const void* r);

/// they are same
#define ae2f_ds_Arr_EQUAL		ae2f_static_cast(ae2f_ds_Arr_Compared_t, 0)

// right is lesser
#define ae2f_ds_Arr_RIGHT_UNIT	ae2f_static_cast(ae2f_ds_Arr_Compared_t, 1)

// left is lesser
#define ae2f_ds_Arr_LEFT_UNIT	ae2f_static_cast(ae2f_ds_Arr_Compared_t, -1)

/// @brief 
/// Finds the element [wanted] via binary search.
/// @param arr 
/// Array to see.
/// It must be sorted.
/// @param wanted 
/// The element which is wanted
/// @param elsize 
/// Suggested element size
/// @param fpElCmp 
/// Comparing function.
/// comparing will be proceed as: `fpElCmp`(`element`, `wanted`);
/// @param out 
/// Buffer where the Index may be stored
/// @return 
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Arr_BSearch_imp(
	const ae2f_struct ae2f_ds_cAlloc* arr,
	const void* wanted,
	size_t elsize,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp,
	size_t* out
);

/// @brief 
/// Finds the element [wanted] via binary search.
/// @param arr 
/// Array to see.
/// It must be sorted.
/// @param wanted 
/// The element which is wanted
/// @param elsize 
/// Suggested element size
/// @param fpElCmp 
/// Comparing function.
/// comparing will be proceed as: `fpElCmp`(`element`, `wanted`);
/// @param out 
/// Buffer where the Index may be stored
/// @return 
#define ae2f_ds_Arr_BSearch(arr, wanted, elsize, fpElCmp) ae2f_ds_Arr_BSearch_imp(ae2f_reinterpret_cast(const ae2f_struct ae2f_ds_Alloc_Refer*, arr), wanted, elsize, ae2f_reinterpret_cast(const ae2f_ds_Arr_fpElCmp_t, fpElCmp))

/// @brief
/// Failed to find the wanted value.
/// 
/// Your array might have not been sorted finely.
/// @return
/// (ae2f_errGlob_NFOUND | ae2f_errGlob_DONE_HOWEV)
#define ae2f_ds_Arr_BSearch_NOT_FOUND ae2f_static_cast(ae2f_errint_t, 0b1100000)

/// @brief 
/// Order the arr via quick sort.
/// @param arr 
/// An array to sort
/// @param elsize 
/// Size suggestion for each element
/// @param fpElCmp 
/// Comparing function:
/// comparing will process as: `fpElCmp`(`element`, `target`);
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Arr_QSort_imp(
	ae2f_struct ae2f_ds_cAlloc* arr,
	size_t elsize,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp
);

#define ae2f_ds_Arr_QSort(arr, elsize, fpElCmp) ae2f_ds_Arr_QSort_imp(ae2f_reinterpret_cast(ae2f_struct ae2f_ds_Alloc_cRef*, arr), elsize, ae2f_reinterpret_cast(const ae2f_ds_Arr_fpElCmp_t, fpElCmp))

#endif // !defined(ae2f_DataStructure_Array_h)
