#============================================================================#

cmake_minimum_required(VERSION 3.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

project(HashTables-Research)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(DEFAULT_BUILD_TYPE "Release")

  set(CMAKE_CXX_EXTENSIONS OFF)

  set(RELEASE_FLAGS " \
    -O3 \
    -Wno-unused-parameter \
  ")

  set(DEBUG_FLAGS " \
    -g \
    -O3 \
    -Wconversion \
    -Wlogical-op \
    -Wshift-overflow=2 \
		-Wduplicated-cond \
		-Wno-unused-parameter \
		-Wcast-qual -Wcast-align \
		-D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
		-D_FORTIFY_SOURCE=2 -fsanitize=address \
		-fsanitize=undefined -fno-sanitize-recover \
		-fstack-protector -Wno-format-nonliteral \
    -fno-omit-frame-pointer \
  ")

  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS}")
  set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} ${DEBUG_FLAGS}")

  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS}")
  set (CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} ${RELEASE_FLAGS}")

  if (MSVC)
    add_compile_options(/W3 /WX)
  else()
    add_compile_options(-W -Wall -Wextra -Wpedantic -Werror -pedantic-errors)
  endif()

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

endif()

#============================================================================#

set(INCROOT ${PROJECT_SOURCE_DIR}/include/HashTables)

add_library(Interface INTERFACE)

target_include_directories(Interface
  INTERFACE
    ${INCROOT}
  )

target_sources(Interface
  INTERFACE
    ${INCROOT}/Interface.hpp
  )

target_compile_features(Interface
  INTERFACE
    cxx_std_17
  )

#============================================================================#

add_library(HashTables INTERFACE)

target_include_directories(HashTables
  INTERFACE
    ${INCROOT}
  )

target_link_libraries(HashTables
  INTERFACE
    OpenAddressing
  )

#============================================================================#

add_executable(RunBenchmarks)

target_include_directories(RunBenchmarks
  PRIVATE
    ${INCROOT}
  )

target_sources(RunBenchmarks
  PRIVATE
    src/main.cpp
  )

target_link_libraries(RunBenchmarks
  PRIVATE
    HashTables
    Benchmark
  )

add_subdirectory(src/Hashes)
add_subdirectory(src/Benchmark)
add_subdirectory(src/OpenAddressing)

#============================================================================#
