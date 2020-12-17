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
    ${INCROOT}/HashCollection.ipp
    HashCollection.cpp
  )

target_link_libraries(Hashes
  PUBLIC
    Interface
  PRIVATE
    HashLibrary
  )

target_compile_features(Hashes
  PUBLIC
    cxx_std_17
  )