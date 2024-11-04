#if !defined(ae2f_ds_Alloc_h)
#define ae2f_ds_Alloc_h

#include <ae2f/Macro/Cast.h>
#include <ae2f/Macro/Cmp.h>
#include <ae2f/Macro/errGlob.h>
#include <ae2f/Macro/Call.h>

#include "Alloc/Err.h"
 
struct ae2f_ds_vAlloc;
struct ae2f_ds_cAlloc;

#include "Alloc/Ref.h"
#include "Alloc/Own.h"

#pragma region vOwner

/// @brief Structure for virtual function pointer.
struct ae2f_ds_vAlloc {
	const ae2f_ds_Alloc_fpLen_t GetSize;
	const ae2f_ds_Alloc_fpRead_t Read;
	const ae2f_ds_Alloc_fpWrite_t Write;	
	const ae2f_ds_Alloc_fpDel_t Del;
	const ae2f_ds_Alloc_fpReConfig_t ReConfig;
};

/// @brief
/// Each elements will be physically linear.
ae2f_SHAREDCALL ae2f_extern const ae2f_struct ae2f_ds_vAlloc ae2f_ds_vAlloc_cLinear;

#pragma endregion

/// @brief
/// The data holder for [cRef] and [cOwn].
/// @see
/// ae2f_ds_Alloc_cRef \n
/// ae2f_ds_Alloc_cOwn
struct ae2f_ds_cAlloc {
	/// @brief Where data is hold.
	char* data;
	/// @brief The implementations.
	const ae2f_struct ae2f_ds_vAlloc* v;
};

/// @param This {const ae2f_ds_cAlloc*} Structure
/// The structure suggested to have a function pointer.
/// @param Name {Member Name} The valid member's name.
/// Wanted Function Name.
/// @returns
/// The Function Pointer with the given name.
/// @exception 0: [This] was nullptr.
#define _ae2f_ds_Alloc_FndFun(This, Name) ae2f_Macro_Cmp_TakeMem(ae2f_Macro_Cmp_TakeMem(This, v, 0), Name, 0)

/// @warning
/// Notice that it can't handle the function without parameters. \n
/// For certain functions, use @ref _ae2f_ds_Alloc_CallVoid.
/// @brief
/// @param This {const ae2f_ds_cAlloc*} Structure
/// @param Name {Member Name} Function Name
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_ds_cAlloc
/// @see _ae2f_ds_Alloc_FndFun
#define _ae2f_ds_Alloc_Call(This, Name, ...) (_ae2f_ds_Alloc_FndFun(This, Name) ? _ae2f_ds_Alloc_FndFun(This, Name)(This, __VA_ARGS__) : ae2f_errGlob_IMP_NOT_FOUND)

/// @warning
/// Notice that it can't handle the function with parameters. \n
/// For certain functions, use @ref _ae2f_ds_Alloc_Call.
/// @param This {const ae2f_ds_cAlloc*} Structure
/// @param Name {Member Name} Function Name
/// @exception \
/// @ref ae2f_errGlob_IMP_NOT_FOUND
/// @see ae2f_ds_cAlloc
/// @see _ae2f_ds_Alloc_FndFun
#define _ae2f_ds_Alloc_CallVoid(This, Name) (_ae2f_ds_Alloc_FndFun(This, Name) ? _ae2f_ds_Alloc_FndFun(This, Name)(This) : ae2f_errGlob_IMP_NOT_FOUND)


#endif