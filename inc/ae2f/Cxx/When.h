#ifndef	ae2f_Cxx_When_h

#include "../LangVer.h"

#if	ae2f_stdcc_v

/**
 @def ae2f_WhenCXX 
 @brief
 Appears when the current language is C++.
 */
#define ae2f_WhenCXX(a) a

/**
 @brief
 Appears when the current language is C.
 */
#define ae2f_WhenC(a) 

#else

/**
 @brief
 Appears when the current language is C++.
 */
#define ae2f_WhenC(a) a

/**
 @brief
 Appears when the current language is C.
 */
#define ae2f_WhenCXX(a) 

#endif
#endif
