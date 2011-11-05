cmake_minimum_required (VERSION 2.6)

project (niceamx)

set(EXECUTABLE_OUTPUT_PATH "../..")

SET(MY_OWN_INSTALL_PREFIX "../.." CACHE PATH "Prefix prepended to install directories")
SET(CMAKE_INSTALL_PREFIX "${MY_OWN_INSTALL_PREFIX}" CACHE INTERNAL "Prefix prepended to install directories" FORCE)

add_subdirectory(lib)
add_subdirectory(test)

