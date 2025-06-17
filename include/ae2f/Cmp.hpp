/**
 * @file Cmp.hpp
 * @author ae2f
 * @brief 
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#if !defined(ae2f_Macro_Compare_hpp)
#define ae2f_Macro_Compare_hpp

#include "./Cmp.h"
#include "./Cmp/Fun.hpp"

namespace ae2f {
    namespace Cmp {
        /// @warning
        /// Two parameters must be comparable with operator.
        /// @return
        /// One bigger.
        template<typename T, typename K = T, typename R = T>
        constexprmethod R TakeGt(T a, K b) { return ae2f_CmpGetGt(a, b); }

        /// @warning
        /// Two parameters must be comparable with operator.
        /// @return
        /// One smaller.
        template<typename T, typename K = T, typename R = T>
        constexprmethod R TakeLs(T a, K b) { return ae2f_CmpGetLs(a, b); }

        /// @return
        /// The absolute different of two.
        template<typename T, typename K = T, typename R = T>
        constexprmethod R Diff(T a, K b) { return ae2f_CmpDiff(a, b); }
    }
}

#endif // !defined(ae2f_Macro_Compare_hpp)
