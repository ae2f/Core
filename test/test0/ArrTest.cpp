#include <ae2f/Ds/Arr.hpp>
#include <iostream>
#include <ae2f/Macro/Cast.h>

#include "../test.h"

struct a {
    static int _d;
    int v;

    inline a() {
        v = _d++;
        std::cout << _d - 1 << " is here!\n";
    }

    inline a(int d) {
        v = _d++;
        std::cout << _d - 1 << " is here with parameters! [" << d << "]\n";
    }

    inline ~a() {
        std::cout << v << " is gone!\n";
    }
};

int a::_d = 0;


static int Test0() {
    ae2f::Ds::Arr::cOwner::Linear_t<a> _a;

    std::cout << "Linear: " << (int)(_a.v == &ae2f_ds_vAlloc_cLinear) << "\n";

    std::cout << "Resize: " << (int)_a.Resize(10) << "\n";
    size_t d, df;
    _a.Length(&d, &df);

    std::cout << "Size: " << d << " " << df << "\n";
    _a.Write(0);
    _a.Write(1, 143);

    return 0;
}

// raw copy test
static int Test3() {
    ae2f::Ds::Arr::cOwner::Linear_t<int> _a, _b;

    _a.Resize(5);
    _a.Write(0, 6);

    std::cout << (int)_b.Copy(_a) << " is a copying state\n";
    std::cout << "copy Read: " << _b.Read(0, 0) << "\n";

    return 0;
}

// raw ref test
static int Test1() {
    ae2f::Ds::Arr::cOwner::Linear_t<int> _a;

    _a.Resize(5);
    _a.Write(0, 6);

    ae2f::Ds::Arr::cRefer<int> _b = _a;
    std::cout << "Ref Read: " << _b.Read(0, 0) << "\n";

    return 0;
}

// ref test [non-trivial]
static int Test2() {
    ae2f::Ds::Arr::cOwner::Linear_t<a> _a;
    _a.Resize(20);
    _a.Write(0);

    ae2f::Ds::Arr::cRefer<a> ref(_a);
    std::cout << ref.Read(0).Obj.v << "\n";

    return 0;
}


int ArrTest() {
    int errcode;
    TEST(Test0, errcode);
    TEST(Test1, errcode);
    TEST(Test2, errcode);
    TEST(Test3, errcode);

    return errcode;
}
