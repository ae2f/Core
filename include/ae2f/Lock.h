/**
 * @file Lock.h
 * @todo Give a way for err-handling
 */

#ifndef ae2f_Lock_h
#define ae2f_Lock_h

#include "./Platform.h"


#if ae2f_IS_WIN
#include <windows.h>
#pragma comment(lib, synchronization) /** synchronization link */

/**
 * @brief 
 * Address element type.
 */
#define ae2f_addrel_t LONG

/**
 * @def __ae2f_win_wait
 * @param uaddr {ae2f_addrel_t*}
 * @param v     {int}
 * @brief
 * Wait `uaddr` if its value equals to `v`.
 */
#define __ae2f_win_wait(uaddr, v) \
    { int vv = v; WaitOnAddress(((volatile LONG*)(uaddr)), &vv, sizeof(int), INFINITE); }

/**
 * @def __ae2f_win_wakesingle
 * @param uaddr     {ae2f_addrel_t*}
 */
#define __ae2f_win_wakesingle(uaddr) \
    WakeByAddressSingle((PVOID)(uaddr))

#define __ae2f_WakeSingle   __ae2f_win_wakesingle
#define __ae2f_Wait         __ae2f_win_wait

#endif

#if ae2f_IS_LINUX
#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>

/**
 * @brief 
 * Address element type.
 */
#define ae2f_addrel_t int

/**
 * @def __ae2f_futex
 * @param uaddr     {int*}
 * @param op        {int}
 * @param val       {int}
 * @param timeout   {const struct timespec*}
 * @param uaddr2    {int*}
 * @param val3      {int}
 * @returns         {int}
 */
#define __ae2f_futex(uaddr, op, val, timeout, uaddr2, val3) \
    syscall(SYS_futex, uaddr, op, val, timeout, uaddr2, val3)


/**
 * @def __ae2f_futex_wait
 * @param uaddr {ae2f_addrel_t*}
 * @param v     {int}
 * @brief
 * Wait `uaddr` if its value equals to `v`.
 */
#define __ae2f_futex_wait(uaddr, v) \
    __ae2f_futex(uaddr, FUTEX_WAIT, v, NULL, NULL, 0)

/**
 * @def __ae2f_futex_wake
 * @param uaddr     {ae2f_addrel_t*}
 * @param n         {int} waking thread count.
 * @brief
 * Wake `n` counts of threads waiting as `uaddr`.
 */
#define __ae2f_futex_wake(uaddr, n) \
    __ae2f_futex(uaddr, FUTEX_WAKE, n, NULL, NULL, 0)


/**
 * @def __ae2f_futex_wakesigle
 * @param uaddr     {ae2f_addrel_t*}
 */
#define __ae2f_futex_wakesigle(uaddr) \
    __ae2f_futex_wake(uaddr, 1)

/**/

#define __ae2f_Wait         __ae2f_futex_wait
#define __ae2f_WakeSingle   __ae2f_futex_wakesigle

#endif

#if ae2f_IS_APPLE
#include <pthread.h>

/**
 * @brief Address element type.
 */
#define ae2f_addrel_t int32_t

/**
 * @brief Static mutex and condition variable for synchronization.
 */
static pthread_mutex_t __ae2f_osx_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t __ae2f_osx_cond = PTHREAD_COND_INITIALIZER;

/**
 * @brief Wait on uaddr if its value equals v.
 * @param uaddr Pointer to address to wait on.
 * @param v Value to compare against.
 * @return 0 on success, -1 on error with errno set.
 */
#define __ae2f_osx_wait(uaddr, v) \
    ({ int __ret = 0; \
       if (pthread_mutex_lock(&__ae2f_osx_mutex) != 0) { \
           errno = EAGAIN; \
           __ret = -1; \
       } else { \
           while (*(uaddr) == (v) && __ret == 0) { \
               if (pthread_cond_wait(&__ae2f_osx_cond, &__ae2f_osx_mutex) != 0) { \
                   errno = EAGAIN; \
                   __ret = -1; \
               } \
           } \
           if (pthread_mutex_unlock(&__ae2f_osx_mutex) != 0) { \
               errno = EAGAIN; \
               __ret = -1; \
           } \
       } \
       __ret; })

/**
 * @brief Wake one thread waiting on uaddr.
 * @param uaddr Pointer to address (unused, wakes condition variable).
 * @return 0 on success, -1 on error with errno set.
 */
#define __ae2f_osx_wakesingle(uaddr) \
    ({ int __ret = 0; \
       if (pthread_mutex_lock(&__ae2f_osx_mutex) != 0) { \
           errno = EAGAIN; \
           __ret = -1; \
       } else { \
           if (pthread_cond_signal(&__ae2f_osx_cond) != 0) { \
               errno = EAGAIN; \
               __ret = -1; \
           } \
           if (pthread_mutex_unlock(&__ae2f_osx_mutex) != 0) { \
               errno = EAGAIN; \
               __ret = -1; \
           } \
       } \
       __ret; })

#define __ae2f_Wait         __ae2f_osx_wait
#define __ae2f_WakeSingle   __ae2f_osx_wakesingle
#endif

#endif