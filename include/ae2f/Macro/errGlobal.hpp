#include <ae2f/Macro/errGlobal.h>
#include "Call.h"

#if !defined(ae2f_Macro_errGlobal_hpp) && defined(__cplusplus)
#define ae2f_Macro_errGlobal_hpp

namespace ae2f {
    namespace Macro {
        /// @brief Stores the last error occured on deconstructor of class C++.
        ae2f_SHAREDCALL extern ae2f_errint_t gErrOccurredOnDeconstructor;
    }
}
#endif