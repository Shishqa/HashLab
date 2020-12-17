# Hash-Tables benchmark

To run benchmark with your lovely hash-set with all hashes in collection:
```c++
Benchmark::runForAllHashes<YourLovelySet>("YourLovelySet");
```

To build and run:
```shell
mkdir build
cd build
cmake ../
cmake --build . --target=RunBenchmarks
./RunBenchmarks output/
```

Ready hash-tables:

- OpenAddressing
    - Linear probing
    - Quadratic probing
    - Double Hashing
- SeparateChaining
- CuckooHashing

Benchmark results can be found [there](./results)