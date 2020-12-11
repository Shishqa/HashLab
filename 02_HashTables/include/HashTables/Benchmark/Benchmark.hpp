/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_BENCHMARK_HPP
#define HASHTABLES_RESEARCH_BENCHMARK_HPP
/*============================================================================*/
#include "Timer.hpp"
#include <map>
#include <string_view>
/*============================================================================*/
namespace Research::Benchmark {

    template <typename HashSet>
    bool run(const char* filename);

    template <typename HashSet>
    TimeDelta run(size_t test_set_size);

}
/*============================================================================*/
#include "Benchmark.ipp"
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_BENCHMARK_HPP
/*============================================================================*/