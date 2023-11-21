#ifndef PEA_PWR_2_TIMER_H
#define PEA_PWR_2_TIMER_H


#include <windows.h>
#include <iostream>
#include <iomanip>

class Timer {
public:
    static long long int read_QPC();

    static double getMicroSecondsElapsed(long long int start, long long int end);

    static double getMilliSecondsElapsed(long long int start, long long int end);

    static double getSecondsElapsed(long long int start, long long int end);
};

#endif //PEA_PWR_2_TIMER_H
