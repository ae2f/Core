#include <ae2f/Lock.h>

#if !ae2f_IS_WIN
#include <pthread.h>
#endif

ae2f_addrel_t el = 0;

void* P(void*) {
    __ae2f_Wait(&el, 0);
    return NULL;
}

int main() {
#if !ae2f_IS_WIN
    pthread_t thread;
    pthread_create(&thread, 0, P, 0);
    el = 1;
    __ae2f_WakeSingle(&el);
    return pthread_join(thread, 0);;
#endif
    return 0;
}