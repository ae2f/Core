#if !defined(ae2f_DataStructure_Allocator_h)
#define ae2f_DataStructure_Allocator_h

#include <ae2f/Macro/Cast.h>
#include <ae2f/Macro/Compare.h>
#include <ae2f/Macro/errGlobal.h>
#include <ae2f/Macro/Call.h>
 
#pragma region Structures

/// @brief
/// # This structure does not own the memory.
/// 
/// An interface to implement the linear array.
struct ae2f_ds_Alloc_Refer;

/// @brief
/// # This structure owns the memory.
/// 
/// An interface to implement the linear array.
struct ae2f_ds_Alloc_Owner;

#pragma region vRefer

/// @param _this The constant instance of the class.
/// @param pSize A pointer where the length of the array.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpLen_t)(
	const ae2f_struct ae2f_ds_Alloc_Refer* _this,
	size_t* pSize
);


/// @param _this The constant instance of the class.
/// @param Index The Index [in an unit of bytes] where the element to copy is.
/// @param lpBuff A pointer of buffer where the element to be copied.
/// @param Buff_size The allocated size of the `lpBuff`.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpRead_t)(
	const ae2f_struct ae2f_ds_Alloc_Refer* _this, 
	size_t Index, 
	void* lpBuff, 
	size_t Buff_size
);

/// @param _this The instance of the class.
/// @param Index The Index [in an unit of bytes] where the element to be overwritten.
/// @param lpBuff A pointer of an element.
/// @param Buff_size An allocated size of the `lpBuff`.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpWrite_t)(
	ae2f_struct ae2f_ds_Alloc_Refer* _this, 
	size_t Index, 
	const void* lpBuff,
	size_t Buff_size
);

struct ae2f_ds_Alloc_vRefer {
	const ae2f_ds_Alloc_fpLen_t getSize;
	const ae2f_ds_Alloc_fpRead_t Read;
	const ae2f_ds_Alloc_fpWrite_t Write;
};

#pragma endregion
#pragma region vOwner

/// @brief 
/// Frees the memory of `_this`.
/// @param _this The instance of a class where the memory to free is located.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpDel_t)(
	ae2f_struct ae2f_ds_Alloc_Owner* _this
);

/// @brief 
/// Resizes the memory of `_this` in a byte size of `size`.
/// 
/// Additional allocated memory would be set as 0.
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpResize_t)(
	ae2f_struct ae2f_ds_Alloc_Owner* _this, 
	size_t size
);

struct ae2f_ds_Alloc_vOwner {
	const ae2f_ds_Alloc_fpDel_t Del;
	const ae2f_ds_Alloc_fpResize_t reSize;
};

struct ae2f_ds_Alloc_Refer {
	char* data;
	const ae2f_struct ae2f_ds_Alloc_vRefer* vRefer;
};

struct ae2f_ds_Alloc_Owner {
	char* data;
	const ae2f_struct ae2f_ds_Alloc_vRefer* vRefer;
	const ae2f_struct ae2f_ds_Alloc_vOwner* vOwner;
};

/// @brief A default function set of [vRefer].
ae2f_SHAREDCALL ae2f_extern const ae2f_struct ae2f_ds_Alloc_vRefer ae2f_ds_Alloc_vRefer_cLinear;

