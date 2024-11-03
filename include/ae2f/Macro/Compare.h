#if !defined(ae2f_Macro_Compare_h)
#define ae2f_Macro_Compare_h

/// @warning
/// Two parameters must be comparable with operator.
/// @return
/// One bigger.
#define ae2f_Macro_Cmp_TakeGt(a, b)		((a) > (b) ? (a) : (b))

/// @warning
/// Two parameters must be comparable with operator.
/// @return
/// One smaller.
#define ae2f_Macro_Cmp_TakeLs(a, b)	((a) < (b) ? (a) : (b))

/// @return
/// The absolute different of two.
#define ae2f_Macro_Cmp_Diff(a, b)			(ae2f_Macro_Cmp_TakeGt(a, b) - ae2f_Macro_Cmp_TakeLs(a, b))

/// @brief
/// Gets the member from the pointer.
/// Given nullptr, the return will be alter.
/// @param ptr The pointer for getting member.
/// @param member The valid member's name. [as the structure]
/// @param alter The alternative value when given nullptr.
#define ae2f_Macro_Cmp_TakeMem(ptr, member, alter) ((ptr) ? ((ptr)->member) : (alter))

/// @brief
/// Returns ptr's self.
/// Given nullptr, the return will be alt.
/// @param ptr Self Referring
/// @param alt The alternative value.
#define ae2f_Macro_Cmp_TakeSelf(ptr, alt) ((ptr) ? (ptr) : (alt))
#endif // !defined(ae2f_Macro_Compare_h)