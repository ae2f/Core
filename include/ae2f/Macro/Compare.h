#if !defined(ae2f_Macro_Compare_h)
#define ae2f_Macro_Compare_h

#define ae2f_Macro_Compare_TakeBigger(a, b)		((a) > (b) ? (a) : (b))
#define ae2f_Macro_Compare_TakeSmaller(a, b)	((a) < (b) ? (a) : (b))
#define ae2f_Macro_Compare_Diff(a, b)			(ae2f_Macro_Compare_TakeBigger(a, b) - ae2f_Macro_Compare_TakeSmaller(a, b))

#define ae2f_Macro_Compare_TakeMember(ptr, member, alter) ((ptr) ? ((ptr)->member) : (alter))
#define ae2f_Macro_Compare_TakeSelf(ptr, alt) ((ptr) ? (ptr) : (alt))

#endif // !defined(ae2f_Macro_Compare_h)

#if !defined(ae2f_Macro_Compare_hpp) && defined(__cplusplus)
#define ae2f_Macro_Compare_hpp

namespace ae2f {
	namespace Macro {
		namespace Compare {
			template<typename T>
			constexpr T TakeBigger(T a, T b) { return ae2f_Macro_Compare_TakeBigger(a, b); }
			template<typename T>
			constexpr T TakeSmaller(T a, T b) { return ae2f_Macro_Compare_TakeSmaller(a, b); }
			template<typename T>
			constexpr T Diff(T a, T b) { return ae2f_Macro_Compare_Diff(a, b); }
		}
	}
}

#endif // !defined(ae2f_Macro_Compare_hpp)
