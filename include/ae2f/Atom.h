#ifndef ae2f_Atom_h
#define ae2f_Atom_h

#include <stdatomic.h>

#ifdef __cplusplus
#include <atomic>
#include "./Cast.h"
#endif

#define ae2f_Atom(t)    ae2f_WhenC(_Atomic(t))    ae2f_WhenCXX(std::atomic<t>)

#endif