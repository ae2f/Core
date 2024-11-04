/// @file
/// Helper header for ae2f/Ds/Arr.hpp
/// @warning 
/// This file has lack of definitions.

namespace ae2f { namespace Ds { namespace Arr {

    /// @warning
    /// Using this class directly may cause undefined behaviour. \n
    /// Using the binder instead is recommended.
    /// @brief 
    /// # This structure does not own the memory.
    ///
    /// Suggest the type is trivial. \n
    /// Therefore the element type will be [T] itself.
    /// @tparam T 
    /// Trivial data type
    template<typename T>
    struct __Refer<T, 1>
    :   public Alloc::cRefer,
        public __def<T> 
    {
        using _f = __def<T>;

        /// @brief
        /// Gets data from a class.
        /// @param index
        /// The Index [in an unit of bytes] where the element to copy is.
        /// @param perr
        /// The pointer to store the error state.
        /// @return 
        /// The element of index.
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpRead_t
        /// @see ae2f_ds_Alloc_cRef_Read
        /// @see ae2f::Ds::Alloc::cRefer::Read
        inline const typename _f::El_t Read(size_t index, ae2f_errint_t* perr = &ae2f_errGlob_LastErr) const noexcept {
            if(!perr) perr = &ae2f_errGlob_LastErr;

            T b[1];

            perr[0] |= Alloc::cRefer::Read(
                index * sizeof(T), 
                ae2f_reinterpret_cast(void*, b), 
                sizeof(T)
            );

            return b[0];
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param el The element to write.
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpWrite_t
        /// @see ae2f_ds_Alloc_cRef_Write
        /// @see ae2f::Ds::Alloc::cRefer::Write
        inline ae2f_errint_t Write(size_t idx, const typename _f::El_t& el) noexcept {
            return Alloc::cRefer::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param el The element to write.
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpWrite_t
        /// @see ae2f_ds_Alloc_cRef_Write
        /// @see ae2f::Ds::Alloc::cRefer::Write
        inline ae2f_errint_t Write(size_t idx, const typename _f::El_t&& el) noexcept {
            return Alloc::cRefer::Write(
                idx * sizeof(T),
                ae2f_reinterpret_cast(const void*, &el),
                sizeof(T)
            );
        }

        constexpr __Refer(const Alloc::rRefer& src) 
        : cRefer(src) {}

        constexpr __Refer(const Alloc::rRefer&& src) 
        : cRefer(src) {}
    };

    /// @warning
    /// Using this class directly may cause undefined behaviour. \n
    /// Using the binder instead is recommended.
    /// @brief 
    /// # This structure does not own the memory.
    ///
    /// Suggest the type is no trivial. \n
    /// Therefore the element type will be @ref ae2f::Ds::Arr::Pack<T>, in order to avoid the data destruction under wrong responsibility.
    /// @tparam T 
    /// Non-Trivial data type
    /// @see ae2f::Ds::Arr::Pack<T>
    template<typename T>
    struct __Refer<T, 0>
    :   public Alloc::cRefer,
        public __def<Pack<T>> 
    {
        using _f = __def<Pack<T>>;

        /// @brief
        /// Gets data from a class.
        /// @param index
        /// The Index [in an unit of bytes] where the element to copy is.
        /// @param perr
        /// The pointer to store the error state.
        /// @return 
        /// The element of index.
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpRead_t
        /// @see ae2f_ds_Alloc_cRef_Read
        /// @see ae2f::Ds::Alloc::cRefer::Read
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

        /// @brief
        /// Sets data to a class.
        /// @tparam Args 
        /// Arguments datatype.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param args Arguments to build the element to write.
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID \n
        /// @ref eRef::EL_NON_VALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpWrite_t
        /// @see ae2f_ds_Alloc_cRef_Write
        /// @see ae2f::Ds::Alloc::cRefer::Write
        template<typename... Args>
        inline ae2f_errint_t Write(size_t idx, Args&& ...args) noexcept {
            if(!_ae2f_ds_Alloc_FndFun(ae2f_static_cast(Alloc::rRefer*, this), Write)) {
                return ae2f_errGlob_IMP_NOT_FOUND;
            }

            ae2f_errint_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[0] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            if(el->isvalid()) {
                el->Obj.~T();
            }
            new(el->c) T(args...);
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpWrite_t
        /// @see ae2f_ds_Alloc_cRef_Write
        /// @see ae2f::Ds::Alloc::cRefer::Write
        inline ae2f_errint_t Write(size_t idx) noexcept {
            if(!_ae2f_ds_Alloc_FndFun(ae2f_static_cast(Alloc::rRefer*, this), Write)) {
                return ae2f_errGlob_IMP_NOT_FOUND;
            }

            ae2f_errint_t code[1] = { ae2f_errGlob_OK };
            typename _f::El_t el[1] = { Read(idx, code) };

            if(code[0] & eRef::EL_NON_VALID) {
                if(!(code[0] & ae2f_errGlob_DONE_HOWEV))
                return code[0];
            }

            if(el->isvalid()) el->Obj.~T();
            new(el->c) T();
            el->_isvalid() = 1;

            return Alloc::xrOwner::Write(
                idx * _f::ElSize, 
                ae2f_reinterpret_cast(void*, el->c), 
                _f::ElSize
            );
        }

#pragma endregion
        constexpr __Refer(const __Refer<T, 0>& src)
        : cRefer(src) {}

        constexpr __Refer(const __Refer<T, 0>&& src)
        : cRefer(src) {}

        constexpr __Refer(const __Owner<T, 0>& src)
        : cRefer(src) {}

        constexpr __Refer(const __Owner<T, 0>&& src)
        : cRefer(src) {}
    };


    /// @brief 
    /// The binder for [__Refer].
    /// @tparam T 
    /// Trivial data type
    template<typename T>
    using cRefer = __Refer<T, std::is_trivial<T>::value>;
 
}}}