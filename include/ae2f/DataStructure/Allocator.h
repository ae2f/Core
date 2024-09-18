#if !defined(ae2f_DataStructure_Allocator_h)
#define ae2f_DataStructure_Allocator_h

#include <ae2f/Macro/Cast.h>
#include <ae2f/Macro/Compare.h>
#include <ae2f/Macro/errGlobal.h>

#pragma region Structures
struct ae2f_ds_Alloc_Refer;
struct ae2f_ds_Alloc_Owner;

#pragma region vRefer
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpLen_t)(const ae2f_struct ae2f_ds_Alloc_Refer*, size_t*);
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpRead_t)(const ae2f_struct ae2f_ds_Alloc_Refer*, size_t, void*, size_t);
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpWrite_t)(ae2f_struct ae2f_ds_Alloc_Refer*, size_t, const void*, size_t);

struct ae2f_ds_Alloc_vRefer {
	const ae2f_ds_Alloc_fpLen_t getSize;
	const ae2f_ds_Alloc_fpRead_t Read;
	const ae2f_ds_Alloc_fpWrite_t Write;
};

#define ae2f_ds_Alloc_vRefer_mPrm(getsize, read, write, ...) { (getsize), (read), (write) }
#pragma endregion
#pragma region vOwner
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpMake_t)(ae2f_struct ae2f_ds_Alloc_Owner*, size_t);
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpDel_t)(ae2f_struct ae2f_ds_Alloc_Owner*);
typedef ae2f_errint_t(*ae2f_ds_Alloc_fpResize_t)(ae2f_struct ae2f_ds_Alloc_Owner*, size_t);

struct ae2f_ds_Alloc_vOwner {
	const ae2f_ds_Alloc_fpMake_t Make;
	const ae2f_ds_Alloc_fpDel_t Del;
	const ae2f_ds_Alloc_fpResize_t reSize;
};

struct ae2f_ds_Alloc_Refer {
	char* data;
	ae2f_struct ae2f_ds_Alloc_vRefer* vRefer;
};

struct ae2f_ds_Alloc_Owner {
	char* data;
	ae2f_struct ae2f_ds_Alloc_vRefer* vRefer;
	ae2f_struct ae2f_ds_Alloc_vOwner* vOwner;
};

ae2f_extern const ae2f_struct ae2f_ds_Alloc_vRefer ae2f_ds_Alloc_vRefer_cLinear;
ae2f_extern const ae2f_struct ae2f_ds_Alloc_vOwner ae2f_ds_Alloc_vOwner_cLinear;

#define ae2f_ds_Alloc_vOwner_mPrm(mk, del, resize, ...) { (mk), (del), (resize) }
#pragma endregion
#pragma endregion

/// <summary>
///	Initialises the pointer.
///	Injects the function pointers automatically.
/// 
/// Passing zero via [vRef] or [vOwn] causes this function to set the functions as default.
/// </summary>
/// <param name="This">
/// Address to be set.
/// Do not pass when it is allocated.
/// </param>
/// <param name="vRef">
/// Refering functions custom.
/// </param>
/// <param name="vOwn">
/// Functions custom for memory owning structure.
/// </param>
/// <returns>[errGlobal]</returns>
ae2f_extern ae2f_errint_t ae2f_ds_Alloc_vOwner_Init(ae2f_struct ae2f_ds_Alloc_Owner* This, const ae2f_struct ae2f_ds_Alloc_vRefer* vRef ae2f_add_when_cxx(=0), const ae2f_struct ae2f_ds_Alloc_vOwner* vOwn ae2f_add_when_cxx(= 0));

// Summary:
//	Initialises the pointer.
//	Injects the function pointers automatically.
// 
// Parameters:
//	This:	ae2f_ds_Alloc_Owner*
//		Address to be set.
//		Do not pass when it is allocated.
// 
// Returns:
//	ae2f_errint_t
// 
//	From:
//		errGlobal
#define ae2f_ds_Alloc_vOwner_InitAuto(This) ae2f_ds_Alloc_vOwner_Init(This, 0, 0)

