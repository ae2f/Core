#include <ae2f/Ds/Arr.h>
#include "../test.h"
#include <stdio.h>

int cmp(const int* a, const int* b) {
    return b[0] - a[0];
}

/// search test 
static int Test0() {
    struct ae2f_ds_Alloc_cOwn a;
    ae2f_ds_Alloc_cOwn_InitAuto(&a);
    ae2f_ds_Alloc_cOwn_ReConfig(&a, 5, sizeof(int));

    for(int i = 0; i < 5; i++) {
        int j = 6 - i;
        ae2f_ds_Alloc_cOwn_Write(&a, i * sizeof(int), &j, sizeof(int)); 
    }

    int i = 3;
    size_t eli;
    // second
    int err = ae2f_ds_Arr_BSearch(&a, &i, cmp, &eli, sizeof(int));
    ae2f_ds_Alloc_cRef_Read(&a, eli * sizeof(int), &i, sizeof(int));
    if(i != 3) return 1;
    return 0;
}

/// search test 
static int Test1() {
    struct ae2f_ds_Alloc_cOwn a;
    ae2f_ds_Alloc_cOwn_InitAuto(&a);
    ae2f_ds_Alloc_cOwn_ReConfig(&a, 5, sizeof(int));

    for(int i = 0; i < 5; i++) {
        int j = i;
        ae2f_ds_Alloc_cOwn_Write(&a, i * sizeof(int), &j, sizeof(int));
    }

    // second
    int err = ae2f_ds_Arr_QSort(&a, cmp, sizeof(int));

    for(int i = 0; i < 5; i++) {
        int j;
        ae2f_ds_Alloc_cOwn_Read(&a, i * sizeof(int), &j, sizeof(int));
        printf("%d ", j);
    } printf("\n");
    return 0;
}

int ArrTestMain() {
    int code;
    TEST(Test0, code);
    TEST(Test1, code);
    return 0;
}