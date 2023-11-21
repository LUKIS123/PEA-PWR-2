#include "Timer.h"

using namespace std;

long long int Timer::read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}

double Timer::getMicroSecondsElapsed(long long int start, long long int end) {
    long long int elapsed, frequency;
    elapsed = end - start;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    return ((1000000.0 * elapsed) / frequency);
}

double Timer::getMilliSecondsElapsed(long long int start, long long int end) {
    long long int elapsed, frequency;
    elapsed = end - start;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    return ((1000.0 * elapsed) / frequency);
}

double Timer::getSecondsElapsed(long long int start, long long int end) {
    long long int elapsed, frequency;
    elapsed = end - start;
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
    return (elapsed / frequency);
}