#pragma region Call vRefer
// Parameters:
//	This:	const ae2f_ds_Alloc_Refer*
// Returns:
//	const ae2f_ds_Alloc_Refer
#define ae2f_ds_Alloc_vRefer_Ref(This) ae2f_record_make(ae2f_struct ae2f_ds_Alloc_Refer, (This)->data, (This)->vRefer)

// Parameters:
//	This:	const ae2f_ds_Alloc_Refer*
//	Name:	Wanted Function Name
// Returns:
//	Function Pointer
// 
//	Good:
//		The Function Pointer with the given name.
//	Bad:
//		0
#define ae2f_ds_Alloc_vRefer_FindFunc(This, Name) ae2f_Macro_Compare_TakeMember(ae2f_Macro_Compare_TakeMember(This, vRefer, 0), Name, 0)

// Parameters:
//	This:	const ae2f_ds_Alloc_Refer*
//	sizebuff:	size_t*
// Returns:
//	ae2f_errint_t
//		[errGlobal]
#define ae2f_ds_Alloc_vRefer_getSize(This, sizebuff) (ae2f_ds_Alloc_vRefer_FindFunc(This, getSize) ? ae2f_ds_Alloc_vRefer_FindFunc(This, getSize)(This, sizebuff) : ae2f_errGlobal_IMP_NOT_FOUND)

// Parameters:
//	This:	const ae2f_ds_Alloc_Refer*
//	idx:	size_t
//	buff:	void*
//	elsize:	size_t
// Returns:
//	ae2f_errint_t
//		[errGlobal]
#define ae2f_ds_Alloc_vRefer_Read(This, idx, buff, elsize) (ae2f_ds_Alloc_vRefer_FindFunc(This, Read) ? ae2f_ds_Alloc_vRefer_FindFunc(This, Read)(This, idx, buff, elsize) : ae2f_errGlobal_IMP_NOT_FOUND)

// Parameters:
//	This:	ae2f_ds_Alloc_Refer*
//	idx:	size_t
//	src:	const void*
//	srcsize:	size_t
// Returns:
//	ae2f_errint_t
//		[errGlobal]
#define ae2f_ds_Alloc_vRefer_Write(This, idx, src, srcsize) (ae2f_ds_Alloc_vRefer_FindFunc(This, Write) ? ae2f_ds_Alloc_vRefer_FindFunc(This, Write)(This, idx, src, srcsize) : ae2f_errGlobal_IMP_NOT_FOUND)
#pragma endregion
#pragma region Call vOwner
#define ae2f_ds_Alloc_vOwner_Ref ae2f_ds_Alloc_vRefer_Ref
#define ae2f_ds_Alloc_vOwner_getSize ae2f_ds_Alloc_vRefer_getSize
#define ae2f_ds_Alloc_vOwner_Read ae2f_ds_Alloc_vRefer_Read
#define ae2f_ds_Alloc_vOwner_Write ae2f_ds_Alloc_vRefer_Write

// Parameters:
//	This:	const ae2f_ds_Alloc_Owner*
//	Name:	Wanted Function Name
// Returns:
//	Function Pointer
// 
//	Good:
//		The Function Pointer with the given name.
//	Bad:
//		0
#define ae2f_ds_Alloc_vOwner_FindFunc(This, Name) ae2f_Macro_Compare_TakeMember(ae2f_Macro_Compare_TakeMember(This, vOwner, 0), Name, 0)

// Parameters:
//	This:		ae2f_ds_Alloc_Owner*
//	NewSize:	size_t
// Returns:
//	ae2f_errint_t
//		[errGlobal]
#define ae2f_ds_Alloc_vOwner_Make(This, NewSize) (ae2f_ds_Alloc_vOwner_FindFunc(This, Make) ? ae2f_ds_Alloc_vOwner_FindFunc(This, Make)(This, NewSize) : ae2f_errGlobal_IMP_NOT_FOUND)

