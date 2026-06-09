#define _POSIX_C_SOURCE 199309L
#include "timer.h"
#include <time.h>

TimePoint getTimePoint(void){
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);

  TimePoint t;
  t.sec = ts.tv_sec;
  t.nsec = ts.tv_nsec;
  return t;
}

double elapsedSeconds(TimePoint start, TimePoint end){
  long sec = end.sec - start.sec;
  long nsec = end.nsec - start.nsec;
  return (double)sec + (double)nsec / 1000000000.0;
}
