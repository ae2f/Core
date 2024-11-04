/// @file
/// @warning
/// This file is a helper header of @ref ae2f/Ds/Alloc.hpp \n
/// Few definitions may lack.

namespace ae2f { namespace Ds { namespace Alloc {

    /// @brief
    /// # This structure does not own the memory.
    /// 
    /// An interface to implement the linear array.
    /// @see ae2f_ds_cAlloc
    /// @see ae2f_ds_Alloc_cRef
    /// @see ae2f::Ds::Alloc::rRefer
    struct cRefer : public rRefer {
        public:

        /// @brief
        /// Gets data from a class.
        /// @param idx The Index [in an unit of bytes] where the element to copy is.
        /// @param buff A pointer of buffer where the element to be copied.
        /// @param elsize The allocated size of the [buff].
        /// @return @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpRead_t
        /// @see ae2f_ds_Alloc_cRef_Read
        inline ae2f_errint_t Read(size_t idx, void* buff, size_t elsize) const noexcept {
            return ae2f_ds_Alloc_cRef_Read(this, idx, buff, elsize);
        }

        /// @brief
        /// Sets data to a class.
        /// @param idx The Index [in an unit of bytes] where the element to be overwritten.
        /// @param src A pointer of an element.
        /// @param srcsize An allocated size of the [src].
        /// @return 
        /// @ref ae2f_errGlob_OK
        /// @exception \
        /// @ref ae2f_errGlob_IMP_NOT_FOUND \n
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @ref ae2f_ds_Alloc_Err_IDX_INVALID
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpWrite_t
        /// @see ae2f_ds_Alloc_cRef_Write
        inline ae2f_errint_t Write(size_t idx, const void* src, size_t srcsize) noexcept {
            return ae2f_ds_Alloc_cRef_Write(this, idx, src, srcsize);
        }

        /// @brief
        /// Gets the length, and element size of the class.
        /// @param sizebuff A pointer where the count of the array, as an unit of elements.
        /// @param elsizebuff A pointer where the size of the element.
        /// @return 
        /// @ref ae2f_errGlob_OK \n
        /// @ref ae2f_ds_Alloc_Err_NCOPIED
        /// @exception \
        /// @ref ae2f_errGlob_PTR_IS_NULL \n
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_fpLen_t
        /// @see ae2f_ds_Alloc_cRef_getSize
        inline ae2f_errint_t Length(size_t* sizebuff, size_t* elsizebuff) const noexcept {
            return ae2f_ds_Alloc_cRef_getSize(this, sizebuff, elsizebuff);
        }

        /// @brief
        /// Initialises the class for reffering.
        /// @param r {const ae2f_ds_cAlloc*}
        /// @returns {const ae2f_ds_Alloc_cRef} This initiated structure.
        /// @warning
        /// You need to suggest that returning value of this does not own the memory.
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_cRef_Mk
        constexpr cRefer(const rRefer& r) noexcept : rRefer(ae2f_ds_Alloc_cRef_Mk(&r)) {}

        /// @brief
        /// Initialises the class for reffering.
        /// @param r {const ae2f_ds_cAlloc*}
        /// @returns {const ae2f_ds_Alloc_cRef} This initiated structure.
        /// @warning
        /// You need to suggest that returning value of this does not own the memory.
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_cRef_Mk
        constexpr cRefer(const rRefer&& r) noexcept : rRefer(ae2f_ds_Alloc_cRef_Mk(&r)) {}

        /// @brief
        /// Initialises the class for reffering.
        /// @param r {const ae2f_ds_cAlloc*}
        /// @returns {const ae2f_ds_Alloc_cRef} This initiated structure.
        /// @warning
        /// You need to suggest that returning value of this does not own the memory.
        /// @see ae2f_ds_Alloc_cRef
        /// @see ae2f_ds_Alloc_cRef_Mk
        constexpr cRefer(const xrOwner& r) noexcept;

        /// @warning
        /// Notice that will have no implementation.
        /// @brief 
        /// A constructor for instance of class without any implementations.
        constexpr cRefer() noexcept : rRefer{ 0, 0 } {}
    };
}}}