#ifndef INCLUDE_TIMESPEC_H
#define INCLUDE_TIMESPEC_H 1

#include <features.h>
#include <time.h>

#include <stdbool.h>


static inline bool timespec_eq(struct timespec a, struct timespec b){
    return a.tv_sec == b.tv_sec && a.tv_nsec == b.tv_nsec;
}

static inline bool timespec_neq(struct timespec a, struct timespec b){
    return a.tv_sec != b.tv_sec || a.tv_nsec != b.tv_nsec;
}

static inline bool timespec_lt(struct timespec a, struct timespec b){
    return a.tv_sec < b.tv_sec ||
           (a.tv_sec == b.tv_sec && a.tv_nsec < b.tv_nsec);
}

static inline bool timespec_le(struct timespec a, struct timespec b){
    return a.tv_sec < b.tv_sec ||
           (a.tv_sec == b.tv_sec && a.tv_nsec <= b.tv_nsec);
}

static inline bool timespec_gt(struct timespec a, struct timespec b){
    return a.tv_sec > b.tv_sec ||
           (a.tv_sec == b.tv_sec && a.tv_nsec > b.tv_nsec);
}

static inline bool timespec_ge(struct timespec a, struct timespec b){
    return a.tv_sec > b.tv_sec ||
           (a.tv_sec == b.tv_sec && a.tv_nsec >= b.tv_nsec);
}

static inline struct timespec timespec_make(time_t sec, long nsec){
    struct timespec ret;
    ret.tv_sec = sec;
    ret.tv_nsec = nsec;
    return ret;
}

static inline struct timespec timespec_neg(struct timespec t){
    if ( t.tv_nsec )
        return timespec_make(-t.tv_sec - 1, 1000000000 - t.tv_nsec);
    return timespec_make(-t.tv_sec, 0);
}

static inline struct timespec timespec_nul(){
    return timespec_make(0, 0);
}

struct timespec timespec_canonalize(struct timespec t);
struct timespec timespec_add(struct timespec a, struct timespec b);
struct timespec timespec_sub(struct timespec a, struct timespec b);


#endif
