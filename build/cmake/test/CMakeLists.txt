project (niceamx-test CXX C)

set (src_dir "${CMAKE_SOURCE_DIR}/../..")

aux_source_directory(${src_dir}/api sources)
aux_source_directory(${src_dir}/system sources)
aux_source_directory(${src_dir}/util sources)

aux_source_directory(${src_dir}/tests sources)

include_directories (
  ${src_dir}/
  ${src_dir}/system/
)

if (CMAKE_COMPILER_IS_GNUCXX)
  set (CMAKE_CXX_FLAGS "-std=c++0x")
endif ()

if (WIN32)
    add_definitions ("-DWIN32")
endif (WIN32)

find_package (Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


add_executable(niceamx-test ${sources})

install (TARGETS niceamx-test DESTINATION "${CMAKE_SOURCE_DIR}/../")

