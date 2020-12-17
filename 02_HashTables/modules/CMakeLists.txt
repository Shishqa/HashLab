add_library(HashLibrary)

set(SRCROOT ${PROJECT_SOURCE_DIR}/modules/hash-library/)

target_include_directories(HashLibrary
  PUBLIC
    ${SRCROOT}
  )

target_sources(HashLibrary
  PUBLIC
    ${SRCROOT}/md5.h
    ${SRCROOT}/sha256.h
  PRIVATE
    ${SRCROOT}/md5.cpp
    ${SRCROOT}/sha256.cpp
  )