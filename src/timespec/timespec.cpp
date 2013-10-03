#include <time.h>
#include "timespec.h"

static const long NANOSECONDS_PER_SECOND = 1000000000L;

static long proper_modulo(long a, long b){
    if ( 0 <= a )
        return a % b;
    long tmp = - (unsigned long) a % b;
    return tmp ? tmp : 0;
}

struct timespec timespec_canonalize(struct timespec t){
    t.tv_sec += t.tv_nsec / NANOSECONDS_PER_SECOND;
    t.tv_nsec = proper_modulo(t.tv_nsec, NANOSECONDS_PER_SECOND);
    return t;
}

struct timespec timespec_add(struct timespec a, struct timespec b){
    struct timespec ret;
    a = timespec_canonalize(a);
    b = timespec_canonalize(b);
    ret.tv_sec = a.tv_sec + b.tv_sec;
    ret.tv_nsec = a.tv_nsec + b.tv_nsec;
    return timespec_canonalize(ret);
}

struct timespec timespec_sub(struct timespec a, struct timespec b){
    a = timespec_canonalize(a);
    b = timespec_canonalize(b);
    return timespec_add(a, timespec_neg(b));
}
