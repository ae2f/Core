/// @file
/// Helper header for ae2f/Ds/Arr.hpp
/// @warning 
/// This file has lack of definitions.

namespace ae2f { namespace Ds { namespace Arr {
    /// @warning
    /// This class is not intended to be used directly. \n
    /// Use binder classes in order not to get undefined behaviour.
    /// @brief
    /// # This structure does not own the memory.
    /// 
    /// An interface to implement the linear array.
    /// @tparam T 
    /// @tparam NIsTrivial 
    /// Whether [T] is trivial or not. \n
    /// 0 means [T] is not trivial, which means it has a custom constructor - destructor.
    /// @see ae2f_ds_cAlloc
    /// @see ae2f_ds_Alloc_cRef
    /// @see ae2f::Ds::Alloc::rRefer
    template<typename T, bool NIsTrivial>
    struct __Refer {};

    /// @warning
    /// This class is not intended to be used directly. \n
    /// Use binder classes in order not to get undefined behaviour.
    /// @brief
    /// # This structure owns the memory.
    /// 
    /// An interface to implement the linear array.
    /// @tparam T 
    /// @tparam NIsTrivial 
    /// Whether [T] is trivial or not. \n
    /// 0 means [T] is not trivial, which means it has a custom constructor - destructor.
    /// @see ae2f_ds_cAlloc
    /// @see ae2f_ds_Alloc_cOwn
    /// @see ae2f::Ds::Alloc::rOwner
    template<typename T, bool NIsTrivial>
    struct __Owner {};

    namespace eRef {
        /// @brief
        /// The element has not been yet constructed.
        /// @return 
        /// @ref ae2f_errGlob_WRONG_OPERATION  \n
        /// @ref ae2f_errGlob_DONE_HOWEV
        constexpr ae2f_errint_t EL_NON_VALID = 80;
    };
}}}