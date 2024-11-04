/// @file
/// @warning
/// This file is a helper header of @ref ae2f/Ds/Alloc.h \n
/// Few definitions may lack.

/// @brief
/// # This structure owns the memory.
/// @see ae2f_ds_cAlloc
#define ae2f_ds_Alloc_cOwn ae2f_ds_cAlloc

#pragma region Virtual Functions

/// @brief 
/// Frees the memory of `_this`.
/// @param _this The instance of a class where the memory to free is located.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see ae2f_ds_Alloc_cOwn
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpDel_t)(
    ae2f_struct ae2f_ds_Alloc_cOwn* _this
);

/// @brief 
/// Resizes the memory of `_this`. \n
/// Additional memories(newly allocated) must be initiated as 0.
/// @param _this The owner of the memory.
/// @param elcount The count of the elements.
/// @param elsize The size of each elements.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_ds_Alloc_cOwn
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpReConfig_t)(
    ae2f_struct ae2f_ds_Alloc_cOwn* _this, 
    size_t elcount, 
    size_t elsize
);


#pragma endregion


#pragma region inits

/// @brief 
///	Initialises the pointer. \n
///	Injects the function pointers automatically.
/// @param This 
/// Address to be set. \n
/// Do not pass when it is allocated.
/// @param imp
/// Class Implementations
/// @return @ref ae2f_errGlob_OK
/// @exception  \
/// @ref ae2f_ds_Alloc_Err_FPIMPNULL  \n
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see ae2f_ds_Alloc_cOwn
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Alloc_cOwn_Init(
	ae2f_struct ae2f_ds_Alloc_cOwn* This, 
	const ae2f_struct ae2f_ds_vAlloc* imp
);

/// @brief 
///	Initialises the pointer. \n
///	Injects the function pointers automatically.
/// @param This 
/// Address to be set. \n
/// Do not pass when it is allocated.
/// @param imp
/// Class Implementations
/// @return @ref ae2f_errGlob_OK
/// @exception  \
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see ae2f_ds_Alloc_cOwn
/// @see ae2f_ds_Alloc_cOwn_Init
#define ae2f_ds_Alloc_cOwn_InitAuto(This) ae2f_ds_Alloc_cOwn_Init(This, &ae2f_ds_vAlloc_cLinear)

/// @brief 
/// Allocates the memory.
/// Copies the data from [Source] to [This].
/// @param This Points the allocated memory.
/// @param Source Source to copy.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_ds_Alloc_cRef_getSize
/// @see ae2f_ds_Alloc_cRef_Read
/// @see ae2f_ds_Alloc_cRef_Write
/// @see ae2f_ds_Alloc_cOwn
/// @see ae2f_ds_Alloc_cOwn_ReConfig
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Alloc_cOwn_Cpy_imp(
	ae2f_struct ae2f_ds_Alloc_cOwn* This, 
	const ae2f_struct ae2f_ds_cAlloc* Source
);

/// @brief 
/// Allocates the memory.
/// Copies the data from [Source] to [This].
/// @param This Points the allocated memory.
/// @param Source Source to copy.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_ds_Alloc_cRef_getSize
/// @see ae2f_ds_Alloc_cRef_Read
/// @see ae2f_ds_Alloc_cRef_Write
/// @see ae2f_ds_Alloc_cOwn
/// @see ae2f_ds_Alloc_cOwn_ReConfig
/// @see ae2f_ds_Alloc_cOwn_Cpy_imp
#define ae2f_ds_Alloc_cOwn_Cpy(This, Source) ae2f_ds_Alloc_cOwn_Cpy_imp(This, ae2f_reinterpret_cast(const ae2f_struct ae2f_ds_cAlloc*, Source))

#pragma endregion


#pragma region Methods Call

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
/// @see ae2f_ds_Alloc_fpLen_t
/// @see ae2f_ds_Alloc_cRef_getSize
#define ae2f_ds_Alloc_cOwn_getSize ae2f_ds_Alloc_cRef_getSize

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
/// @see ae2f_ds_Alloc_cRef_Read
#define ae2f_ds_Alloc_cOwn_Read ae2f_ds_Alloc_cRef_Read

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
/// @see ae2f_ds_Alloc_cRef_Write
#define ae2f_ds_Alloc_cOwn_Write ae2f_ds_Alloc_cRef_Write

/// @brief 
/// Frees the memory of [This].
/// @param This The instance of a class where the memory to free is located.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL
/// @see ae2f_ds_Alloc_cOwn
/// @see ae2f_ds_Alloc_fpDel_t
#define ae2f_ds_Alloc_cOwn_Del(This) _ae2f_ds_Alloc_CallVoid(This, Del)

/// @brief 
/// Resizes the memory of [This]. \n
/// Additional memories(newly allocated) must be initiated as 0.
/// @param This The owner of the memory.
/// @param elcount The count of the elements.
/// @param elsize The size of each elements.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_ds_Alloc_cOwn
/// @see ae2f_ds_Alloc_fpReConfig_t
#define ae2f_ds_Alloc_cOwn_ReConfig(This, elcount, elsize) _ae2f_ds_Alloc_Call(This, ReConfig, elcount, elsize)

/// @warning
/// This operation may not be efficient under certain implements.
/// @brief 
/// Resizes the memory of [This] as bytes count. \n
/// Additional memories(newly allocated) must be initiated as 0. \n
/// Element size will be suggested as 1.
/// @param This The owner of the memory.
/// @param bytecount The byte length to resize.
/// @return @ref ae2f_errGlob_OK
/// @exception \
/// @ref ae2f_errGlob_PTR_IS_NULL \n
/// @ref ae2f_errGlob_ALLOC_FAILED
/// @see ae2f_ds_Alloc_cOwn
/// @see ae2f_ds_Alloc_fpReConfig_t
/// @see ae2f_ds_Alloc_cOwn_ReConfig
#define ae2f_ds_Alloc_cOwn_ReSize(This, bytecount) ae2f_ds_Alloc_cOwn_ReConfig(This, bytecount, 1)

#pragma endregion