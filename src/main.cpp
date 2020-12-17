/*============================================================================*/
#include <iostream>
#include <filesystem>

#include "Benchmark.hpp"
#include "HashTables.hpp"
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

    Benchmark::runForAllHashes<HashTables::OpenAddressingLinear>("OpenLinear");
    Benchmark::runForAllHashes<HashTables::OpenAddressingQuadratic>("OpenQuadratic");
    Benchmark::runForAllHashes<HashTables::OpenAddressingDoubleHasing>("OpenDoubleHashing");

    Benchmark::runForAllHashes<HashTables::SeparateChaining75>("SeparateChaining75");
    Benchmark::runForAllHashes<HashTables::SeparateChaining95>("SeparateChaining95");

    Benchmark::runForAllHashes<HashTables::Cuckoo>("Cuckoo");

    return 0;
}

/*============================================================================*/