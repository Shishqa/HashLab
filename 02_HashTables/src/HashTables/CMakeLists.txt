set(INCROOT ${PROJECT_SOURCE_DIR}/include/HashTables/HashTables/)


add_library(OpenAddressing)

target_include_directories(OpenAddressing
  PUBLIC
    ${INCROOT}/OpenAddressing
  )

target_sources(OpenAddressing
  PUBLIC
    ${INCROOT}/OpenAddressing/OpenAddressing.hpp
  PRIVATE
    ${INCROOT}/OpenAddressing/OpenAddressing.ipp
    ${INCROOT}/OpenAddressing/Runs.ipp
  )

target_link_libraries(OpenAddressing
  PUBLIC
    Interface
  )


add_library(SeparateChaining)

target_include_directories(SeparateChaining
  PUBLIC
    ${INCROOT}/SeparateChaining
  )

target_sources(SeparateChaining
  PUBLIC
    ${INCROOT}/SeparateChaining/SeparateChaining.hpp
  PRIVATE
    ${INCROOT}/SeparateChaining/SeparateChaining.ipp
  )

target_link_libraries(SeparateChaining
  PUBLIC
    Interface
  )


add_library(Cuckoo)

target_include_directories(Cuckoo
  PUBLIC
  ${INCROOT}/Cuckoo
  )

target_sources(Cuckoo
  PUBLIC
  ${INCROOT}/Cuckoo/Cuckoo.hpp
  PRIVATE
  ${INCROOT}/Cuckoo/Cuckoo.ipp
  )

target_link_libraries(Cuckoo
  PUBLIC
  Interface
  )


add_library(HashTables INTERFACE)

target_sources(HashTables
  INTERFACE
    ${INCROOT}/HashTables.hpp
  )

target_include_directories(HashTables
  INTERFACE
    ${INCROOT}
  )

target_link_libraries(HashTables
  INTERFACE
    OpenAddressing
    SeparateChaining
    Cuckoo
  )
