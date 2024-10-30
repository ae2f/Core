#include <ae2f/Ds/Arr.hpp>
#include <iostream>

struct a {
    inline a() {
        std::cout << this << " is here!\n";
    }

    inline ~a() {
        std::cout << this << " is gone!\n";
    }
};

int Test0x5() {
    ae2f::Ds::Arr::cOwner::Linear_t<a> _a;
    _a.Resize(10);
    _a.Write(0);
    auto d = _a.Read(0);

    return 0;
}

int Test0x6() {
    ae2f::Ds::Arr::cOwner::Linear_t<a> _a;
    // ae2f::Ds::Arr::cRefer<a> d = _a; // TODO: Make it work
    return 1;
}