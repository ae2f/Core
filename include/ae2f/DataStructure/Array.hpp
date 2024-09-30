#include "./Allocator.hpp"
#include "./Array.h"

#if defined(__cplusplus) && !defined(ae2f_DataStructure_Array_hpp)
#define ae2f_DataStructure_Array_hpp

#include <type_traits>

namespace ae2f {
	namespace DataStructure {
		namespace Array {
			template<typename T>
			struct def {
				static constexpr bool hasDestructor = (!std::is_trivial<T>::value);
				static constexpr size_t elsize = sizeof(T) + hasDestructor;
			};

			template<typename T>
			union uElement {
			private:
				char buff[def<T>::elsize];
			public:
				T obj;
				char __buff[1];
				constexpr char& isAvailable() noexcept {
					return buff[def<T>::elsize - 1];
				}
				constexpr const bool isAvailable() const noexcept {
					return buff[def<T>::elsize - 1];
				}
				inline ~uElement() noexcept {}
				constexpr uElement(bool toKill = false) noexcept : buff{ 0, } {
					if (def<T>::hasDestructor)
						isAvailable() = toKill;
				}
				inline uElement(const T&& Class, bool toKill = true) noexcept : obj(Class) {
					if (def<T>::hasDestructor)
						isAvailable() = toKill;
				}
				inline uElement(const T& Class, bool toKill = true) noexcept : obj(Class) {
					if (def<T>::hasDestructor)
						isAvailable() = toKill;
				}
				inline uElement(const uElement& a) noexcept : uElement(a.obj, def<T>::hasDestructor && a.isAvailable()) {}
				inline uElement(const uElement&& a) noexcept : uElement(a.obj, def<T>::hasDestructor && a.isAvailable()) {}
			};


            template<typename T>
            struct xrOwner;

            template<typename T>
            struct cRefer {
                Allocator::cRefer a;

                inline cRefer(const cRefer<T>& a) noexcept : a(a.a) {}
                inline cRefer(const cRefer<T>&& a) noexcept : a(a.a) {}
                inline cRefer(const xrOwner<T>& a) noexcept;

                inline uElement<T> Read(size_t i, ae2f_errint_t* perr) const noexcept {
                    uElement<T> __el;
                    if(perr) perr[0] = a.Read(i * def<T>::elsize, __el.buff, def<T>::elsize);
                    return __el;
                }

                inline uElement<T> Write(size_t i, const T& el, ae2f_errint_t* perr) noexcept {
                    uElement<T> __el;
                    __el.obj = el;
                    if(def<T>::hasDestructor) __el.isAvailable() = 1;
                    if(perr) perr[0] = a.Read(i * def<T>::elsize, __el.buff, def<T>::elsize);
                }

                inline uElement<T> Write(size_t i, const T&& el, ae2f_errint_t* perr) noexcept {
                    uElement<T> __el;
                    __el.obj = el;
                    if(def<T>::hasDestructor) __el.isAvailable() = 1;
                    if(perr) perr[0] = a.Read(i * def<T>::elsize, __el.buff, def<T>::elsize);
                }

                inline size_t Count(ae2f_errint_t* perr) const {
                    size_t __size;
                    perr ? (perr[0] = this->a.Length(&__size)) : this->a.Length(&__size);
                    return __size;
                }
            };


            template<typename T>
            struct xrOwner {
                Allocator::xrOwner a;

#pragma region Refer Momoent
                inline uElement<T> Read(size_t i, ae2f_errint_t* perr) const noexcept {
                    uElement<T> __el;
                    if(perr) perr[0] = a.Read(i * def<T>::elsize, __el.buff, def<T>::elsize);
                    return __el;
                }

                inline uElement<T> Write(size_t i, const T& el, ae2f_errint_t* perr) noexcept {
                    uElement<T> __el;
                    __el.obj = el;
                    if(def<T>::hasDestructor) __el.isAvailable() = 1;
                    if(perr) perr[0] = a.Read(i * def<T>::elsize, __el.buff, def<T>::elsize);
                }

                inline uElement<T> Write(size_t i, const T&& el, ae2f_errint_t* perr) noexcept {
                    uElement<T> __el;
                    __el.obj = el;
                    if(def<T>::hasDestructor) __el.isAvailable() = 1;
                    if(perr) perr[0] = a.Read(i * def<T>::elsize, __el.buff, def<T>::elsize);
                }

                inline size_t Count(ae2f_errint_t* perr) const {
                    size_t __size;
                    perr ? (perr[0] = this->a.Length(&__size)) : this->a.Length(&__size);
                    return __size;
                }
#pragma endregion
                inline ae2f_errint_t SetCount(size_t Size) noexcept {
                    ae2f_errint_t perr;
                    size_t count;

                    if(def<T>::hasDestructor) {
                        count = this->Count(&perr);

                        if(perr != ae2f_errGlobal_OK)
                            return perr;

                        for(size_t i = Size; i < count; i++) {
                            const uElement<T> el = this->Read(i, &perr);
                            if(perr != ae2f_errGlobal_OK) return perr;
                            if(el.isAvailable()) { el.obj.~T(); }
                        }
                    }

                    return a.Resize(Size);
                }

