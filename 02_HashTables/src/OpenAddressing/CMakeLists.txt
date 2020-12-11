add_library(OpenAddressing)

set(INCROOT ${PROJECT_SOURCE_DIR}/include/HashTables/OpenAddressing)

target_include_directories(OpenAddressing
  PUBLIC
    ${INCROOT}
  )

target_sources(OpenAddressing
  PUBLIC
    ${INCROOT}/OpenAddressing.hpp
  PRIVATE
    ${INCROOT}/OpenAddressing.ipp
    ${INCROOT}/Runs.ipp
  )

target_link_libraries(OpenAddressing
  PUBLIC
    Interface
    Hashes
  )