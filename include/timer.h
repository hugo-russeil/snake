#ifndef TIMER_H
#define TIMER_H

#include <time.h>

extern struct timespec waitTime;

void setupTimer(struct timespec* timer, long nanoseconds);
long calculateWaitTime(int score);



#endif // TIMER_H