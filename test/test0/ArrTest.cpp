#include <ae2f/Ds/Arr.hpp>
#include <iostream>

struct a {
    int d;

    inline a() {
        std::cout << this << " is here!\n";
    }

    inline a(int d) {
        std::cout << this << " is here with parameters! (" << d << ")\n";
    }

    inline ~a() {
        std::cout << this << " is gone!\n";
    }
};

int Test0x5() {
    ae2f::Ds::Arr::cOwner::Linear_t<a> _a;
    std::cout << (int)_a.Resize(10) << "\n";
    size_t d, df;
    _a.Length(&d, &df);
    std::cout << d << " " << df << "\n";

    _a.Write(0);
    _a.Write(1, 143);

    return 0;
}

int Test0x6() {
    ae2f::Ds::Arr::cOwner::Linear_t<int> _a;
    _a.Resize(5);
    _a.Read(0);
    /// ae2f::Ds::Arr::cRefer<int> ref = _a;

    return 1;
}