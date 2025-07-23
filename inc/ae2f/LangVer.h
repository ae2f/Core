#include "./LangVer.auto.h"

#ifdef	__cplusplus
#undef	ae2f_stdcc_v
#define	ae2f_stdcc_v	(__cplusplus)
#else

#undef	ae2f_stdcc_v
#define	ae2f_stdcc_v	(199711L)

#if __ae2f_lvcheck_cc(2011)
#undef	ae2f_stdcc_v
#define	ae2f_stdcc_v	(201103L)
#endif

#if __ae2f_lvcheck_cc(2014)
#undef	ae2f_stdcc_v
#define	ae2f_stdcc_v	(201402L)
#endif

#if __ae2f_lvcheck_cc(2017)
#undef	ae2f_stdcc_v
#define	ae2f_stdcc_v	(201703L)
#endif

#if __ae2f_lvcheck_cc(2020)
#undef	ae2f_stdcc_v
#define	ae2f_stdcc_v	(202002L)
#endif

#if __ae2f_lvcheck_cc(2023)
#undef	ae2f_stdcc_v
#define	ae2f_stdcc_v	(202302L)
#endif

#endif

#ifdef	__STDC_VERSION__
#undef	ae2f_stdc_v
#define ae2f_stdc_v	(__STDC_VERSION__)
#else

#undef	ae2f_stdc_v
#define ae2f_stdc_v	(199001L)

#if __ae2f_lvcheck_cc(1999)
#undef	ae2f_stdc_v
#define ae2f_stdc_v	(199901L)
#endif

#if __ae2f_lvcheck_cc(2011)
#undef	ae2f_stdc_v
#define ae2f_stdc_v	(201112L)
#endif

#if __ae2f_lvcheck_cc(2017)
#undef	ae2f_stdc_v
#define ae2f_stdc_v	(201710L)
#endif

#if __ae2f_lvcheck_cc(2023)
#undef	ae2f_stdc_v
#define ae2f_stdc_v	(202311L)
#endif

#endif

#undef	__ae2f_stdcheck_C
#undef	__ae2f_stdcheck_CC

#define __ae2f_stdcheck_C(v)	(ae2f_stdc_v >= (v))
#define __ae2f_stdcheck_CC(v)	(ae2f_stdcc_v >= (v))

#if __ae2f_stdcheck_C(199901L)
#undef	restrict
#else
#define restrict	ae2f_NONE
#endif
