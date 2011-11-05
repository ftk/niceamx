#project(niceamx-test)
aux_source_directory(../../../api sources)
aux_source_directory(../../../system sources)
aux_source_directory(../../../util sources)

aux_source_directory(../../../tests sources)

include_directories (
  ../../../
  ../../../system/
)

if (CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-std=c++0x -ggdb3 -O0)
endif ()


find_package (Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})



add_executable(niceamx-test ${sources})
install (TARGETS niceamx-test DESTINATION build)

