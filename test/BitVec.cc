#include <ae2f/BitVec.hpp>

int main() {

#if __ae2f_cppcheck(201103L)
    constexpr ae2f::rBitVec<int> a{23};
#endif
    return 0;
}
