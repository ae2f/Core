#include <ae2f/DataStructure/Allocator.h>

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
    struct ae2f_ds_Alloc_Owner a;
    size_t sizeBuff;

    TEST_VAL(code, ae2f_ds_Alloc_vOwner_InitAuto(&a));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_reSize(&a, 34));

    TEST_IF(code, ae2f_ds_Alloc_vOwner_getSize(&a, &sizeBuff))
    goto __END;

    if(sizeBuff != 34) {
        code = ae2f_errGlobal_LMT;
        goto __END;
    }

    __END:
    ae2f_ds_Alloc_vOwner_Del(&a);
    return code;
}

// read / write
static int Test0x1() {
    int code = 0; int data = 45;
    struct ae2f_ds_Alloc_Owner a;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Init(&a, &ae2f_ds_Alloc_vRefer_cLinear, &ae2f_ds_Alloc_vOwner_cLinear));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_reSize(&a, sizeof(int)));
    TEST_IF(code, ae2f_ds_Alloc_vOwner_Write(&a, 0, &data, sizeof(int)))
        goto END;

    data = 3;
    TEST_IF(code, ae2f_ds_Alloc_vOwner_Read(&a, 0, &data, sizeof(int)))
        goto END;

    if(data != 45) {
        code = ae2f_errGlobal_LMT;
        goto END;
    }

    END:
    ae2f_ds_Alloc_vOwner_Del(&a);
    return code;
}

// if it works on ref
static int Test0x2() {
    int code = 0; int data = 45;
    struct ae2f_ds_Alloc_Owner a;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Init(&a, &ae2f_ds_Alloc_vRefer_cLinear, &ae2f_ds_Alloc_vOwner_cLinear));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_reSize(&a, sizeof(int)));
    TEST_IF(code, ae2f_ds_Alloc_vOwner_Write(&a, 0, &data, sizeof(int))) {
        goto END;
    }
    data = 3;

    struct ae2f_ds_Alloc_Refer b = ae2f_ds_Alloc_vOwner_Ref(&a);
    TEST_IF(code, ae2f_ds_Alloc_vRefer_Read(&b, 0, &data, sizeof(int))) {
        goto END;
    }

    if(data != 45) {
        goto END;
    }
    
    END:
    ae2f_ds_Alloc_vOwner_Del(&a);
    return code;
}

// test copy
static int Test0x3() {
    int code = 0; int data = 45;
    struct ae2f_ds_Alloc_Owner a, b;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_InitAuto(&a));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_InitAuto(&b));

    TEST_VAL(code, ae2f_ds_Alloc_vOwner_reSize(&a, sizeof(int)));

    TEST_IF(code, ae2f_ds_Alloc_vOwner_Write(&a, 0, &data, sizeof(int)))
    goto __KILL_A_ONLY;

    data = 3;

    TEST_IF(code, ae2f_ds_Alloc_vOwner_Copy(&b, &a))
    goto __KILL_ALL;

    TEST_IF(code, ae2f_ds_Alloc_vOwner_Read(&b, 0, &data, sizeof(int)))
    goto __KILL_ALL;

    if(data != 45) {
        code = ae2f_errGlobal_LMT;
        goto __KILL_ALL;
    }

    __KILL_ALL:
    ae2f_ds_Alloc_vOwner_Del(&b);

    __KILL_A_ONLY:
    ae2f_ds_Alloc_vOwner_Del(&a);
    return code;
}

// Error
static int Test0x4() {
    struct ae2f_ds_Alloc_Owner a;
    if(ae2f_ds_Alloc_vOwner_Init(&a, 0, 0) == ae2f_errGlobal_OK)
    return ae2f_errGlobal_WRONG_OPERATION;
    return ae2f_errGlobal_OK;
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