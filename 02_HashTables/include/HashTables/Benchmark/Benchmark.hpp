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
    bool run(const std::string_view& filename);

    template <template<typename, typename> typename HashSet>
    void runForAllHashes(const std::string& set_name);

    template <typename HashSet>
    TimeDelta run(size_t test_set_size);

    template <typename HashSet>
    bool test(size_t test_set_size, TimeDelta& delta);

}
/*============================================================================*/
#include "Benchmark.ipp"
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_BENCHMARK_HPP
/*============================================================================*/