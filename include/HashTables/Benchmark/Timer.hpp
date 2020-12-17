/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_TIMER_HPP
#define HASHTABLES_RESEARCH_TIMER_HPP
/*============================================================================*/
#include <chrono>
/*============================================================================*/
namespace Research::Benchmark {

    using Clock     = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    using TimeDelta = std::chrono::nanoseconds;

    /*------------------------------------------------------------------------*/

    class Timer {
    public:

        Timer();

        virtual ~Timer() = default;

        void reset();

        [[nodiscard]]
        TimeDelta elapsed() const;

    protected:

        TimePoint start_time;

    };

}
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_TIMER_HPP
/*============================================================================*/