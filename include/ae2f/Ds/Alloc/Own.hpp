/// @file
/// @warning
/// This file is a helper header of @ref ae2f/Ds/Alloc.hpp \n
/// Few definitions may lack.

namespace ae2f { namespace Ds { namespace Alloc {

    /// @brief
    /// # This structure owns the memory.
    /// 
    /// An interface to implement the linear array.
    /// @see ae2f_ds_cAlloc
    /// @see ae2f_ds_Alloc_cOwn
    /// @see ae2f::Ds::Alloc::rOwner
    struct xrOwner : public rOwner {
        public:
        /// @brief
        /// Gets data from a class.
        /// @param i The Index [in an unit of bytes] where the element to copy is.
        /// @param dest A pointer of buffer where the element to be copied.
        /// @param destlen The allocated size of the [dest].
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpRead_t
        /// @see ae2f_ds_Alloc_cRef_Read
        /// @see ae2f_ds_Alloc_cOwn_Read
        inline ae2f_errint_t Read(size_t i, void* dest, size_t destlen) const noexcept {
            return ae2f_ds_Alloc_cOwn_Read(this, i, dest, destlen);
        }

        /// @brief
        /// Sets data to a class.
        /// @param i The Index [in an unit of bytes] where the element to be overwritten.
        /// @param src A pointer of an element.
        /// @param srclen An allocated size of the [src].
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpWrite_t
        /// @see ae2f_ds_Alloc_cRef_Write
        /// @see ae2f_ds_Alloc_cOwn_Write
        inline ae2f_errint_t Write(size_t i, const void* src, size_t srclen) noexcept {
            return ae2f_ds_Alloc_cOwn_Write(this, i, src, srclen);
        }

        /// @brief
        /// Gets the length, and element size of the class.
        /// @param lenbuff A pointer where the count of the array, as an unit of elements.
        /// @param elsizebuff A pointer where the size of the element.
        /// @return 
        /// @ref ae2f_errGlob_OK \n
        /// @ref ae2f_ds_Alloc_Err_NCOPIED
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpLen_t
        /// @see ae2f_ds_Alloc_cRef_getSize
        /// @see ae2f_ds_Alloc_cOwn_getSize
        inline ae2f_errint_t Length(size_t* lenbuff, size_t* elsizebuff) const noexcept {
            return ae2f_ds_Alloc_cOwn_getSize(this, lenbuff, elsizebuff);
        }

        /// @warning
        /// This operation may not be efficient under certain implements.
        /// @brief 
        /// Resizes the memory of [This] as bytes count. \n
        /// Additional memories(newly allocated) must be initiated as 0. \n
        /// Element size will be suggested as 1.
        /// @param bytecount The byte length to resize.
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errGlob_ALLOC_FAILED
        /// @see ae2f_ds_Alloc_cOwn
        /// @see ae2f_ds_Alloc_fpReConfig_t
        /// @see ae2f_ds_Alloc_cOwn_ReConfig
        /// @see ae2f_ds_Alloc_cOwn_ReSize
        inline ae2f_errint_t Resize(size_t bytecount) noexcept {
            return ae2f_ds_Alloc_cOwn_ReSize(this, bytecount);
        }

        /// @brief 
        /// Resizes the memory of [This]. \n
        /// Additional memories(newly allocated) must be initiated as 0.
        /// @param elcount The count of the elements.
        /// @param elsize The size of each elements.
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errGlob_ALLOC_FAILED
        /// @see ae2f_ds_Alloc_cOwn
        /// @see ae2f_ds_Alloc_fpReConfig_t
        /// @see ae2f_ds_Alloc_cOwn_ReConfig
        inline ae2f_errint_t ReConfig(size_t elcount, size_t elsize) {
            return ae2f_ds_Alloc_cOwn_ReConfig(this, elcount, elsize);
        }

