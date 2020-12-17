/*============================================================================*/
#include "Benchmark/Timer.hpp"
/*============================================================================*/
using namespace Research::Benchmark;
/*============================================================================*/

Timer::Timer() : start_time(Clock::now()) {}

/*----------------------------------------------------------------------------*/

void Timer::reset() {
    start_time = Clock::now();
}

/*----------------------------------------------------------------------------*/

TimeDelta Timer::elapsed() const {
    TimePoint now = Clock::now();
    return now - start_time;
}

/*============================================================================*/