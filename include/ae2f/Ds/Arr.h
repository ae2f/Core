#if !defined(ae2f_ds_Arr_h)
#define ae2f_ds_Arr_h
#include "Alloc.h"
#include "Arr/Err.h"

/// @brief 
/// A predefined returning data type for @ref ae2f_ds_Arr_fpElCmp_t.
/// @see ae2f_ds_Arr_EQUAL
/// @see ae2f_ds_Arr_RIGHT_UNIT
/// @see ae2f_ds_Arr_LEFT_UNIT
typedef int ae2f_ds_Arr_CmpRet_t;

/// @brief
/// It is an api for following approximate pseudo code.
/// ```c
/// *l - *r
/// ```
/// @see ae2f_ds_Arr_CmpRet_t
typedef ae2f_ds_Arr_CmpRet_t(*ae2f_ds_Arr_fpElCmp_t)(const void* l, const void* r);

/// @brief they are same
#define ae2f_ds_Arr_EQUAL		ae2f_static_cast(ae2f_ds_Arr_CmpRet_t, 0)

/// @brief right is lesser
#define ae2f_ds_Arr_RIGHT_UNIT	ae2f_static_cast(ae2f_ds_Arr_CmpRet_t, 1)

/// @brief left is lesser
#define ae2f_ds_Arr_LEFT_UNIT	ae2f_static_cast(ae2f_ds_Arr_CmpRet_t, -1)

/// @brief 
/// Finds the element [wanted] via binary search.
/// @param arr 
/// Array to see.
/// It must be sorted.
/// @param wanted 
/// The element which is wanted
/// @param fpElCmp 
/// comparing will be proceed as
/// ```c
/// fpElCmp(element, wanted);
/// ```
/// @param out 
/// Buffer where the Index may be stored
/// @return 
/// @ref ae2f_errGlob_OK \n
/// @ref ae2f_ds_Arr_NOT_FOUND 
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_ALLOC_FAILED \n 
/// @see ae2f_ds_Alloc_cRef_getSize
/// @see ae2f_ds_Alloc_cRef_Read
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Arr_BSearch_imp(
	const ae2f_struct ae2f_ds_cAlloc* arr,
	const void* wanted,
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
/// @param fpElCmp 
/// Comparing function.
/// comparing will be proceed as
/// ```c
/// fpElCmp(element, wanted);
/// ```
/// @param out 
/// Buffer where the Index may be stored
/// @return 
/// @ref ae2f_errGlob_OK \n
/// @ref ae2f_ds_Arr_NOT_FOUND 
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_ALLOC_FAILED \n 
/// @see ae2f_ds_Alloc_cRef_getSize
/// @see ae2f_ds_Alloc_cRef_Read
/// @see ae2f_ds_Arr_BSearch_imp
#define ae2f_ds_Arr_BSearch(arr, wanted, fpElCmp, retidx) ae2f_ds_Arr_BSearch_imp(ae2f_reinterpret_cast(const ae2f_struct ae2f_ds_Alloc_Refer*, arr), wanted, ae2f_reinterpret_cast(const ae2f_ds_Arr_fpElCmp_t, fpElCmp), retidx)

/// @brief 
/// Order the arr via quick sort.
/// @param arr 
/// An array to sort
/// @param fpElCmp 
/// comparing will be proceed as
/// ```c
/// fpElCmp(element, wanted);
/// ```
/// @return
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_ALLOC_FAILED \n
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_ds_Alloc_cRef_getSize
/// @see ae2f_ds_Alloc_cRef_Read
/// @see ae2f_ds_Alloc_cRef_Write
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Arr_QSort_imp(
	ae2f_struct ae2f_ds_cAlloc* arr,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp
);

/// @brief 
/// Order the arr via quick sort.
/// @param arr 
/// An array to sort
/// @param fpElCmp 
/// comparing will be proceed as
/// ```c
/// fpElCmp(element, wanted);
/// ```
/// @return
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_ALLOC_FAILED \n
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_ds_Alloc_cRef_getSize
/// @see ae2f_ds_Alloc_cRef_Read
/// @see ae2f_ds_Alloc_cRef_Write
/// @see ae2f_ds_Arr_QSort_imp
#define ae2f_ds_Arr_QSort(arr, fpElCmp) ae2f_ds_Arr_QSort_imp(ae2f_reinterpret_cast(ae2f_struct ae2f_ds_Alloc_cRef*, arr),ae2f_reinterpret_cast(const ae2f_ds_Arr_fpElCmp_t, fpElCmp))

#endif // !defined(ae2f_DataStructure_Array_h)
