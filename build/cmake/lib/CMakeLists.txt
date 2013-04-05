project (niceamx CXX C)


set (src_dir "${CMAKE_SOURCE_DIR}/../..")


#aux_source_directory(${src_dir}/api sources)
#aux_source_directory(${src_dir}/system sources)
#aux_source_directory(${src_dir}/util sources)

#aux_source_directory(${src_dir}/system/pawn sources)
#aux_source_directory(${src_dir}/system/SDK sources)
file(GLOB sources ${src_dir}/api *.cpp)
file(GLOB sources ${src_dir}/system *.cpp)
file(GLOB sources ${src_dir}/util *.cpp)
file(GLOB sources ${src_dir}/system/SDK *.cpp)
file(GLOB sources ${src_dir}/system/pawn *.cpp)



include_directories (
  ${src_dir}/
  ${src_dir}/system/
)

include(CheckIncludeFile)

function(check_include_and_define include_file define)
    check_include_file(${include_file} HAVE_${include_file})
    if(HAVE_${include_file})
        add_definitions(-D${define})
    endif()
endfunction()

check_include_and_define("alloca.h" "HAVE_ALLOCA_H")
check_include_and_define("inttypes.h" "HAVE_INTTYPES_H")
check_include_and_define("malloc.h" "HAVE_MALLOC_H")
check_include_and_define("stdint.h" "HAVE_STDINT_H")


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)


set (CMAKE_MODULE_LIBRARY_PREFIX "") # set empty prefix
#set (CMAKE_SHARED_MODULE_PREFIX "")

if (CMAKE_COMPILER_IS_GNUCXX)
  set (CMAKE_CXX_FLAGS "-std=c++0x")
  if (UNIX)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
      add_definitions("-DLINUX")
    endif()
    if(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
      add_definitions("-DFREEBSD")
    endif()
    set (CMAKE_MODULE_LINKER_FLAGS "-Wl,--no-undefined")
  endif (UNIX)
endif (CMAKE_COMPILER_IS_GNUCXX)

set (DEFFILE "../../win/plugin.def")

if (WIN32)
    add_definitions ("-DWIN32")
    if (MSVC)
        if (MSVC_VERSION LESS 1600)
            message (FATAL_ERROR "Need VC++ version 10.0 or higher to compile successfully")
        endif (MSVC_VERSION LESS 1600)
        set (CMAKE_MODULE_LINKER_FLAGS "/DEF:${DEFFILE}")
    elseif (MINGW)
        set (CMAKE_MODULE_LINKER_FLAGS "-Wl,--kill-at --def ${DEFFILE}")
    endif ()
endif (WIN32)

find_package (Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set (libs "")


add_library (niceamx MODULE ${sources})
set_target_properties (niceamx PROPERTIES PREFIX "" )
set_target_properties(niceamx PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(niceamx ${libs})

install (TARGETS niceamx DESTINATION ${src_dir}/server/plugins)
#install (TARGETS niceamx DESTINATION lib)

