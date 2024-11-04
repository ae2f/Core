/// @file
/// Helper header for ae2f/Ds/Arr.hpp
/// @warning 
/// This file has lack of definitions.

namespace ae2f { namespace Ds { namespace Arr {

    /// @brief 
    /// A helper class for getting element type and element size.
    /// @tparam __el_t 
    /// @tparam __elsize 
    template<typename __el_t>
    struct __def {
        public:
        /// @brief Pre-defined element size 
        static constexpr size_t ElSize = sizeof(__el_t);

        /// @brief Defined element type
        using El_t = __el_t;

        /// @brief Self
        using _f = __def<__el_t>;
    };

    
    /// @brief 
    /// A value package for non-trivial classes. \n
    /// Which will not call the destructor of [T].
    /// @tparam T 
    /// Non-trivial value.
    template<typename T>
    union Pack {
        private:
        friend __Refer<T, 0>;
        friend __Owner<T, 0>;

        /// @brief 
        /// Byte stream for class.
        uint8_t c[sizeof(T) + 1];

        /// @brief 
        /// Check if @ref ae2f::Ds::Arr::Pack<T>::Obj is valid.
        constexpr uint8_t& _isvalid() noexcept {
            return c[sizeof(T)];
        }

        /// @brief 
        /// Check if @ref ae2f::Ds::Arr::Pack<T>::Obj is valid.
        constexpr const uint8_t& _isvalid() const noexcept {
            return c[sizeof(T)];
        }

        template<int d = 0>
        inline Pack() noexcept : c{0, } {
            for(size_t i = 0; i < sizeof(T) + 1; i++)
            c[i] = 0;
        }

        public:

        /// @warning
        /// Note that this class will not be destructed.
        T Obj;

        /// @brief 
        /// Check if @ref ae2f::Ds::Arr::Pack<T>::Obj is valid.
        constexpr bool isvalid() const noexcept {
            return c[sizeof(T)];
        }
        inline ~Pack() {}
    };
}}}