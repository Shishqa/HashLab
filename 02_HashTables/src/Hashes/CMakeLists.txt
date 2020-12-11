add_library(Hashes)

set(INCROOT ${PROJECT_SOURCE_DIR}/include/HashTables/Hashes)

target_include_directories(Hashes
  PUBLIC
    ${INCROOT}
  PRIVATE
    ./
  )

target_sources(Hashes
  PUBLIC
    ${INCROOT}/HashCollection.hpp
  PRIVATE
    Md5Hash.cpp
    Sha256Hash.cpp
    DumbHash.cpp
    RabinKarpHash.cpp
    Murmur3Hash.cpp
  )

target_link_libraries(Hashes
  PUBLIC
    Interface
  )

target_compile_features(Hashes
  PUBLIC
    cxx_std_17
  )