#ifndef ae2f_c90_StdInt_filter_h
#define ae2f_c90_StdInt_filter_h

#include <ae2f/c90/stdint/.have.h>

#if defined(__cplusplus) && __cplusplus >= 201103L
#include <cstdint>
#elif AE2F_HAVE_STDINT_H
#include <stdint.h>
#else
#include "./base.h"
#endif

#endif
