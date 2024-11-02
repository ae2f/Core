#if !defined(ae2f_ds_Alloc_h)
#define ae2f_ds_Alloc_h

#include <ae2f/Macro/Cast.h>
#include <ae2f/Macro/Compare.h>
#include <ae2f/Macro/errGlob.h>
#include <ae2f/Macro/Call.h>
 
#pragma region Structures


/// @brief
/// The data holder for [cRef] and [cOwn].
struct ae2f_ds_cAlloc;


/// @brief
/// # This structure does not own the memory.
/// 
/// An interface to implement the linear array.
#define ae2f_ds_Alloc_cRef ae2f_ds_cAlloc

/// @brief
/// # This structure owns the memory.
#define ae2f_ds_Alloc_cOwn ae2f_ds_cAlloc

#pragma region vRefer

/// @param _this The constant instance of the class.
/// @param pSize A pointer where the count of the array, as an unit of elements.
/// @param pel A pointer where the size of the element.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpLen_t)(
	const ae2f_struct ae2f_ds_Alloc_cRef* _this,
	size_t* pSize,
	size_t* pel
);

/// @param _this The constant instance of the class.
/// @param Index The Index [in an unit of bytes] where the element to copy is.
/// @param lpBuff A pointer of buffer where the element to be copied.
/// @param Buff_size The allocated size of the `lpBuff`.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpRead_t)(
	const ae2f_struct ae2f_ds_Alloc_cRef* _this, 
	size_t Index, 
	void* lpBuff, 
	size_t Buff_size
);

/// @param _this The instance of the class.
/// @param Index The Index [in an unit of bytes] where the element to be overwritten.
/// @param lpBuff A pointer of an element.
/// @param Buff_size An allocated size of the `lpBuff`.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpWrite_t)(
	ae2f_struct ae2f_ds_Alloc_cRef* _this, 
	size_t Index, 
	const void* lpBuff,
	size_t Buff_size
);

#pragma endregion
#pragma region vOwner

/// @brief 
/// Frees the memory of `_this`.
/// @param _this The instance of a class where the memory to free is located.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpDel_t)(
	ae2f_struct ae2f_ds_Alloc_cOwn* _this
);

/// @brief 
/// Resizes the memory of `_this`.
/// 
/// Additional memories(newly allocated) must be initiated as 0.
/// @param _this The owner of the memory.
/// @param elcount The count of the elements.
/// @param elsize The size of each elements.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpReConfig_t)(
	ae2f_struct ae2f_ds_Alloc_cOwn* _this, 
	size_t elcount,
	size_t elsize
);

/// @brief Structure for virtual function pointer.
struct ae2f_ds_vAlloc {
	/// @param _this The constant instance of the class.
	/// @param pSize A pointer where the count of the array, as an unit of elements.
	/// @param pel A pointer where the size of the element.
	const ae2f_ds_Alloc_fpLen_t GetSize;

	/// @param _this The constant instance of the class.
	/// @param Index The Index [in an unit of bytes] where the element to copy is.
	/// @param lpBuff A pointer of buffer where the element to be copied.
	/// @param Buff_size The allocated size of the `lpBuff`.
	const ae2f_ds_Alloc_fpRead_t Read;

	/// @param _this The instance of the class.
	/// @param Index The Index [in an unit of bytes] where the element to be overwritten.
	/// @param lpBuff A pointer of an element.
	/// @param Buff_size An allocated size of the `lpBuff`.
	const ae2f_ds_Alloc_fpWrite_t Write;

	/// @brief 
	/// Frees the memory of `_this`.
	/// @param _this The instance of a class where the memory to free is located.
	const ae2f_ds_Alloc_fpDel_t Del;

	/// @brief 
	/// Resizes the memory of `_this`.
	/// 
	/// Additional memories(newly allocated) must be initiated as 0.
	/// @param _this The owner of the memory.
	/// @param elcount The count of the elements.
	/// @param elsize The size of each elements.
	const ae2f_ds_Alloc_fpReConfig_t ReConfig;
};

struct ae2f_ds_cAlloc {
	char* data;
	const ae2f_struct ae2f_ds_vAlloc* v;
};

/// @brief A default implementation of [ae2f_ds_vAlloc].
ae2f_SHAREDCALL ae2f_extern const ae2f_struct ae2f_ds_vAlloc ae2f_ds_vAlloc_cLinear;

#pragma endregion
#pragma endregion

/// @brief 
///	Initialises the pointer.
/// 
///	Injects the function pointers automatically.
/// 
/// Passing zero via [vRef] or [vOwn] causes this function to set the functions as default.
/// @param This 
/// Address to be set.
/// 
/// Do not pass when it is allocated.
/// @param imp
/// Class Implementations
/// @return 
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Alloc_cOwn_Init(
	ae2f_struct ae2f_ds_Alloc_cOwn* This, 
	const ae2f_struct ae2f_ds_vAlloc* imp
);

/// @brief
///	Initialises the pointer.
/// 
///	Injects the function pointers automatically.
/// @param This:	ae2f_ds_Alloc_Owner* 
/// 
/// Address to be set.
/// Do not pass when it is allocated.
/// @returns ae2f_errint_t
#define ae2f_ds_Alloc_cOwn_InitAuto(This) ae2f_ds_Alloc_cOwn_Init(This, &ae2f_ds_vAlloc_cLinear)

