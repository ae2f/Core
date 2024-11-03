#include "Compare.h"

#if !defined(ae2f_Macro_Compare_hpp)
#define ae2f_Macro_Compare_hpp

namespace ae2f {
	namespace Macro {
		namespace Cmp {

            /// @warning
            /// Two parameters must be comparable with operator.
            /// @return
            /// One bigger.
			template<typename T, typename K = T, typename R = T>
			constexpr R TakeGt(T a, K b) { return ae2f_Macro_Cmp_TakeGt(a, b); }

            /// @warning
            /// Two parameters must be comparable with operator.
            /// @return
            /// One smaller.
			template<typename T, typename K = T, typename R = T>
			constexpr R TakeLs(T a, K b) { return ae2f_Macro_Cmp_TakeLs(a, b); }

            /// @return
            /// The absolute different of two.
			template<typename T, typename K = T, typename R = T>
			constexpr R Diff(T a, K b) { return ae2f_Macro_Cmp_Diff(a, b); }
		}
	}
}

#endif // !defined(ae2f_Macro_Compare_hpp)