        /// @brief 
        /// Frees the memory of class. \n
        /// Error code will be stored in @ref ae2f_errGlob_LastErr.
        /// @param This The instance of a class where the memory to free is located.
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL
        /// @see ae2f_ds_Alloc_cOwn
        /// @see ae2f_ds_Alloc_fpDel_t
        /// @see ae2f_ds_Alloc_cOwn_Del
        /// @see ae2f_errGlob_LastErr
        inline ~xrOwner() noexcept {
            ae2f_errGlob_LastErr |= (ae2f_ds_Alloc_cOwn_Del(this));
        }

        /// @brief 
        /// Allocates the memory.
        /// Copies the data from [src] to a class.
        /// @param src Source to copy.
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errGlob_ALLOC_FAILED
        /// @see ae2f_ds_Alloc_cRef_getSize
        /// @see ae2f_ds_Alloc_cRef_Read
        /// @see ae2f_ds_Alloc_cRef_Write
        /// @see ae2f_ds_Alloc_cOwn
        /// @see ae2f_ds_Alloc_cOwn_ReConfig
        /// @see ae2f_ds_Alloc_cOwn_Cpy_imp
        /// @see ae2f_ds_Alloc_cOwn_Cpy
        inline ae2f_errint_t Copy(const rRefer& src) noexcept {
            return ae2f_ds_Alloc_cOwn_Cpy(this, &src);
        }

        /// @brief 
        /// Allocates the memory.
        /// Copies the data from [src] to a class.
        /// @param src Source to copy.
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_errGlob_ALLOC_FAILED
        /// @see ae2f_ds_Alloc_cRef_getSize
        /// @see ae2f_ds_Alloc_cRef_Read
        /// @see ae2f_ds_Alloc_cRef_Write
        /// @see ae2f_ds_Alloc_cOwn
        /// @see ae2f_ds_Alloc_cOwn_ReConfig
        /// @see ae2f_ds_Alloc_cOwn_Cpy_imp
        /// @see ae2f_ds_Alloc_cOwn_Cpy
        inline ae2f_errint_t Copy(const rRefer&& src) noexcept {
            return ae2f_ds_Alloc_cOwn_Cpy(this, &src);
        }

        /// @brief 
        ///	Initialises the pointer. \n
        ///	Injects the function pointers automatically.
        /// @param perr 
        /// An address where state number be stored. \n
        /// Setting it 0 will cause a status number stored in @ref ae2f_errGlob_LastErr.
        /// @param imp
        /// Class Implementations
        /// @return @ref ae2f_errGlob_OK
        /// @exception  \
        /// @ref ae2f_ds_Alloc_Err_FPIMPNULL  \n
        /// @ref ae2f_errGlob_PTR_IS_NULL
        /// @see ae2f_ds_Alloc_cOwn
        inline xrOwner(
            ae2f_errint_t* perr,
            const ae2f_ds_vAlloc* imp
        ) noexcept : rOwner() {
            perr = perr ? perr : &ae2f_errGlob_LastErr;
            *perr |= ae2f_ds_Alloc_cOwn_Init(this, imp);
        }
    };

    /// @brief
    /// # This structure owns the memory.
    /// 
    /// An interface to implement the linear array.
    /// @tparam __imp
    /// Function implementations set.
    /// @see ae2f_ds_cAlloc
    /// @see ae2f_ds_Alloc_cOwn
    /// @see ae2f::Ds::Alloc::rOwner
    template<const ae2f_ds_vAlloc* __imp>
    struct iOwner : public xrOwner, public vfDef<__imp> {
        /// @brief 
        ///	Initialises the pointer. \n
        ///	Injects the function pointers automatically.
        /// @param perr 
        /// An address where state number be stored. \n
        /// Setting it 0 will cause a status number stored in @ref ae2f_errGlob_LastErr.
        /// @param imp
        /// Class Implementations
        /// @return @ref ae2f_errGlob_OK
        /// @exception  \
        /// @ref ae2f_ds_Alloc_Err_FPIMPNULL  \n
        /// @ref ae2f_errGlob_PTR_IS_NULL
        /// @see ae2f_ds_Alloc_cOwn
        /// @see ae2f::Ds::Alloc::xrOwner::xrOwner
        inline iOwner(
            ae2f_errint_t* perr = 0
        ) noexcept : xrOwner(perr, __imp) {}
    };
}}}