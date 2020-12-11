/*============================================================================*/
#include <iostream>
#include <algorithm>
#include <filesystem>

#include "Benchmark.hpp"
#include "HashCollection.hpp"
#include "OpenAddressing.hpp"
/*============================================================================*/
using namespace Research;
using namespace Research::Types;
/*============================================================================*/

int main(int argc, const char* argv[]) {

    if (argc != 2) {
        std::cout << "Usage: " << (argc ? argv[0] : "RunBenchmarks")  << " [folder for results]\n";
        return 1;
    }

    std::filesystem::current_path(argv[1]);

    Benchmark::run<HashTables::OpenAddressingLinear<String, std::hash>>(
        "OpenAddressing-LinearRun-StdHash.csv"
        );

    return 0;
}

/*============================================================================*/