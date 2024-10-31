#include <ae2f/Ds/Alloc.hpp>

enum globalErr_Byte1 {
    ALL_GOOD,
    WRONG_DS,
};

#define TEST_IF(buff, ...) if((buff) = (__VA_ARGS__))
#define TEST_VAL(buff, ...) TEST_IF(buff, __VA_ARGS__) return (buff);
#define TEST(fun, buff) if((buff) = ((fun)())) return (buff);
 
#pragma region Test Alloc

// resize / getsize / init / del
static int Test0x0() {
    ae2f_errint_t code = 0;
    ae2f::Ds::Alloc::cOwner::Linear_t a(&code);
    size_t sizeBuff, nsize;
    
    if(code) {
        return code;
    }

    TEST_VAL(code, a.Resize(34));
    TEST_IF(code, a.Length(&sizeBuff, &nsize))
    goto __END;

    if(sizeBuff != 34 || nsize != 1) {
        code = ae2f_errGlob_NFOUND;
        goto __END;
    }

    __END:
    return code;
}

// read / write
static int Test0x1() {
    ae2f_errint_t code = 0; int data = 45;
    ae2f::Ds::Alloc::cOwner::Linear_t a(&code);
    if(code) return code;

    
    TEST_VAL(code, a.Resize(sizeof(int)));
    TEST_IF(code, a.Write(0, &data, sizeof(int)))
        goto END;

    data = 3;
    TEST_IF(code, a.Read(0, &data, sizeof(int)))
        goto END;

    if(data != 45) {
        code = ae2f_errGlob_NFOUND;
        goto END;
    }

    END:
    return code;
}

// if it works on ref
static int Test0x2() {
    ae2f_errint_t code = 0; int data = 45;
    ae2f::Ds::Alloc::cOwner::Linear_t a(&code);
    if(code) return code;
    size_t sizeBuff;

    ae2f::Ds::Alloc::cRefer b;
    TEST_VAL(code, a.Resize(sizeof(int)));
    TEST_IF(code, a.Write(0, &data, sizeof(data))) {
        goto END;
    }
    data = 3;

    b = a;
    TEST_IF(code, b.Read(0, &data, sizeof(int))) {
        goto END;
    }

    if(data != 45) {
        goto END;
    }
    
    END:
    return code;
}

// test copy
static int Test0x3() {
    ae2f_errint_t code = 0; int data = 45;
    ae2f::Ds::Alloc::cOwner::Linear_t a(&code), b(&code);
    size_t sizeBuff;
    if(code) return code;

    TEST_VAL(code, a.Resize(sizeof(int)));

    TEST_IF(code, a.Write(0, &data, sizeof(int)))
    goto __KILL_A_ONLY;

    data = 3;

    TEST_IF(code, b.Copy(a))
    goto __KILL_ALL;

    TEST_IF(code, b.Read(0, &data, sizeof(int)))
    goto __KILL_ALL;

    if(data != 45) {
        code = ae2f_errGlob_NFOUND;
        goto __KILL_ALL;
    }

    __KILL_ALL:
    __KILL_A_ONLY:
    return code;
}

// Error
static int Test0x4() {
    ae2f_errint_t code;
    ae2f::Ds::Alloc::xrOwner a(&code, 0);
    if(code) return ae2f_errGlob_OK;
    return ae2f_errGlob_NFOUND;
}

int Test0x5();
int Test0x6();

#pragma endregion

int main() {
    int ErrCode;

    TEST(Test0x0, ErrCode);
    TEST(Test0x1, ErrCode);
    TEST(Test0x2, ErrCode);
    TEST(Test0x3, ErrCode);
    TEST(Test0x4, ErrCode);
    // TEST(Test0x5, ErrCode);
    // TEST(Test0x6, ErrCode);

    return 0;
}