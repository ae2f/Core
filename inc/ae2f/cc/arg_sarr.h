#ifndef	ae2f_cc_arg_sarr_h
#define ae2f_cc_arg_sarr_h

#include <ae2f/LangVer.h>
#include "./qualifier.h"

#if	ae2f_stdcc_v || ae2f_stdc_v < 199900L
#	define ae2fcc_arg_sarr(name, c)			name[c]
#	define ae2fcc_arg_sarr_restrict(name, c)	* const ae2f_restrict name
#else
#	define ae2fcc_arg_sarr(name, c)			name[static c]
#	define ae2fcc_arg_sarr_restrict(name, c)	name[static ae2f_restrict c]
#endif

#endif