/// @brief A default function set of [vOwner].
ae2f_SHAREDCALL ae2f_extern const ae2f_struct ae2f_ds_Alloc_vOwner ae2f_ds_Alloc_vOwner_cLinear;

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
/// @param vRef 
/// Refering functions custom.
/// @param vOwn 
/// Functions custom for memory owning structure.
/// @return 
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Alloc_vOwner_Init(
	ae2f_struct ae2f_ds_Alloc_Owner* This, 
	const ae2f_struct ae2f_ds_Alloc_vRefer* vRef, 
	const ae2f_struct ae2f_ds_Alloc_vOwner* vOwn
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
#define ae2f_ds_Alloc_vOwner_InitAuto(This) ae2f_ds_Alloc_vOwner_Init(This, &ae2f_ds_Alloc_vRefer_cLinear, &ae2f_ds_Alloc_vOwner_cLinear)

#pragma region Call vRefer


/// @brief
/// @param This	const	ae2f_ds_Alloc_Refer*
/// @returns const ae2f_ds_Alloc_Refer
#define ae2f_ds_Alloc_vRefer_Ref(This) ae2f_record_make(ae2f_struct ae2f_ds_Alloc_Refer, (This)->data, (This)->vRefer)

/// @param This:	const	ae2f_ds_Alloc_Refer*
/// @param Name:	code
/// Wanted Function Name
/// @returns
/// Good: The Function Pointer with the given name.
/// 
/// Bad: 0
#define ae2f_ds_Alloc_vRefer_FindFunc(This, Name) ae2f_Macro_Compare_TakeMember(ae2f_Macro_Compare_TakeMember(This, vRefer, 0), Name, 0)

/// @param This:	const	ae2f_ds_Alloc_Refer*
/// @param sizebuff:	size_t*
/// 
/// @returns ae2f_errint_t
#define ae2f_ds_Alloc_vRefer_getSize(This, sizebuff) (ae2f_ds_Alloc_vRefer_FindFunc(This, getSize) ? ae2f_ds_Alloc_vRefer_FindFunc(This, getSize)(This, sizebuff) : ae2f_errGlobal_IMP_NOT_FOUND)

/// @param	This:	const	ae2f_ds_Alloc_Refer*
/// @param	idx:	size_t
///	@param buff:	void*
/// @param elsize:	size_t
/// @returns	ae2f_errint_t
#define ae2f_ds_Alloc_vRefer_Read(This, idx, buff, elsize) (ae2f_ds_Alloc_vRefer_FindFunc(This, Read) ? ae2f_ds_Alloc_vRefer_FindFunc(This, Read)(This, idx, buff, elsize) : ae2f_errGlobal_IMP_NOT_FOUND)

///	@param This:	ae2f_ds_Alloc_Refer*
/// @param idx:	size_t
///	@param src:	const	void*
///	@param srcsize:	size_t
/// @returns ae2f_errint_t
#define ae2f_ds_Alloc_vRefer_Write(This, idx, src, srcsize) (ae2f_ds_Alloc_vRefer_FindFunc(This, Write) ? ae2f_ds_Alloc_vRefer_FindFunc(This, Write)(This, idx, src, srcsize) : ae2f_errGlobal_IMP_NOT_FOUND)
#pragma endregion
#pragma region Call vOwner

/// @brief
/// @param This:	const	ae2f_ds_Alloc_Owner*
/// @returns const ae2f_ds_Alloc_Refer
#define ae2f_ds_Alloc_vOwner_Ref ae2f_ds_Alloc_vRefer_Ref

/// @param This:	const	ae2f_ds_Alloc_Owner*
/// @param sizebuff:	size_t*
/// 
/// @returns ae2f_errint_t
#define ae2f_ds_Alloc_vOwner_getSize(This, sizebuff) ae2f_ds_Alloc_vRefer_getSize(ae2f_reinterpret_cast(const ae2f_struct ae2f_ds_Alloc_Refer*, This), sizebuff)

/// @param	This:	const	ae2f_ds_Alloc_Owner*
/// @param	idx:	size_t
///	@param buff:	void*
/// @param elsize:	size_t
/// @returns	ae2f_errint_t
#define ae2f_ds_Alloc_vOwner_Read(This, idx, buff, elsize) ae2f_ds_Alloc_vRefer_Read(ae2f_reinterpret_cast(const ae2f_struct ae2f_ds_Alloc_Refer*, This), idx, buff, elsize)

///	@param This:	ae2f_ds_Alloc_Owner*
/// @param idx:	size_t
///	@param src:	const	void*
///	@param srcsize:	size_t
/// @returns ae2f_errint_t
#define ae2f_ds_Alloc_vOwner_Write(This, idx, src, srcsize) ae2f_ds_Alloc_vRefer_Write(ae2f_reinterpret_cast(ae2f_struct ae2f_ds_Alloc_Refer*, This), idx, src, srcsize)

///	@param This:	const	ae2f_ds_Alloc_Owner*
///	@param Name:	Code
/// Wanted Function Name
/// @returns
///	Good: The Function Pointer with the given name.  
/// 
///	Bad: 0
#define ae2f_ds_Alloc_vOwner_FindFunc(This, Name) ae2f_Macro_Compare_TakeMember(ae2f_Macro_Compare_TakeMember(This, vOwner, 0), Name, 0)

///	@param This:		ae2f_ds_Alloc_Owner*
/// @param Returns:
/// @returns
///	ae2f_errint_t
#define ae2f_ds_Alloc_vOwner_Del(This) (ae2f_ds_Alloc_vOwner_FindFunc(This, Del) ? ae2f_ds_Alloc_vOwner_FindFunc(This, Del)(This) : ae2f_errGlobal_IMP_NOT_FOUND)

///	@param This:		ae2f_ds_Alloc_Owner*
///	@param NewSize:	size_t
/// @returns
///	ae2f_errint_t
#define ae2f_ds_Alloc_vOwner_reSize(This, NewSize) (ae2f_ds_Alloc_vOwner_FindFunc(This, reSize) ? ae2f_ds_Alloc_vOwner_FindFunc(This, reSize)(This, NewSize) : ae2f_errGlobal_IMP_NOT_FOUND)

/// @brief 
/// Allocates the memory.
/// Copies the data from `Source` to `This`.
/// @param This Points the allocated memory
/// @param Source Copy Source
/// @return 
ae2f_SHAREDCALL ae2f_extern ae2f_errint_t ae2f_ds_Alloc_vOwner_Copy_imp(ae2f_struct ae2f_ds_Alloc_Owner* This, const ae2f_struct ae2f_ds_Alloc_Refer* Source);

/// @brief 
/// Allocates the memory.
/// Copies the data from `Source` to `This`.
/// @param This Points the allocated memory
/// @param Source Copy Source
/// @return 
#define ae2f_ds_Alloc_vOwner_Copy(This, Source) ae2f_ds_Alloc_vOwner_Copy_imp(This, ae2f_reinterpret_cast(const ae2f_struct ae2f_ds_Alloc_Refer*, Source))

#pragma endregion
#endif