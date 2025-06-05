/**
 * @file WaitWake.h
 * @todo Give a way for err-handling
 */

#ifdef _WIN32
#include <windows.h>

/**
 * @brief 
 * Address element type.
 */
#define ae2f_addrel_t volatile LONG

/**
 * @def __ae2f_win_wait
 * @param uaddr {ae2f_addrel_t*}
 * @param v     {int}
 * @brief
 * Wait `uaddr` if its value equals to `v`.
 */
#define __ae2f_win_wait(uaddr, v) \
    { int vv = v; WaitOnAddress((uaddr), &vv, sizeof(int), INFINITE); }

/**
 * @def __ae2f_win_wakesingle
 * @param uaddr     {ae2f_addrel_t*}
 */
#define __ae2f_win_wakesingle(uaddr) \
    WakeByAddressSingle((PVOID)(uaddr))

#define __ae2f_WakeSingle   __ae2f_win_wakesingle
#define __ae2f_Wait         __ae2f_win_wait

#else
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