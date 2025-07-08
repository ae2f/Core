


#if __cplusplus >= (201103L)
#define voidconv (void)

#include <ae2f/errGlob.hpp>

#include <ae2f/BitVec.h>
#include <ae2f/BitVec.hpp>

#include <ae2f/Call.h>

#include <ae2f/Cmp.h>
#include <ae2f/Cmp.hpp>

#include <ae2f/Float.h>
#include <ae2f/Cast.h>

#include <ae2f/errGlob.h>

#include <ae2f/Pack/Beg.h>
#include <ae2f/Pack/End.h>

#include <ae2f/Pack/Num.auto.h>

#else
#define voidconv 
#endif


#if __cplusplus >= (201103L)
int main() {
    voidconv ae2f::xfpCmp<int>;
    voidconv ae2f::errGlobState::errGlobStateWithThrow;
    ae2f::rBitVec<int> a = 3;
    voidconv ae2f::Cmp::Diff<int>;
    voidconv ae2f::Cmp::TakeGt<int>;
    voidconv ae2f::Cmp::TakeLs<int>;
    voidconv ae2f::rBitVec<int>::Filled;

    switch(3) {
        case ae2f::Cmp::TakeLs<int>(3, 5):
        break; default: return 1;
    }

    switch(3) {
        case ae2f::Cmp::TakeGt<int>(-1, 3):
        break; default: return 1;
    }

    switch(34) {
        case ae2f::Cmp::Diff<int>(0, 34):
        break; default: return 1;
    }


#if __ae2f_cppcheck(201403L)
    switch(8) {
        case ae2f::rBitVec<int>(8).FndOne().obj:
        break; default: 
        return 1;
    }

    switch(0) {
        case ae2f::rBitVec<unsigned int>(0).FndOne().obj:
        break; default: return 1;
    }
#endif

    switch(0) {
        case ae2f::rBitVec<int>(5).Get(1):
        break; default: return 1;
    }

    return 0;     
}

#else

int main() {
	return 0;
}
#endif
