#define ON 1
#define OFF 0

#if (defined(_WIN32) || defined(_WIN64))
#define ae2f_IS_WIN 1
#else 
#define ae2f_IS_WIN 0
#endif

#if (defined(__linux__))
#define ae2f_IS_LINUX 1
#else 
#define ae2f_IS_LINUX 0
#endif

#if defined(__MACH__) || defined(__APPLE__)
#define ae2f_IS_APPLE 1
#else
#define ae2f_IS_APPLE 0
#endif

#if (ae2f_IS_WIN == ae2f_IS_LINUX) && (ae2f_IS_LINUX == ae2f_IS_APPLE) && (ae2f_IS_APPLE == ae2f_IS_WIN)
#pragma message("[WARNING] Platform not specified") 
/*** @brief UNSPECIFIED */
#define ae2f_IDK 1
#else
/*** @brief UNSPECIFIED */
#define ae2f_IDK 0
#endif