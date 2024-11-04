/// @file
/// @warning
/// This file is a helper header of @ref ae2f/Ds/Alloc.h \n
/// Few definitions may lack.

/// @brief
/// # This structure does not own the memory.
/// 
/// An interface to implement the linear array.
/// @see ae2f_ds_cAlloc
#define ae2f_ds_Alloc_cRef ae2f_ds_cAlloc

#pragma region functions pointers

/// @brief
/// Gets the length, and element size of the class.
/// @param _this The constant instance of the class.
/// @param pSize A pointer where the count of the array, as an unit of elements.
/// @param pel A pointer where the size of the element.
/// @return 
/// @ref ae2f_errGlob_OK \n
/// @ref ae2f_ds_Alloc_Err_NCOPIED
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @see ae2f_ds_Alloc_cRef
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpLen_t)(
	const ae2f_struct ae2f_ds_Alloc_cRef* _this,
	size_t* pSize,
	size_t* pel
);

/// @brief
/// Gets data from a class.
/// @param _this The constant instance of the class.
/// @param Index The Index [in an unit of bytes] where the element to copy is.
/// @param lpBuff A pointer of buffer where the element to be copied.
/// @param Buff_size The allocated size of the `lpBuff`.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
/// @see ae2f_ds_Alloc_cRef
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpRead_t)(
	const ae2f_struct ae2f_ds_Alloc_cRef* _this, 
	size_t Index, 
	void* lpBuff, 
	size_t Buff_size
);

/// @brief
/// Sets data to a class.
/// @param _this The instance of the class.
/// @param Index The Index [in an unit of bytes] where the element to be overwritten.
/// @param lpBuff A pointer of an element.
/// @param Buff_size An allocated size of the `lpBuff`.
/// @return 
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
/// @see ae2f_ds_Alloc_cRef
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpWrite_t)(
	ae2f_struct ae2f_ds_Alloc_cRef* _this, 
	size_t Index, 
	const void* lpBuff,
	size_t Buff_size
);

#pragma endregion


/// @brief
/// Initialises the class for reffering.
/// @param This	{const ae2f_ds_cAlloc*}
/// @returns {const ae2f_ds_Alloc_cRef} This initiated structure.
/// @warning
/// You need to suggest that returning value of this does not own the memory.
/// @see ae2f_ds_Alloc_cRef
#define ae2f_ds_Alloc_cRef_Mk(This) ae2f_record_make(ae2f_struct ae2f_ds_Alloc_cRef, (This)->data, (This)->v)


#pragma region Methods

/// @brief
/// Gets the length, and element size of the class.
/// @param This The constant instance of the class.
/// @param sizebuff A pointer where the count of the array, as an unit of elements.
/// @param elsizebuff A pointer where the size of the element.
/// @return 
/// @ref ae2f_errGlob_OK \n
/// @ref ae2f_ds_Alloc_Err_NCOPIED
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @see ae2f_ds_Alloc_cRef
/// @see ae2f_ds_Alloc_fpLen_t
#define ae2f_ds_Alloc_cRef_getSize(This, sizebuff, elsizebuff) _ae2f_ds_Alloc_Call(This, GetSize, sizebuff, elsizebuff)

/// @brief
/// Gets data from a class.
/// @param This The constant instance of the class.
/// @param idx The Index [in an unit of bytes] where the element to copy is.
/// @param buff A pointer of buffer where the element to be copied.
/// @param elsize The allocated size of the [buff].
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
/// @see ae2f_ds_Alloc_cRef
/// @see ae2f_ds_Alloc_fpRead_t
#define ae2f_ds_Alloc_cRef_Read(This, idx, buff, elsize) _ae2f_ds_Alloc_Call(This, Read, idx, buff, elsize)

/// @brief
/// Sets data to a class.
/// @param This The instance of the class.
/// @param idx The Index [in an unit of bytes] where the element to be overwritten.
/// @param src A pointer of an element.
/// @param srcsize An allocated size of the [src].
/// @return 
/// @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND \n
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_ds_Alloc_Err_IDX_INVALID
/// @see ae2f_ds_Alloc_cRef
/// @see ae2f_ds_Alloc_fpWrite_t
#define ae2f_ds_Alloc_cRef_Write(This, idx, src, srcsize) _ae2f_ds_Alloc_Call(This, Write, idx, src, srcsize)

#pragma endregion