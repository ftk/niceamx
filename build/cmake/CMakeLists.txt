cmake_minimum_required (VERSION 2.6)

#include(CPack)

set(EXECUTABLE_OUTPUT_PATH "../..")

add_subdirectory(lib)
add_subdirectory(test EXCLUDE_FROM_ALL)

