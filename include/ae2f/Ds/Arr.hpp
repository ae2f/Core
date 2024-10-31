#include "Arr.h"

#if !defined(ae2f_ds_Arr_hpp) && defined(__cplusplus)
#define ae2f_ds_Arr_hpp

#include "Alloc.hpp"
#include <type_traits>

namespace ae2f {
namespace Ds {
namespace Arr {
    template<typename T, bool NIsTrivial>
    struct __Refer {};

    template<typename T, bool NIsTrivial>
    struct __Owner {};

    namespace eRef {
        /// @return 
        /// ae2f_errGlob_WRONG_OPERATION | ae2f_errGlob_DONE_HOWEV
        constexpr ae2f_errint_t EL_NON_VALID = 80;
    };

    template<typename __el_t, const size_t __elsize>
    struct __def {
        public:
        static constexpr size_t ElSize = __elsize;
        using El_t = __el_t;
        using _f = __def<__el_t, __elsize>;
    };

    template<typename T>
    union Pack {
        private:
        friend __Refer<T, 0>;
        friend __Owner<T, 0>;
        uint8_t c[sizeof(T) + 1];

        constexpr uint8_t& _isvalid() noexcept {
            return c[sizeof(T)];
        }

        constexpr const uint8_t& _isvalid() const noexcept {
            return c[sizeof(T)];
        }

        public:
        T Obj;

        constexpr bool isvalid() const noexcept {
            return c[sizeof(T)];
        }
        
        template<int d = 0>
        inline Pack() noexcept : c{0, } {}
        inline ~Pack() {}
    };



    #pragma region Ref
    template<typename T>
    struct __Refer<T, 1>
    :   public Alloc::cRefer,
        public __def<T, sizeof(T)> 
    {
        using _f = __def<T, sizeof(T)>;

        inline const typename _f::El_t Read(size_t index, ae2f_errint_t* perr = 0) const noexcept {
            if(!perr) perr = &ae2f_errGlob_LastErr;

            T b[1];

            perr[0] = Alloc::cRefer::Read(
                index * sizeof(T), 
                ae2f_reinterpret_cast(void*, b), 
                sizeof(T)
            );

            return b[0];
        }

        inline ae2f_errint_t Write(size_t idx, const typename _f::El_t& el) noexcept {
            return Alloc::cRefer::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }

        inline ae2f_errint_t Write(size_t idx, const typename _f::El_t&& el) noexcept {
            return Alloc::cRefer::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }
    };

