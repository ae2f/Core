#include "./Alloc.h"

#if defined(__cplusplus) && !defined(ae2f_ds_Alloc_hpp)
#define ae2f_ds_Alloc_hpp

namespace ae2f {
	namespace Ds {
		namespace Alloc {
			namespace E_GetSize {
				constexpr ae2f_errint_t NCOPIED = ae2f_ds_Alloc_cRef_getSize_NCOPIED;
			};

			using vf = ae2f_ds_vAlloc;

			using rRefer = ae2f_ds_Alloc_cRef;
			using rOwner = ae2f_ds_Alloc_cOwn;

            struct xrOwner;

            struct cRefer : public rRefer {
                public:
				/// @param i The Index [in an unit of bytes] where the element to copy is.
				/// @param dest A pointer of buffer where the element to be copied.
				/// @param destlen The allocated size of the `lpBuff`.
				inline ae2f_errint_t Read(size_t i, void* dest, size_t destlen) const noexcept {
					return ae2f_ds_Alloc_cRef_Read(this, i, dest, destlen);
				}

				/// @param i The Index [in an unit of bytes] where the element to be overwritten.
				/// @param src A pointer of an element.
				/// @param srclen An allocated size of the `lpBuff`.
				inline ae2f_errint_t Write(size_t i, const void* src, size_t srclen) noexcept {
					return ae2f_ds_Alloc_cRef_Write(this, i, src, srclen);
				}

				/// @param lenbuff A pointer where the count of the array, as an unit of elements.
				/// @param elsizebuff A pointer where the size of the element.
				inline ae2f_errint_t Length(size_t* lenbuff, size_t* elsizebuff) const noexcept {
					return ae2f_ds_Alloc_cRef_getSize(this, lenbuff, elsizebuff);
				}

				static constexpr ae2f_errint_t Length_NCOPIED = ae2f_ds_Alloc_cRef_getSize_NCOPIED;

				constexpr cRefer(const rRefer& r) noexcept : rRefer(ae2f_ds_Alloc_cRef_Mk(&r)) {}
				constexpr cRefer(const rRefer&& r) noexcept : rRefer(ae2f_ds_Alloc_cRef_Mk(&r)) {}

				constexpr cRefer(const xrOwner& r) noexcept;

				constexpr cRefer() noexcept : rRefer{ 0, 0 } {}
			};
			
			struct xrOwner : public rOwner {
                public:
				/// @param i The Index [in an unit of bytes] where the element to copy is.
				/// @param dest A pointer of buffer where the element to be copied.
				/// @param destlen The allocated size of the `lpBuff`.
				inline ae2f_errint_t Read(size_t i, void* dest, size_t destlen) const noexcept {
					return ae2f_ds_Alloc_cRef_Read(this, i, dest, destlen);
				}

				/// @param i The Index [in an unit of bytes] where the element to be overwritten.
				/// @param src A pointer of an element.
				/// @param srclen An allocated size of the `lpBuff`.
				inline ae2f_errint_t Write(size_t i, const void* src, size_t srclen) noexcept {
					return ae2f_ds_Alloc_cRef_Write(this, i, src, srclen);
				}

				/// @param lenbuff A pointer where the count of the array, as an unit of elements.
				/// @param elsizebuff A pointer where the size of the element.
				inline ae2f_errint_t Length(size_t* lenbuff, size_t* elsizebuff) const noexcept {
					return ae2f_ds_Alloc_cRef_getSize(this, lenbuff, elsizebuff);
				}

				inline ae2f_errint_t Resize(size_t NewLen) noexcept {
					return ae2f_ds_Alloc_cOwn_ReSize(this, NewLen);
				}

				inline ae2f_errint_t ReConfig(size_t elcount, size_t elsize) {
					return ae2f_ds_Alloc_cOwn_ReConfig(this, elcount, elsize);
				}

                inline ~xrOwner() noexcept {
                    ae2f_errGlob_LastErr |= (ae2f_ds_Alloc_cOwn_Del(this));
                }

				inline ae2f_errint_t Copy(const rRefer& src) noexcept {
					return ae2f_ds_Alloc_cOwn_Cpy(this, &src);
				}

				inline ae2f_errint_t Copy(const rRefer&& src) noexcept {
					return ae2f_ds_Alloc_cOwn_Cpy(this, &src);
				}

				inline xrOwner(
					ae2f_errint_t* perr,
                    const ae2f_ds_vAlloc* imp
				) noexcept : rOwner() {
					perr = perr ? perr : &ae2f_errGlob_LastErr;
					perr[0] = ae2f_ds_Alloc_cOwn_Init(this, imp);
				}
            };

            template<const ae2f_ds_vAlloc* __imp>
            struct vfDef {
                static constexpr ae2f_ds_vAlloc* ___vRef() noexcept { return __imp; }
            };

            template<const ae2f_ds_vAlloc* __imp>
            struct iOwner : public xrOwner, public vfDef<__imp> {
                inline iOwner(
                    ae2f_errint_t* perr = 0
                ) noexcept : xrOwner(perr, __imp) {}
			};

			constexpr cRefer::cRefer(const xrOwner& r) noexcept : cRefer(ae2f_ds_Alloc_cRef_Mk(&r)) {}

            namespace cOwner {
                using Linear_t = iOwner<&ae2f_ds_vAlloc_cLinear>;
            }
		}
	}
}

#endif // defined(__cplucpluc)