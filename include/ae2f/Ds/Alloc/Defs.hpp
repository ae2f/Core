/// @file
/// @warning
/// This file is a helper header of @ref ae2f/Ds/Alloc.hpp \n
/// Few definitions may lack.


namespace ae2f { namespace Ds { namespace Alloc {

    /// @brief Structure for virtual function pointer.
    /// @see ae2f_ds_vAlloc
    using vf = ae2f_ds_vAlloc;

    /// @brief
    /// # This structure does not own the memory.
    /// 
    /// An interface to implement the linear array.
    /// @see ae2f_ds_cAlloc
    /// @see ae2f_ds_Alloc_cRef
    using rRefer = ae2f_ds_Alloc_cRef;

    /// @brief
    /// # This structure owns the memory.
    /// 
    /// An interface to implement the linear array.
    /// @see ae2f_ds_cAlloc
    /// @see ae2f_ds_Alloc_cOwn
    using rOwner = ae2f_ds_Alloc_cOwn;
}}}