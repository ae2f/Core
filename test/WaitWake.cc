#if __cplusplus >= 201103L

#include <ae2f/Lock.h>
#include <thread>

ae2f_addrel_t el = 0;

void P() {
    __ae2f_Wait(&el, 0);
}

int main() {
    std::thread td(P);
    el = 1;

    __ae2f_WakeSingle(&el);
    td.join();

    return 0;
}

#else 
int main() { return 0; }
#endif
