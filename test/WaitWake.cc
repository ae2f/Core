#include <ae2f/WaitWake.h>
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