#pragma region Call vRefer


/// @brief
/// @param This	const	ae2f_ds_cAlloc*
/// @returns const ae2f_ds_cAlloc
#define ae2f_ds_Alloc_cRef_Mk(This) ae2f_record_make(ae2f_struct ae2f_ds_Alloc_cRef, (This)->data, (This)->v)

/// @param This:	const	ae2f_ds_cAlloc*
/// @param Name:	code
/// Wanted Function Name
/// @returns
/// Good: The Function Pointer with the given name.
/// 
/// Bad: 0
#define _ae2f_ds_Alloc_FndFun(This, Name) ae2f_Macro_Compare_TakeMember(ae2f_Macro_Compare_TakeMember(This, v, 0), Name, 0)
#define _ae2f_ds_Alloc_Call(This, Name, ...) (_ae2f_ds_Alloc_FndFun(This, Name) ? _ae2f_ds_Alloc_FndFun(This, Name)(This, __VA_ARGS__) : ae2f_errGlob_IMP_NOT_FOUND)
#define _ae2f_ds_Alloc_CallVoid(This, Name) (_ae2f_ds_Alloc_FndFun(This, Name) ? _ae2f_ds_Alloc_FndFun(This, Name)(This) : ae2f_errGlob_IMP_NOT_FOUND)

/// @param This:	const	ae2f_ds_cAlloc*
/// @param sizebuff:	size_t*
/// @param elsizebuff:	size_t*
/// 
/// @returns ae2f_errint_t
#define ae2f_ds_Alloc_cRef_getSize(This, sizebuff, elsizebuff) _ae2f_ds_Alloc_Call(This, GetSize, sizebuff, elsizebuff)

/// @brief
/// One of [buff], [one] was null.
/// Data was not be copied either to [buff] or [one].
/// Operation has done gracefully.
/// @return
/// (ae2f_errGlob_DONE_HOWEV | ae2f_errGlob_PTR_IS_NULL)
#define ae2f_ds_Alloc_cRef_getSize_NCOPIED ae2f_static_cast(ae2f_errint_t, 0b1000010)

/// @param	This:	const	ae2f_ds_cAlloc*
/// @param	idx:	size_t
///	@param buff:	void*
/// @param elsize:	size_t
/// @returns	ae2f_errint_t
#define ae2f_ds_Alloc_cRef_Read(This, idx, buff, elsize) _ae2f_ds_Alloc_Call(This, Read, idx, buff, elsize)

///	@param This:	ae2f_ds_cAlloc*
/// @param idx:	size_t
///	@param src:	const	void*
///	@param srcsize:	size_t
/// @returns ae2f_errint_t
#define ae2f_ds_Alloc_cRef_Write(This, idx, src, srcsize) _ae2f_ds_Alloc_Call(This, Write, idx, src, srcsize)
#pragma endregion
#pragma region Call vOwner

/// @param This:	const	ae2f_ds_cAlloc*
/// @param sizebuff:	size_t*
/// @param elsizebuff:	size_t*
/// 
/// @returns ae2f_errint_t
#define ae2f_ds_Alloc_cOwn_getSize ae2f_ds_Alloc_cRef_getSize

/// @param	This:	const	ae2f_ds_Alloc_Owner*
/// @param	idx:	size_t
///	@param buff:	void*
/// @param elsize:	size_t
/// @returns	ae2f_errint_t
#define ae2f_ds_Alloc_cOwn_Read ae2f_ds_Alloc_cRef_Read

///	@param This:	ae2f_ds_Alloc_Owner*
/// @param idx:	size_t
///	@param src:	const	void*
///	@param srcsize:	size_t
/// @returns ae2f_errint_t
#define ae2f_ds_Alloc_cOwn_Write ae2f_ds_Alloc_cRef_Write

///	@param This:		ae2f_ds_Alloc_Owner*
/// @param Returns:
/// @returns
///	ae2f_errint_t
#define ae2f_ds_Alloc_cOwn_Del(This) _ae2f_ds_Alloc_CallVoid(This, Del)

#define ae2f_ds_Alloc_cOwn_ReConfig(This, elcount, elsize) _ae2f_ds_Alloc_Call(This, ReConfig, elcount, elsize)

///	@param This:		ae2f_ds_Alloc_Owner*
///	@param NewSize:	size_t
/// @returns
///	ae2f_errint_t
#define ae2f_ds_Alloc_cOwn_ReSize(This, bitcount) ae2f_ds_Alloc_cOwn_ReConfig(This, bitcount, 1)


/// @brief 
/// Allocates the memory.
/// Copies the data from `Source` to `This`.
/// @param This Points the allocated memory
/// @param Source Copy Source
/// @return 
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Alloc_cOwn_Cpy_imp(
	ae2f_struct ae2f_ds_Alloc_cOwn* This, 
	const ae2f_struct ae2f_ds_cAlloc* Source
);

/// @brief 
/// Allocates the memory.
/// Copies the data from `Source` to `This`.
/// @param This Points the allocated memory
/// @param Source Copy Source
/// @return 
#define ae2f_ds_Alloc_cOwn_Cpy(This, Source) ae2f_ds_Alloc_cOwn_Cpy_imp(This, ae2f_reinterpret_cast(const ae2f_struct ae2f_ds_cAlloc*, Source))

#pragma endregion
#endif