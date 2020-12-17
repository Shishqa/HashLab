set(INCROOT ${PROJECT_SOURCE_DIR}/include/HashTables/Benchmark)

add_library(Benchmark)

target_include_directories(Benchmark
  PUBLIC
    ${INCROOT}
  PRIVATE
    ./
  )

target_sources(Benchmark
  PUBLIC
    ${INCROOT}/Benchmark.hpp
    ${INCROOT}/Benchmark.ipp
    ${INCROOT}/Timer.hpp
  PRIVATE
    Timer.cpp
  )

target_link_libraries(Benchmark
  PUBLIC
    Interface
    Hashes
  )