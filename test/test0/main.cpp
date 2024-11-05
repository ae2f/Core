#include "../test.h"

int AllocTest();
int ArrTest();

int main() {
    int code;
    TEST(AllocTest, code);
    TEST(ArrTest, code);

    return code;
}