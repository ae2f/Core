#include "./Allocator.h"
#include <ae2f/Macro/errGlobal.hpp>

#if defined(__cplusplus) && !defined(ae2f_DataStructure_Allocator_hpp)
#define ae2f_DataStructure_Allocator_hpp

namespace ae2f {
	namespace DataStructure {
		namespace Allocator {

			using vRefer = ae2f_ds_Alloc_vRefer;
			using vOwner = ae2f_ds_Alloc_vOwner;

			using rRefer = ae2f_ds_Alloc_Refer;
			using rOwner = ae2f_ds_Alloc_Owner;

            struct xrOwner;

            struct cRefer : public rRefer {
                public:
				friend xrOwner;

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

				constexpr cRefer(const xrOwner& r) noexcept;

				constexpr cRefer() noexcept : rRefer{ 0, 0 } {}
			};
			struct xrOwner : public rOwner {
                public:
                friend cRefer;
				inline ae2f_errint_t Read(size_t i, void* dest, size_t destlen) const noexcept {
					return ae2f_ds_Alloc_vOwner_Read(this, i, dest, destlen);
				}

				inline ae2f_errint_t Write(size_t i, const void* src, size_t srclen) noexcept {
					return ae2f_ds_Alloc_vOwner_Write(this, i, src, srclen);
				}

				inline ae2f_errint_t Length(size_t* lenbuff) const noexcept {
					return ae2f_ds_Alloc_vOwner_getSize(this, lenbuff);
				}

				inline ae2f_errint_t Resize(size_t NewLen) noexcept {
					return ae2f_ds_Alloc_vOwner_reSize(this, NewLen);
				}

                inline ~xrOwner() noexcept {
                    Macro::gErrOccurredOnDeconstructor = (ae2f_ds_Alloc_vOwner_Del(this));
                }
                

                inline xrOwner(
					const rOwner& r, 
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
				) noexcept {
                    if(!(vOwn && vRef)) { vOwn = r.vOwner; vRef = r.vRefer; }

					auto err = ae2f_ds_Alloc_vOwner_Init(this, vRef, vOwn);
					if (err != ae2f_errGlobal_OK) {
						(errcode) && (errcode[0] = err);
						return;
					}
					
					err = ae2f_ds_Alloc_vOwner_Copy(this, &r);
					(errcode) && (errcode[0] = err);
				}

				inline xrOwner(
					const rOwner&& r,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
				) noexcept {
                    if(!(vOwn && vRef)) { vOwn = r.vOwner; vRef = r.vRefer; }

					auto err = ae2f_ds_Alloc_vOwner_Init(this, vRef, vOwn);
					if (err != ae2f_errGlobal_OK) {
						(errcode) && (errcode[0] = err);
						return;
					}

					err = ae2f_ds_Alloc_vOwner_Copy(this, &r);
					(errcode) && (errcode[0] = err);
				}

				inline xrOwner(
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

					err = ae2f_ds_Alloc_vOwner_Copy(this, &r);
					(errcode) && (errcode[0] = err);
				}

				inline xrOwner(
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

					err = ae2f_ds_Alloc_vOwner_Copy(this, &r);
					(errcode) && (errcode[0] = err);
				}

				inline xrOwner(
					const cRefer& r,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0) noexcept
					: xrOwner(static_cast<const rRefer&>(r), vOwn, vRef, errcode) {}
				
				inline xrOwner(
					const cRefer&& r,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0) noexcept
					: xrOwner(static_cast<const rRefer&>(r), vOwn, vRef, errcode) {}

				inline xrOwner(
					const xrOwner& r,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0) noexcept
					: xrOwner(static_cast<const rOwner&>(r), vOwn, vRef, errcode) {}
            };

            template<const vRefer* __vRef, const vOwner* __vOwn>
            struct vfDef {
                static constexpr Allocator::vRefer* ___vRef() noexcept { return __vRef; }
                static constexpr Allocator::vOwner* ___vOwn() noexcept { return __vOwn; }
            };

            template<const vRefer* __vRef, const vOwner* __vOwn>
            struct iOwner : public xrOwner, public vfDef<__vRef, __vOwn> {
                inline iOwner(
                    const Allocator::vOwner* vOwner = __vOwn,
                    const Allocator::vRefer* vRefer = __vRef,
                    ae2f_errint_t* perr = 0
                ) noexcept {
                    perr ? (perr[0] = ae2f_ds_Alloc_vOwner_Init(this, vRefer, vOwner)) : ae2f_ds_Alloc_vOwner_Init(this, vRefer, vOwner);
                }

				inline iOwner(
					size_t size = 1, 
					const Allocator::vOwner* vOwn = __vOwn,
					const Allocator::vRefer* vRef = __vRef,
					ae2f_errint_t* errcode = 0
                ) noexcept {
					ae2f_errint_t  _err, &err = ae2f_Macro_Compare_TakeSelf(errcode, &_err)[0];
					if ((err = ae2f_ds_Alloc_vOwner_Init(this, vRef, vOwn)) != ae2f_errGlobal_OK)
						return;
					err = ae2f_ds_Alloc_vOwner_reSize(this, size);
				}
			};

			constexpr cRefer::cRefer(const xrOwner& r) noexcept : cRefer(ae2f_ds_Alloc_vRefer_Ref(&r)) {}

            namespace cOwner {
                using Linear_t = iOwner<&ae2f_ds_Alloc_vRefer_cLinear, &ae2f_ds_Alloc_vOwner_cLinear>;
            }
		}
	}
}

#endif // defined(__cplucpluc)