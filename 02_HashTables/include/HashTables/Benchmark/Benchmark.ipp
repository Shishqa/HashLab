/*============================================================================*/
#ifndef HASHTABLES_RESEARCH_BENCHMARK_IPP
#define HASHTABLES_RESEARCH_BENCHMARK_IPP
/*============================================================================*/
#include "Interface.hpp"
#include "Random.hpp"
#include "Timer.hpp"
#include "HashCollection.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
/*============================================================================*/
namespace Research::Benchmark {

enum QueryType {
    ADD = 1,
    REMOVE,
    FIND
};

template <typename HashSet>
bool test(size_t test_set_size, TimeDelta& delta) {

    std::vector<typename HashSet::Key> test_sample;
    test_sample.reserve(test_set_size);

    for (size_t i = 0; i < test_sample.capacity(); ++i) {
        test_sample.emplace_back(std::move(Random::getValue<typename HashSet::Key>()));
    }

    /*------------------------------------------------------------------------*/

    std::vector<typename HashSet::Key> query_sample = test_sample;
    std::vector<int> query_type(test_sample.size() + query_sample.size());

    std::shuffle(query_sample.begin(), query_sample.end(), Random::Generator());
    for (size_t i = 0; i < test_sample.size() / 2; ++i) {
        query_sample[i] = std::move(Random::getValue<typename HashSet::Key>());
    }
    std::shuffle(query_sample.begin(), query_sample.end(), Random::Generator());

    /*------------------------------------------------------------------------*/

    size_t curr_add = test_sample.size();
    size_t curr_find_remove = query_sample.size();
    for (auto& query : query_type) {
        if (curr_add && Random::tossCoin(0.5)) {
            query = ADD;
            curr_add--;
        } else if (curr_find_remove && Random::tossCoin(0.5)) {
            query = REMOVE;
            curr_find_remove--;
        } else if (curr_find_remove) {
            query = FIND;
            curr_find_remove--;
        } else if (curr_add) {
            query = ADD;
            curr_add--;
        }
    }

    HashSet set;
    std::unordered_set<typename HashSet::Key> check;

    Timer timer = {};

    for (auto& query : query_type) {

        bool check_status = false;
        bool status = false;

        switch (query) {

            case ADD:
                set.add(test_sample[curr_add]);
                check.insert(test_sample[curr_add]);
                status = set.find(test_sample[curr_add]);
                check_status = check.count(test_sample[curr_add]);
                curr_add++;
                break;

            case FIND:
                status = set.find(query_sample[curr_find_remove]);
                check_status = check.count(query_sample[curr_find_remove]);
                curr_find_remove++;
                break;

            case REMOVE:
                status = set.remove(query_sample[curr_find_remove]);
                check_status = check.erase(query_sample[curr_find_remove]);
                curr_find_remove++;
                break;

            default:
                throw std::runtime_error("bad query");
        }

        if (status != check_status) {
            std::cout << "bad test found:\n"
                      << "set " << (status ? "has" : "doesn't have")
                      << " key " << query_sample[curr_find_remove]
                      << "check set " << (check_status ? "has" : "doesn't have")
                      << " key " << query_sample[curr_find_remove]
                      << "\n";
            delta = timer.elapsed();
            return false;
        }
    }

    delta = timer.elapsed();
    return true;
}


template <typename HashSet>
TimeDelta run(size_t test_set_size) {

    std::vector<typename HashSet::Key> test_sample;
    test_sample.reserve(test_set_size);

    for (size_t i = 0; i < test_sample.capacity(); ++i) {
        test_sample.emplace_back(std::move(Random::getValue<typename HashSet::Key>()));
    }

    /*------------------------------------------------------------------------*/

    std::vector<typename HashSet::Key> query_sample = test_sample;
    std::vector<int> query_type(query_sample.size());

    std::shuffle(query_sample.begin(), query_sample.end(), Random::Generator());
    for (size_t i = 0; i < test_sample.size() / 2; ++i) {
        query_sample[i] = std::move(Random::getValue<typename HashSet::Key>());
    }
    std::shuffle(query_sample.begin(), query_sample.end(), Random::Generator());

    /*------------------------------------------------------------------------*/

    for (size_t i = 0; i < query_type.size(); ++i) {
        if (Random::tossCoin(0.1)) {
            query_type[i] = REMOVE;
        } else {
            query_type[i] = FIND;
        }
    }

    HashSet set;

    Timer timer = {}; // timer started

    for (const auto& key : test_sample) {
        set.add(key);
    }

    for (size_t i = 0; i < query_sample.size(); ++i) {
        if (query_type[i] == REMOVE) {
            set.remove(query_sample[i]);
        } else {
            set.find(query_sample[i]);
        }
    }

    return timer.elapsed();
}

/*----------------------------------------------------------------------------*/

template <typename HashSet>
bool run(const std::string_view& filename) {

    static constexpr size_t MIN_SIZE = 10;
    static constexpr size_t MAX_SIZE = 100000000UL;
    static constexpr double DELTA_MUL = 1.5;

    static constexpr size_t N_RUNS = 10;

    std::ofstream out(filename.data());
    if (!out.is_open()) {
        std::cerr << "Error: can't open file " << filename << "!\n"
                  << "Aborting run\n";
        return false;
    }
    out << "size,time\n";

    std::cout << "Running benchmark for " << filename << "\n";

    Timer overall_timer;
    for (size_t size = MIN_SIZE; size <= MAX_SIZE; size = (size_t)((double)size * DELTA_MUL)) {

        TimeDelta elapsed = overall_timer.elapsed();
        if (elapsed.count() > 500000000000LL) { // 8 minutes
            std::cout << "Stopping due to long waiting time (> 8 min)\n";
            break;
        }

        std::cout << "[";
        for (size_t k = MIN_SIZE; k <= MAX_SIZE; k = (size_t)((double)k * DELTA_MUL)) {
            if (k < size) {
                std::cout << "=";
            } else if (k == size) {
                std::cout << ">";
            } else {
                std::cout << "_";
            }
        }
        std::cout << "] counting: " << size << " ("
                  << static_cast<double>(elapsed.count()) / 60000000000.0
                  << " min elapsed)\r";
        std::cout.flush();

        TimeDelta total_time(0);

        for (size_t k = 0; k < N_RUNS; ++k) {
            total_time += run<HashSet>(size);
        }

        out << size << "," << ((total_time / N_RUNS) / size).count() << "\n";
        out.flush();
    }

    out.close();

    std::cout << "Done. Written to " << filename << "\n";
    std::cout.flush();
    return true;
}

/*----------------------------------------------------------------------------*/

#define RUN( Type, Hash ) \
    run<HashSet<Types::Type, Research::Hashes::Hash<Types::Type>>>( \
        set_name + "_" #Type "_" #Hash ".csv"             \
    );                                                              \

template <template<typename, typename> typename HashSet>
void runForAllHashes(const std::string& set_name) {

    std::cout << "TESTING WITH Indep2PolyHash...\n";

    TimeDelta time_elapsed = {};
    const size_t n_test_elements = 1000000;
    for (size_t k = 0; k < 1; ++k) {
        std::cout << "running " << k << " test...";
        std::cout.flush();
        bool status = test<HashSet<Types::Number , Research::Hashes::TabulationHash<Types::Number>>>(
            n_test_elements, time_elapsed
        );
        if (status) {
            std::cout << "\rTest passed in "
                      << std::chrono::duration_cast<std::chrono::seconds>(time_elapsed).count()
                      << " seconds\n";
        } else {
            std::cout << "\rTest not passed (took "
                      << std::chrono::duration_cast<std::chrono::seconds>(time_elapsed).count()
                      << " seconds)\n";
            return;
        }
    }

    /* TODO: multi-thread ? */

    std::cout << "RUNNING FOR NUMBERS...\n";
    RUN(Number, StdHash);
    RUN(Number, TabulationHash);
    RUN(Number, Indep2PolyHash);
    RUN(Number, Indep3PolyHash);
    RUN(Number, Indep5PolyHash);
    RUN(Number, Md5Hash);
    RUN(Number, Sha256Hash);
    RUN(Number, Murmur3Hash);

    std::cout << "RUNNING FOR STRINGS...\n";
    RUN(String, StdHash);
    RUN(String, Md5Hash);
    RUN(String, Sha256Hash);
    RUN(String, DumbHash);
    RUN(String, RabinKarpHash);
    RUN(String, Murmur3Hash);
}

#undef RUN

} // namespace Research::Benchmark
/*============================================================================*/
#endif //HASHTABLES_RESEARCH_BENCHMARK_IPP
/*============================================================================*/