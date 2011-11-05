
aux_source_directory(../../../api sources)
aux_source_directory(../../../system sources)
aux_source_directory(../../../util sources)

aux_source_directory(../../../system/pawn sources)
aux_source_directory(../../../system/SDK sources)

include_directories (
  ../../../
  ../../../system/
)

set (CMAKE_MODULE_LIBRARY_PREFIX ) # set empty prefix
set (CMAKE_SHARED_MODULE_PREFIX "")

if (CMAKE_COMPILER_IS_GNUCXX)
#  add_definitions(-std=c++0x)
  set (CMAKE_CXX_FLAGS "-std=c++0x")
endif ()

if (UNIX AND CMAKE_COMPILER_IS_GNUCXX)
    add_definitions (-DLINUX)
    set (CMAKE_MODULE_LINKER_FLAGS "-Wl,--no-undefined")
endif (UNIX AND CMAKE_COMPILER_IS_GNUCXX)

set (DEFFILE "../../win/plugin.def")

if (WIN32)
    add_definitions (-DWIN32)
    if (MSVC)
        if (MSVC_VERSION LESS 1600)
            message (FATAL_ERROR "Need VC++ version 10.0 or higher to compile successfully")
        endif (MSVC_VERSION LESS 1600)
        set (CMAKE_MODULE_LINKER_FLAGS /DEF:${DEFFILE})
    elseif (MINGW)
        set (CMAKE_MODULE_LINKER_FLAGS "-Wl,--kill-at --def ${DEFFILE}")
    endif (MSVC)
endif (WIN32)
#if (MSVC)
#set (CMAKE_MODULE_LINKER_FLAGS ${CMAKE_MODULE_LINKER_FLAGS} ) # todo: add /export: flags
#endif ()

find_package (Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})



add_library(niceamx MODULE ${sources})

target_link_Libraries(niceamx)

install (TARGETS niceamx DESTINATION server/plugins)

