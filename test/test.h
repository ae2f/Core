#define TEST_IF(buff, ...) if((buff) = (__VA_ARGS__))
#define TEST_VAL(buff, ...) TEST_IF(buff, __VA_ARGS__) return (buff);
#define TEST(fun, buff) if((buff) = ((fun)())) return (buff);