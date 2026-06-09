#ifndef TIMER_H
#define TIMER_H

typedef struct {
  long sec;
  long nsec;
} TimePoint;

TimePoint getTimePoint(void);
double elapsedSeconds(TimePoint start, TimePoint end);

#endif