                inline ~xrOwner() noexcept {
                    size_t count;

                    if(def<T>::hasDestructor) {
                        count = this->Count(&Macro::gErrOccurredOnDeconstructor);
                        if(ae2f_errGlobal_OK != Macro::gErrOccurredOnDeconstructor) return;

                        for(size_t i = 0; i < count; i++) {
                            const uElement<T> el = this->Read(i, &Macro::gErrOccurredOnDeconstructor);
                            if(Macro::gErrOccurredOnDeconstructor != ae2f_errGlobal_OK) return;
                            if(el.isAvailable()) el.obj.~T();
                        }
                    }
                }

                inline xrOwner(
                    const xrOwner<T>& owner,
                    const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
                ) noexcept : a(owner.a, vOwn, vRef, errcode) {}

                inline xrOwner(
                    const cRefer<T>& owner,
                    const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
                ) noexcept : a(owner.a, vOwn, vRef, errcode) {}

                inline xrOwner(
                    const cRefer<T>&& owner,
                    const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
                ) noexcept : a(owner.a, vOwn, vRef, errcode) {}
            };

            template<typename T, const Allocator::vOwner* own, const Allocator::vRefer* ref>
            struct iOwner : public xrOwner<T>, Allocator::vfDef<ref, own> {
                inline iOwner(
                    const Allocator::vOwner* vOwner = __vOwn,
                    const Allocator::vRefer* vRefer = __vRef,
                    ae2f_errint_t* perr = 0
                ) noexcept {
                    perr ? (perr[0] = ae2f_ds_Alloc_vOwner_Init(&this->a, vRefer, vOwner)) : ae2f_ds_Alloc_vOwner_Init(&this->a, vRefer, vOwner);
                }

                inline iOwner(
					size_t size = 1, 
					const Allocator::vOwner* vOwn = __vOwn,
					const Allocator::vRefer* vRef = __vRef,
					ae2f_errint_t* errcode = 0
                ) noexcept {
					ae2f_errint_t  _err, &err = ae2f_Macro_Compare_TakeSelf(errcode, &_err)[0];
					if ((err = ae2f_ds_Alloc_vOwner_Init(&this->a, vRef, vOwn)) != ae2f_errGlobal_OK) return;
					err = ae2f_ds_Alloc_vOwner_reSize(&this->a, size * def<T>::hasDestructor);
				}
            };

            template<typename T>
            inline cRefer<T>::cRefer(const xrOwner<T>& a)  noexcept : a(a.a) {}

            namespace cOwner {
                template<typename T>
                using Linear_t = iOwner<T, &ae2f_ds_Alloc_vOwner_cLinear, &ae2f_ds_Alloc_vRefer_cLinear>;
            }
        }

		namespace Array {
            inline ae2f_errint_t BSearch(
				const Allocator::rRefer* arr,
				const void* wanted,
				size_t elsize,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp,
				size_t* out
			) {
				return ::ae2f_ds_Arr_BSearch((arr), wanted, elsize, fpElCmp, out);
			}

			inline ae2f_errint_t BSearch(
				const Allocator::rOwner* arr,
				const void* wanted,
				size_t elsize,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp,
				size_t* out
			) {
				return ::ae2f_ds_Arr_BSearch(reinterpret_cast<const Allocator::rRefer*>(arr), wanted, elsize, fpElCmp, out);
			}

			template<typename T>
			static ae2f_ds_Arr_Compared_t __compare(const void* a, const void* b) {
				return 
					ae2f_reinterpret_cast(const T*, a)[0] == ae2f_reinterpret_cast(const T*, b)[0] ? 
					ae2f_ds_Arr_EQUAL : 
					ae2f_reinterpret_cast(const T*, a)[0] < ae2f_reinterpret_cast(const T*, b)[0] 
					? ae2f_ds_Arr_LEFT_UNIT : ae2f_ds_Arr_RIGHT_UNIT;
			}

            template<typename T>
            inline ae2f_errint_t BSearch(
                const xrOwner<T>* arr,
                const T& wanted,
                const ae2f_ds_Arr_fpElCmp_t fpElCmp,
                size_t* out
            ) { return BSearch(&arr->a, wanted, def<T>::elsize, __compare); }

            template<typename T>
            inline ae2f_errint_t BSearch(
                const xrOwner<T>* arr,
                const T&& wanted,
                const ae2f_ds_Arr_fpElCmp_t fpElCmp,
                size_t* out
            ) { return BSearch(&arr->a, wanted, def<T>::elsize, __compare); }


            template<typename T>
            inline ae2f_errint_t BSearch(
                const cRefer<T>* arr,
                const T& wanted,
                const ae2f_ds_Arr_fpElCmp_t fpElCmp,
                size_t* out
            ) { return BSearch(&arr->a, wanted, def<T>::elsize, __compare); }

            template<typename T>
            inline ae2f_errint_t BSearch(
                const cRefer<T>* arr,
                const T&& wanted,
                const ae2f_ds_Arr_fpElCmp_t fpElCmp,
                size_t* out
            ) { return BSearch(&arr->a, wanted, def<T>::elsize, __compare); }

            
            inline ae2f_errint_t QSort(
                const Allocator::rRefer* arr,
                size_t elsize,
	            const ae2f_ds_Arr_fpElCmp_t fpElCmp
            ) {
                return QSort(arr, elsize, fpElCmp);
            }

            inline ae2f_errint_t QSort(
                const Allocator::rOwner* arr,
                size_t elsize,
	            const ae2f_ds_Arr_fpElCmp_t fpElCmp
            ) {
                return QSort(arr, elsize, fpElCmp);
            }
		}
	}
}

#endif // defined(__cplusplus)