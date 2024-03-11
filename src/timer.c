#include <string.h>

#include "timer.h"
#include "score.h"

struct timespec waitTime = {0, 100000000};

void setupTimer(struct timespec* timer, long nanoseconds){ 
    timer->tv_sec = 0;
    timer->tv_nsec = nanoseconds;
}

long calculateWaitTime(int score){
    long newWaitTime = 100000000 - (score * 2000000);
    if (newWaitTime < 10000) { // minimum wait time of 10,000 nanoseconds
        newWaitTime = 10000;
    }
    return newWaitTime;
}
