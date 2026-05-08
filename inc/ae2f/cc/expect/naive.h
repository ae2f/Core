/**
 * @file naive.h
 * */

#include "./strict.h"

#ifndef	ae2f_expected
#	define	ae2f_expected(a)	(!ae2f_expected_not_strict(!(a)))
#endif

#ifndef	ae2f_expected_not
#	define	ae2f_expected_not(a)	(ae2f_expected_not_strict((a)))
#endif
