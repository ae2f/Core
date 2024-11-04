#include <ae2f/Ds/Alloc.h>

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
    int code = 0;
    struct ae2f_ds_Alloc_cOwn a;
    size_t sizeBuff;

    TEST_VAL(code, ae2f_ds_Alloc_cOwn_InitAuto(&a));
    TEST_VAL(code, ae2f_ds_Alloc_cOwn_ReSize(&a, 34));

    TEST_IF(code, ae2f_ds_Alloc_cOwn_getSize(&a, &sizeBuff, 0) & ~ae2f_ds_Alloc_Err_NCOPIED)
    goto __END;

    if(sizeBuff != 34) {
        code = ae2f_errGlob_NFOUND;
        goto __END;
    }

    __END:
    ae2f_ds_Alloc_cOwn_Del(&a);
    return code;
}

// read / write
static int Test0x1() {
    int code = 0; int data = 45;
    struct ae2f_ds_Alloc_cOwn a;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_ds_Alloc_cOwn_InitAuto(&a));
    TEST_VAL(code, ae2f_ds_Alloc_cOwn_ReSize(&a, sizeof(int)));
    TEST_IF(code, ae2f_ds_Alloc_cOwn_Write(&a, 0, &data, sizeof(int)))
        goto END;

    data = 3;
    TEST_IF(code, ae2f_ds_Alloc_cOwn_Read(&a, 0, &data, sizeof(int)))
        goto END;

    if(data != 45) {
        code = ae2f_errGlob_NFOUND;
        goto END;
    }

    END:
    ae2f_ds_Alloc_cOwn_Del(&a);
    return code;
}

// if it works on ref
static int Test0x2() {
    int code = 0; int data = 45;
    struct ae2f_ds_Alloc_cOwn a;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_ds_Alloc_cOwn_InitAuto(&a));
    TEST_VAL(code, ae2f_ds_Alloc_cOwn_ReSize(&a, sizeof(int)));
    TEST_IF(code, ae2f_ds_Alloc_cOwn_Write(&a, 0, &data, sizeof(int))) {
        goto END;
    }
    data = 3;

    struct ae2f_ds_cAlloc b = ae2f_ds_Alloc_cRef_Mk(&a);
    TEST_IF(code, ae2f_ds_Alloc_cRef_Read(&b, 0, &data, sizeof(int))) {
        goto END;
    }

    if(data != 45) {
        goto END;
    }
    
    END:
    ae2f_ds_Alloc_cOwn_Del(&a);
    return code;
}

// test copy
static int Test0x3() {
    int code = 0; int data = 45;
    struct ae2f_ds_Alloc_cOwn a, b;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_ds_Alloc_cOwn_InitAuto(&a));
    TEST_VAL(code, ae2f_ds_Alloc_cOwn_InitAuto(&b));

    TEST_VAL(code, ae2f_ds_Alloc_cOwn_ReSize(&a, sizeof(int)));

    TEST_IF(code, ae2f_ds_Alloc_cOwn_Write(&a, 0, &data, sizeof(int)))
    goto __KILL_A_ONLY;

    data = 3;

    TEST_IF(code, ae2f_ds_Alloc_cOwn_Cpy(&b, &a))
    goto __KILL_ALL;

    TEST_IF(code, ae2f_ds_Alloc_cOwn_Read(&b, 0, &data, sizeof(int)))
    goto __KILL_ALL;

    if(data != 45) {
        code = ae2f_errGlob_NFOUND;
        goto __KILL_ALL;
    }

    __KILL_ALL:
    ae2f_ds_Alloc_cOwn_Del(&b);

    __KILL_A_ONLY:
    ae2f_ds_Alloc_cOwn_Del(&a);
    return code;
}

// Error
static int Test0x4() {
    struct ae2f_ds_Alloc_cOwn a;
    if(ae2f_ds_Alloc_cOwn_Init(&a, 0))
    return ae2f_errGlob_OK;
    return ae2f_errGlob_NFOUND;
}

#pragma endregion

int main() {
    int ErrCode;

    TEST(Test0x0, ErrCode);
    TEST(Test0x1, ErrCode);
    TEST(Test0x2, ErrCode);
    TEST(Test0x3, ErrCode);
    TEST(Test0x4, ErrCode);

    return 0;
}