// Parameters:
//	This:		ae2f_ds_Alloc_Owner*
// Returns:
//	ae2f_errint_t
//		[errGlobal]
#define ae2f_ds_Alloc_vOwner_Del(This) (ae2f_ds_Alloc_vOwner_FindFunc(This, Del) ? ae2f_ds_Alloc_vOwner_FindFunc(This, Del)(This) : ae2f_errGlobal_IMP_NOT_FOUND)

// Parameters:
//	This:		ae2f_ds_Alloc_Owner*
//	NewSize:	size_t
// Returns:
//	ae2f_errint_t
//		[errGlobal]
#define ae2f_ds_Alloc_vOwner_reSize(This, NewSize) (ae2f_ds_Alloc_vOwner_FindFunc(This, reSize) ? ae2f_ds_Alloc_vOwner_FindFunc(This, reSize)(This, NewSize) : ae2f_errGlobal_IMP_NOT_FOUND)

/// <summary>
/// Allocates the memory.
/// Copies the data from [Source] to [This].
/// </summary>
/// <param name="This">Points the allocated memory</param>
/// <param name="Source">Copy Source</param>
/// <returns>[errGlobal]</returns>
ae2f_extern ae2f_errint_t ae2f_ds_Alloc_vOwner_Copy(ae2f_struct ae2f_ds_Alloc_Owner* This, const ae2f_struct ae2f_ds_Alloc_Refer* Source);
#pragma endregion
#endif

#if defined(__cplusplus) && !defined(ae2f_DataStructure_Allocator_hpp)
#define ae2f_DataStructure_Allocator_hpp

#include <ae2f/Macro/Cast.h>

namespace ae2f {
	namespace DataStructure {
		namespace Allocator {

			using vRefer = ae2f_ds_Alloc_vRefer;
			using vOwner = ae2f_ds_Alloc_vOwner;

			using rRefer = ae2f_ds_Alloc_Refer;
			using rOwner = ae2f_ds_Alloc_Owner;

			struct cOwner;
			struct cRefer;

			struct cRefer : public rRefer {
				friend cOwner;

				inline ae2f_errint_t Read(size_t i, void* dest, size_t destlen) const noexcept {
					return ae2f_ds_Alloc_vRefer_Read(this, i, dest, destlen);
				}

				inline ae2f_errint_t Write(size_t i, const void* src, size_t srclen) noexcept {
					return ae2f_ds_Alloc_vRefer_Write(this, i, src, srclen);
				}

				inline ae2f_errint_t Length(size_t* lenbuff) const noexcept {
					return ae2f_ds_Alloc_vRefer_getSize(this, lenbuff);
				}

				constexpr cRefer(const rRefer& r) noexcept : rRefer(r) {}
				constexpr cRefer(const rRefer&& r) noexcept : rRefer(r) {}

				constexpr cRefer(const cRefer& r) noexcept : rRefer(r) {}
				constexpr cRefer(const cRefer&& r) noexcept : rRefer(r) {}

				constexpr cRefer(const rOwner& r) noexcept : rRefer(ae2f_ds_Alloc_vRefer_Ref(&r)) {}
				constexpr cRefer(const rOwner&& r) noexcept : rRefer(ae2f_ds_Alloc_vRefer_Ref(&r)) {}

				constexpr cRefer(const cOwner& r) noexcept;

				constexpr cRefer() noexcept : rRefer{ 0, 0 } {}
			};
			struct cOwner : public rOwner {
				friend cRefer;
				inline ae2f_errint_t Read(size_t i, void* dest, size_t destlen) const noexcept {
					return ae2f_ds_Alloc_vRefer_Read(ae2f_union_cast(const rOwner*, const rRefer*, this), i, dest, destlen);
				}

				inline ae2f_errint_t Write(size_t i, const void* src, size_t srclen) noexcept {
					return ae2f_ds_Alloc_vRefer_Write(ae2f_union_cast(rOwner*, rRefer*, this), i, src, srclen);
				}