    template<typename T>
    struct __Refer<T, 0>
    :   public Alloc::cRefer,
        public __def<Pack<T>, sizeof(T) + 1> 
    {
        using _f = __def<Pack<T>, sizeof(T) + 1>;

        inline const typename _f::El_t Read(size_t index, ae2f_errint_t* perr = 0) const noexcept {
            if(!perr) perr = &ae2f_errGlob_LastErr;

            typename _f::El_t b[1];

            perr[0] |= Alloc::cRefer::Read(
                index * _f::ElSize, 
                ae2f_reinterpret_cast(void*, b), 
                _f::ElSize
            );

            if(!b->isvalid())
            perr[0] |= eRef::EL_NON_VALID;

            return b[0];
        }

#pragma region non_trivial writing

        template<typename... Args>
        inline ae2f_errint_t Write(size_t idx, Args ...args) noexcept {
            ae2f_errint_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(el->isvalid()) el->Obj.~T();

            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[1] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            new(el->c) T(args...);
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

        inline ae2f_errint_t Write(size_t idx) noexcept {
            ae2f_errint_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(el->isvalid()) el->Obj.~T();
            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[0] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            new(el->c) T();
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

#pragma endregion
    };

    template<typename T>
    struct cRefer : public __Refer<T, std::is_trivial<T>::value> {
        public:
        using self_t = __Refer<T, std::is_trivial<T>::value>;

        inline cRefer(const self_t& a) noexcept
        : self_t(a) {}
    };
    #pragma endregion

    #pragma region Own
    template<typename T>
    struct __Owner<T, 1>
    :   public Alloc::xrOwner,
        public __def<T, sizeof(T)> 
    {
        using _f = __def<T, sizeof(T)>;

        inline const typename _f::El_t Read(size_t index, ae2f_errint_t* perr = 0) const noexcept {
            if(!perr) perr = &ae2f_errGlob_LastErr;

            T b[1];

            perr[0] = Alloc::xrOwner::Read(
                index * sizeof(T), 
                ae2f_reinterpret_cast(void*, b), 
                sizeof(T)
            );

            return b[0];
        }

        inline ae2f_errint_t Write(size_t idx, const typename _f::El_t& el) noexcept {
            return Alloc::xrOwner::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }

        inline ae2f_errint_t Write(size_t idx, const typename _f::El_t&& el) noexcept {
            return Alloc::xrOwner::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }

        /// @return  ae2f_errGlob_IMP_NOT_FOUND
        constexpr ae2f_errint_t ReConfig(size_t elcount, size_t elsize) {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        /// @return  ae2f_errGlob_IMP_NOT_FOUND
        constexpr ae2f_errint_t Copy(const Alloc::rRefer& src) noexcept {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        /// @return  ae2f_errGlob_IMP_NOT_FOUND
        constexpr ae2f_errint_t Copy(const Alloc::rRefer&& src) noexcept {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        inline __Owner(
            ae2f_errint_t* perr,
            const ae2f_ds_vAlloc* imp
        ) : Alloc::xrOwner(perr, imp) {}
    };

    template<typename T>
    struct __Owner<T, 0>
    :   public Alloc::xrOwner,
        public __def<Pack<T>, sizeof(T) + 1> 
    {
        using _f = __def<Pack<T>, sizeof(T) + 1>;

        inline const typename _f::El_t Read(size_t index, ae2f_errint_t* perr = 0) const noexcept {
            if(!perr) perr = &ae2f_errGlob_LastErr;

            typename _f::El_t b[1];

            perr[0] |= Alloc::xrOwner::Read(
                index * _f::ElSize, 
                ae2f_reinterpret_cast(void*, b), 
                _f::ElSize
            );

            if(!b->isvalid())
            perr[0] |= eRef::EL_NON_VALID;

            return b[0];
        }

#pragma region non_trivial writing

        template<typename... Args>
        inline ae2f_errint_t Write(size_t idx, Args ...args) noexcept {
            ae2f_errint_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(el->isvalid()) el->Obj.~T();

            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[1] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            new(el->c) T(args...);
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

        inline ae2f_errint_t Write(size_t idx) noexcept {
            ae2f_errint_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(el->isvalid()) el->Obj.~T();
            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[0] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            new(el->c) T();
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

#pragma endregion
        
        inline ~__Owner() {
            size_t a[2] = {0, 0};
            ae2f_errGlob_LastErr |= this->Length(a, a+1);

            a[0] = (a[1] * a[0]) / this->ElSize;

            for(size_t i = 0; i < a[0]; i++) {
                Pack<T> t = this->Read(i, &ae2f_errGlob_LastErr);
                if(t.isvalid()) t.Obj.~T();
            }
        }

        // resizing for arr
        inline ae2f_errint_t Resize(size_t nCount) noexcept {
            size_t a, b; ae2f_errint_t err = ae2f_errGlob_OK;
            err |= xrOwner::Length(&a, &b);
            if(err) return err;

            a = (b * a) / _f::ElSize;

            for(size_t i = nCount; i < a; i++) {
                typename _f::El_t read = Read(i, &err);
                if(err) return err;
                if(read._isvalid()) {
                    read.Obj.~T();
                }
            }

            return xrOwner::ReConfig(nCount, _f::ElSize);
        }

        constexpr ae2f_errint_t ReConfig(size_t elcount, size_t elsize) {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        constexpr ae2f_errint_t Copy(const Alloc::rRefer& src) noexcept {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        constexpr ae2f_errint_t Copy(const Alloc::rRefer&& src) noexcept {
            return ae2f_errGlob_IMP_NOT_FOUND;
        }

        inline __Owner(
            ae2f_errint_t* perr,
            const ae2f_ds_vAlloc* imp
        ) : Alloc::xrOwner(perr, imp) {}
    };

    template<typename T>
    struct xrOwner : public __Owner<T, std::is_trivial<T>::value> {
        public:
        using self_t = __Owner<T, std::is_trivial<T>::value>;

        inline xrOwner(
            ae2f_errint_t* perr,
            const ae2f_ds_vAlloc* imp
        ) noexcept
        : self_t(perr, imp) {}
    };


    #pragma endregion

    template<typename T, const ae2f_ds_vAlloc* __imp>
    struct iOwner : public xrOwner<T>, public Alloc::vfDef<__imp> {
        inline iOwner(
            ae2f_errint_t* perr = 0
        ) noexcept : xrOwner<T>(perr, __imp) {}
    };

    namespace cOwner {
        template<typename T>
        using Linear_t = iOwner<T, &ae2f_ds_vAlloc_cLinear>;
    }
}
}
}

#endif