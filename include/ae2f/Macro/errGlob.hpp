#if !defined(ae2f_Macro_errGlob_hpp)
#define ae2f_Macro_errGlob_hpp
#include "errGlob.h"

namespace ae2f {
    namespace Macro {
        namespace errGlob {
            constexpr ae2f_errint_t 

            /// @brief
            /// The Operation you've wanted went successful. 
            OK = ae2f_errGlob_OK,

            /// @brief
            /// Failed to find the function on preprocessor which is callable for some reason
            /// No operation has beed done.
            IMP_NOT_FOUND = ae2f_errGlob_IMP_NOT_FOUND,

            /// @brief
            /// Failed to refer the pointer either l-value inside the function.
            PTR_IS_NULL = ae2f_errGlob_PTR_IS_NULL,

            /// @brief
            /// Failed freeing the memory.
            FLUSH_FAILED = ae2f_errGlob_FLUSH_FAILED,

            /// @brief
            /// stdlib allocating functions (malloc, calloc, realloc) has been failed.
            ALLOC_FAILED = ae2f_errGlob_ALLOC_FAILED,

            /// @brief
            /// Found that parameter sent by programmer is invalid.
            /// The operation may have been ceased while the middle.
            WRONG_OPERATION = ae2f_errGlob_WRONG_OPERATION,

            /// @brief
            /// Found some errors, but not by parameters.
            /// The operation has failed.
            NFOUND = ae2f_errGlob_NFOUND,

            /// @brief
            /// The operation went done.
            /// Note that operation may not be valid.
            DONE_HOWEV = ae2f_errGlob_DONE_HOWEV;
        }
    }
}

#endif