				inline ae2f_errint_t Length(size_t* lenbuff) const noexcept {
					return ae2f_ds_Alloc_vRefer_getSize(ae2f_union_cast(const rOwner*, const rRefer*, this), lenbuff);
				}

				inline ae2f_errint_t Resize(size_t NewLen) noexcept {
					return ae2f_ds_Alloc_vOwner_reSize(this, NewLen);
				}

				inline cOwner(
					size_t size, 
					const Allocator::vOwner* vOwn = 0, 
					const Allocator::vRefer* vRef = 0, 
					ae2f_errint_t* errcode = 0) noexcept {

					ae2f_errint_t  _err, &err = ae2f_Macro_Compare_TakeSelf(errcode, &_err)[0];
					if ((err = ae2f_ds_Alloc_vOwner_Init(this, vRef, vOwn)) != ae2f_errGlobal_OK)
						return;
					err = ae2f_ds_Alloc_vOwner_Make(this, size);
				}

				inline cOwner(
					const rOwner& r, 
					const Allocator::vOwner* vOwn = 0, 
					const Allocator::vRefer* vRef = 0, 
					ae2f_errint_t* errcode = 0
				) noexcept {
					auto err = ae2f_ds_Alloc_vOwner_Init(this, vRef, vOwn);
					if (err != ae2f_errGlobal_OK) {
						(errcode) && (errcode[0] = err);
						return;
					}
					
					err = ae2f_ds_Alloc_vOwner_Copy(this, reinterpret_cast<const rRefer*>(&r));
					(errcode) && (errcode[0] = err);
				}
				inline cOwner(
					const rOwner&& r,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
				) noexcept {
					auto err = ae2f_ds_Alloc_vOwner_Init(this, vRef, vOwn);
					if (err != ae2f_errGlobal_OK) {
						(errcode) && (errcode[0] = err);
						return;
					}

					err = ae2f_ds_Alloc_vOwner_Copy(this, reinterpret_cast<const rRefer*>(&r));
					(errcode) && (errcode[0] = err);
				}

				inline cOwner(
					const rRefer& r,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
				) noexcept {
					auto err = ae2f_ds_Alloc_vOwner_Init(this, vRef, vOwn);
					if (err != ae2f_errGlobal_OK) {
						(errcode) && (errcode[0] = err);
						return;
					}

					err = ae2f_ds_Alloc_vOwner_Copy(this, reinterpret_cast<const rRefer*>(&r));
					(errcode) && (errcode[0] = err);
				}

				inline cOwner(
					const rRefer&& r,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
				) noexcept {
					auto err = ae2f_ds_Alloc_vOwner_Init(this, vRef, vOwn);
					if (err != ae2f_errGlobal_OK) {
						(errcode) && (errcode[0] = err);
						return;
					}

					err = ae2f_ds_Alloc_vOwner_Copy(this, reinterpret_cast<const rRefer*>(&r));
					(errcode) && (errcode[0] = err);
				}

				inline cOwner(
					const cRefer& r, 
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0) noexcept
					: cOwner(static_cast<const rRefer&>(r), vOwn, vRef, errcode) {}
				
				inline cOwner(
					const cRefer&& r,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0) noexcept
					: cOwner(static_cast<const rRefer&>(r), vOwn, vRef, errcode) {}

				inline cOwner(
					const cOwner& r,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0) noexcept
					: cOwner(static_cast<const rOwner&>(r), vOwn, vRef, errcode) {}

				constexpr cOwner(ae2f_errint_t* errcode = 0) noexcept : rOwner{0, 0, 0}
				{
					(errcode) && (errcode[0] = ae2f_errGlobal_WRONG_OPERATION);
				}

				inline ~cOwner() noexcept {
					ae2f_ds_Alloc_vOwner_Del(this);
				}
			};

			constexpr cRefer::cRefer(const cOwner& r) noexcept : cRefer(ae2f_ds_Alloc_vRefer_Ref(&r)) {}
		}
	}
}

#endif // defined(__cplucpluc)