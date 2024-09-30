#include <ae2f/DataStructure/Allocator.h>

enum globalErr_Byte1 {
    ALL_GOOD,
    WRONG_DS,
};

#define TEST_VAL(buff, ...) if((buff) = (__VA_ARGS__)) return (buff);
#define TEST(fun, buff) if((buff) = ((fun)())) return (buff);
 
#pragma region Test Alloc
// resize / getsize / init / del
static int Test0x0() {
    int code = 0;
    struct ae2f_ds_Alloc_Owner a;
    size_t sizeBuff;

    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Init(&a, &ae2f_ds_Alloc_vRefer_cLinear, &ae2f_ds_Alloc_vOwner_cLinear));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_reSize(&a, 34));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_getSize(&a, &sizeBuff));
    if(sizeBuff != 34) return ae2f_errGlobal_LMT;
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Del(&a));
    
    return 0;
}

// read / write
static int Test0x1() {
    int code = 0; int data = 45;
    struct ae2f_ds_Alloc_Owner a;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Init(&a, &ae2f_ds_Alloc_vRefer_cLinear, &ae2f_ds_Alloc_vOwner_cLinear));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_reSize(&a, sizeof(int)));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Write(&a, 0, &data, sizeof(int)));
    data = 3;
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Read(&a, 0, &data, sizeof(int)));
    if(data != 45) return ae2f_errGlobal_LMT;
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Del(&a));
    return 0;
}

// if it works on ref
static int Test0x2() {
    int code = 0; int data = 45;
    struct ae2f_ds_Alloc_Owner a;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Init(&a, &ae2f_ds_Alloc_vRefer_cLinear, &ae2f_ds_Alloc_vOwner_cLinear));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_reSize(&a, sizeof(int)));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Write(&a, 0, &data, sizeof(int)));
    data = 3;

    struct ae2f_ds_Alloc_Refer b = ae2f_ds_Alloc_vOwner_Ref(&a);
    TEST_VAL(code, ae2f_ds_Alloc_vRefer_Read(&b, 0, &data, sizeof(int)));
    if(data != 45) return ae2f_errGlobal_LMT;

    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Del(&a));
    return 0;
}

// test copy
static int Test0x3() {
    int code = 0; int data = 45;
    struct ae2f_ds_Alloc_Owner a, b;
    size_t sizeBuff;
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Init(&a, &ae2f_ds_Alloc_vRefer_cLinear, &ae2f_ds_Alloc_vOwner_cLinear));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_InitAuto(&b));

    TEST_VAL(code, ae2f_ds_Alloc_vOwner_reSize(&a, sizeof(int)));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Write(&a, 0, &data, sizeof(int)));
    data = 3;

    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Copy(&b, &a));
    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Read(&b, 0, &data, sizeof(int)));
    if(data != 45) return ae2f_errGlobal_LMT;

    TEST_VAL(code, ae2f_ds_Alloc_vOwner_Del(&a) | ae2f_ds_Alloc_vOwner_Del(&b));
    return 0;
}
#pragma endregion

int main() {
    int ErrCode;

    TEST(Test0x0, ErrCode);
    TEST(Test0x1, ErrCode);
    TEST(Test0x2, ErrCode);

    return 0;
}