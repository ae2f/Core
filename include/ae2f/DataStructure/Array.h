#if !defined(ae2f_DataStructure_Array_h)
#define ae2f_DataStructure_Array_h
#include "Allocator.h"


typedef int ae2f_ds_Arr_Compared_t; 

// Returns:
//	Negative: l < r
//	0: l == r
//	Positive: l > r
typedef ae2f_ds_Arr_Compared_t(*ae2f_ds_Arr_fpElCmp_t)(const void* l, const void* r);

// they are same
#define ae2f_ds_Arr_EQUAL		ae2f_static_cast(ae2f_ds_Arr_Compared_t, 0)

// right is lesser
#define ae2f_ds_Arr_RIGHT_UNIT	ae2f_static_cast(ae2f_ds_Arr_Compared_t, 1)

// left is lesser
#define ae2f_ds_Arr_LEFT_UNIT	ae2f_static_cast(ae2f_ds_Arr_Compared_t, -1)


// Failed to find the wanted value.
// Your array might have not been sorted finely.
#define ae2f_ds_Arr_BSearch_NOT_FOUND ae2f_errGlobal_LMT

/// <summary>
/// Finds the element [wanted] via binary search.
/// </summary>
/// <param name="arr">
/// Array to see.
/// It must be sorted.
/// </param>
/// <param name="wanted">The element which is wanted.</param>
/// <param name="elsize">Suggested element size</param>
/// <param name="fpElCmp">
/// Comparing function:
/// comparing will be proceed as: fpElCmp(element, wanted);
/// </param>
/// <param name="out">Buffer where the Index may be stored</param>
/// <returns>[ae2f_errGlobal], [ae2f_ds_Arr_BSearch]</returns>
ae2f_extern ae2f_errint_t ae2f_ds_Arr_BSearch(
	const ae2f_struct ae2f_ds_Alloc_Refer* arr,
	const void* wanted,
	size_t elsize,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp,
	size_t* out
);

/// <summary>
/// Order the arr via quick sort.
/// </summary>
/// <param name="arr">An array to sort</param>
/// <param name="elsize">Size suggestion for each element</param>
/// <param name="fpElCmp">
/// Comparing function:
/// comparing will process as: fpElCmp(element, target);
/// </param>
/// <returns>[ae2f_errGlobal]</returns>
ae2f_extern ae2f_errint_t ae2f_ds_Arr_QSort(
	ae2f_struct ae2f_ds_Alloc_Refer* arr,
	size_t elsize,
	const ae2f_ds_Arr_fpElCmp_t fpElCmp
);

