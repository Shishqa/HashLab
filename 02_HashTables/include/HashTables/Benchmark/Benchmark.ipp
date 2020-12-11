/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_BENCHMARK_IPP
#define HASHTABLES_RESEARCH_BENCHMARK_IPP
/*============================================================================*/
#include "Interface.hpp"
#include "Random.hpp"
#include "Timer.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
/*============================================================================*/
namespace Research::Benchmark {

template <typename HashSet>
TimeDelta run(size_t test_set_size) {

    std::vector<typename HashSet::Type> test_sample;
    test_sample.reserve(test_set_size);

    for (size_t i = 0; i < test_sample.capacity(); ++i) {
        test_sample.emplace_back(Random::getValue<typename HashSet::Type>());
    }

    /*------------------------------------------------------------------------*/

    std::vector<typename HashSet::Type> query_sample = test_sample;

    std::shuffle(query_sample.begin(), query_sample.end(), Random::Generator());
    for (size_t i = 0; i < test_sample.size() / 2; ++i) {
        query_sample[i] = std::move(Random::getValue<typename HashSet::Type>());
    }
    std::shuffle(query_sample.begin(), query_sample.end(), Random::Generator());

    /*------------------------------------------------------------------------*/

    HashSet set;

    Timer timer = {};

    for (const auto& key : test_sample) {
        set.add(key);
    }

    for (const auto& query : query_sample) {
        if (Random::tossCoin(0.1)) {
            set.remove(query);
        } else {
            set.find(query);
        }
    }

    return timer.elapsed();
}

template <typename HashSet>
bool run(const char* filename) {

    static constexpr size_t MIN_SIZE = 10;
    static constexpr size_t MAX_SIZE = 100000000UL;
    static constexpr double DELTA_MUL = 1.5;

    static constexpr size_t N_RUNS = 10;

    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("can't open file!");
    }

    std::cout << "Running benchmark for " << typeid(HashSet).name() << "\n";

    for (size_t size = MIN_SIZE; size <= MAX_SIZE; size = (size_t)((double)size * DELTA_MUL)) {

        TimeDelta total_time(0);

        for (size_t k = 0; k < N_RUNS; ++k) {
            total_time += run<HashSet>(size);
        }

        std::cout << "[";
        for (size_t k = MIN_SIZE; k <= MAX_SIZE; k = (size_t)((double)k * DELTA_MUL)) {
            if (k < size) {
                std::cout << "=";
            } else if (k == size) {
                std::cout << ">";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "] " << size << "\r";
        std::cout.flush();

        out << size << ";" << ((total_time / N_RUNS) / size).count() << "\n";
        out.flush();
    }

    out.close();

    std::cout << "Done. Written to " << filename << "\n";
    std::cout.flush();
    return true;
}

} // namespace Research::Benchmark
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_BENCHMARK_IPP
/*============================================================================*/