#endif // !defined(ae2f_DataStructure_Array_h)


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

			template<typename T, class Alloc_t, bool optIsallocator, bool optIsowner>
			struct imp_cArray;

			template<typename T, class Alloc_t>
			struct imp_cArray<T, Alloc_t, 0, 0> {
				constexpr const Array::uElement<T> Read(size_t idx, ae2f_errint_t* perr = 0) const noexcept {
					(perr) && (perr[0] = ae2f_errGlobal_IMP_NOT_FOUND);
					return Array::uElement<T>();
				}

				constexpr ae2f_errint_t Write(size_t idx, const T&& element) noexcept {
					return ae2f_errGlobal_IMP_NOT_FOUND;
				}

				constexpr ae2f_errint_t Write(size_t idx, const T& element) noexcept {
					return ae2f_errGlobal_IMP_NOT_FOUND;
				}

				constexpr size_t Count(ae2f_errint_t* perr = 0) noexcept {
					(perr) && (perr[0] = ae2f_errGlobal_IMP_NOT_FOUND);
					return 0;
				}
			};

			template<typename T, class Alloc_t>
			struct imp_cArray<T, Alloc_t, 0, 1> 
				: public imp_cArray<T, Alloc_t, 0, 0> {};

			template<typename T, class Alloc_t>
			struct global_imp_cArray : public Alloc_t {
				inline const Array::uElement<T> Read(size_t idx, ae2f_errint_t* perr = 0) const noexcept {
					using namespace Array;
					uElement<T> rtn;
					auto err = Alloc_t::Read(idx * def<T>::elsize, rtn.__buff, def<T>::elsize);

					if (def<T>::hasDestructor && !rtn.isAvailable() && err == ae2f_errGlobal_OK) {
						err = ae2f_errGlobal_PTR_IS_NULL;
					}

					(perr) && (perr[0] = err);
					return rtn;
				} 
				inline ae2f_errint_t Write(size_t idx, const T&& element) noexcept {
					using namespace Array;
					ae2f_errint_t err;
					uElement<T> el = this->Read(idx, &err);

					if (err == ae2f_errGlobal_OK && def<T>::hasDestructor) {
						el.obj.~T();
					}

					el.obj = element;
					if (def<T>::hasDestructor) el.isAvailable() = 1;
					return Alloc_t::Write(idx * def<T>::elsize, el.__buff, def<T>::elsize);
				}
				inline ae2f_errint_t Write(size_t idx, const T& element) noexcept {
					using namespace Array;
					ae2f_errint_t err;
					uElement<T> el = this->Read(idx, &err);

					if (err == ae2f_errGlobal_OK && def<T>::hasDestructor) {
						el.obj.~T();
					}

					el.obj = element;
					if (def<T>::hasDestructor) el.isAvailable() = 1;
					return Alloc_t::Write(idx * def<T>::elsize, el.__buff, def<T>::elsize);
				}
				inline size_t Count(ae2f_errint_t* perr = 0) const noexcept {
					size_t size;
					ae2f_errint_t err = Alloc_t::Length(&size);
					(perr) && (perr[0] = err);
					return size / Array::def<T>::elsize;
				}

				constexpr global_imp_cArray(const Alloc_t& a) noexcept : Alloc_t(a) {}
				constexpr global_imp_cArray(const Alloc_t&& a) noexcept : Alloc_t(a) {}
			};

			template<typename T, class Alloc_t>
			struct imp_cArray<T, Alloc_t, 1, 0> : public global_imp_cArray<T, Alloc_t> {
				constexpr imp_cArray(const global_imp_cArray<T, Alloc_t>& arr) noexcept :
					global_imp_cArray<T, Alloc_t>(Alloc_t(arr)) {}

				constexpr imp_cArray(const global_imp_cArray<T, Alloc_t>&& arr) noexcept :
					global_imp_cArray<T, Alloc_t>(Alloc_t(arr)) {}
			};

			template<typename T, class Alloc_t>
			struct imp_cArray<T, Alloc_t, 1, 1> : public global_imp_cArray<T, Alloc_t> {
				inline imp_cArray(
					const global_imp_cArray<T, Alloc_t>& arr,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
				) noexcept : 
					global_imp_cArray<T, Alloc_t>(Alloc_t(arr, vOwn, vRef, errcode))
				{}

				inline imp_cArray(
					size_t count,
					const Allocator::vOwner* vOwn = 0,
					const Allocator::vRefer* vRef = 0,
					ae2f_errint_t* errcode = 0
				) noexcept : 
					global_imp_cArray<T, Alloc_t>(Alloc_t(count* def<T>::elsize, vOwn, vRef, errcode))
				{}


				inline ~imp_cArray() noexcept {
					ae2f_errint_t err;
					size_t ct = this->Count(&err);

					if (def<T>::hasDestructor && ct == ae2f_errGlobal_OK)
						for (size_t i = 0; i < ct; i++) {
							uElement<T> eltokill = global_imp_cArray<T, Alloc_t>::Read(i, &err);
							if (err == ae2f_errGlobal_OK && eltokill.isAvailable()) {
								eltokill.obj.~T();
							}
						}
				}
			};
		}

		template<typename T, class Alloc_t = Allocator::cOwner>
		using cArray = Array::imp_cArray<
			T, Alloc_t,
			std::is_base_of<Allocator::cOwner, Alloc_t>::value || std::is_base_of<Allocator::cRefer, Alloc_t>::value,
			std::is_base_of<Allocator::cOwner, Alloc_t>::value
		>;

		namespace Array {
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
			inline size_t BSearch(
				const cArray<T, Allocator::cRefer>& arr,
				T wanted,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp = __compare<T>,
				ae2f_errint_t* errbuff = 0
			) {
				size_t sizebuff;
				ae2f_errint_t err = ::ae2f_ds_Arr_BSearch(static_cast<const Allocator::rRefer*>(&arr), &wanted, Array::def<T>::elsize, fpElCmp, &sizebuff);
				errbuff && (errbuff[0] = err);
				return sizebuff;
			}

			template<typename T>
			inline size_t BSearch(
				const cArray<T, Allocator::cRefer>&& arr,
				T wanted,
				ae2f_errint_t* errbuff = 0,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp = __compare<T>
			) {
				size_t sizebuff;
				ae2f_errint_t err = ::ae2f_ds_Arr_BSearch(static_cast<const Allocator::rRefer*>(&arr), &wanted, Array::def<T>::elsize, fpElCmp, &sizebuff);
				errbuff && (errbuff[0] = err);
				return sizebuff;
			}

			template<typename T>
			inline size_t BSearch(
				const cArray<T, Allocator::cOwner>& arr,
				T wanted,
				ae2f_errint_t* errbuff = 0,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp = __compare<T>
			) {
				size_t sizebuff;
				ae2f_errint_t err = BSearch(static_cast<const Allocator::rOwner*>(&arr), &wanted, Array::def<T>::elsize, fpElCmp, &sizebuff);
				errbuff && (errbuff[0] = err);
				return sizebuff; 
			}

			template<typename T>
			inline size_t BSearch(
				const cArray<T, Allocator::cOwner>&& arr,
				T wanted,
				ae2f_errint_t* errbuff = 0,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp = __compare<T>
			) {
				size_t sizebuff;
				ae2f_errint_t err = BSearch(static_cast<const Allocator::rOwner*>(&arr), &wanted, Array::def<T>::elsize, fpElCmp, &sizebuff);
				errbuff && (errbuff[0] = err);
				return sizebuff;
			}

			template<typename T>
			inline ae2f_errint_t QSort(
				cArray<T, Allocator::cRefer>& arr,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp = __compare<T>
			) {
				return ::ae2f_ds_Arr_QSort(&arr, def<T>::elsize, fpElCmp);
			}

			template<typename T>
			inline ae2f_errint_t QSort(
				cArray<T, Allocator::cRefer>&& arr,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp = __compare<T>
			) {
				return ::ae2f_ds_Arr_QSort(&arr, def<T>::elsize, fpElCmp);
			}

			template<typename T>
			inline ae2f_errint_t QSort(
				cArray<T, Allocator::cOwner>& arr,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp = __compare<T>
			) {
				return ::ae2f_ds_Arr_QSort(reinterpret_cast<ae2f_ds_Alloc_Refer*>(&arr), def<T>::elsize, fpElCmp);
			}

			template<typename T>
			inline ae2f_errint_t QSort(
				cArray<T, Allocator::cOwner>&& arr,
				const ae2f_ds_Arr_fpElCmp_t fpElCmp = __compare<T>
			) {
				return ::ae2f_ds_Arr_QSort(reinterpret_cast<ae2f_ds_Alloc_Refer*>(&arr), def<T>::elsize, fpElCmp);
			}
		}
	}
}

#endif // defined(__cplusplus)
