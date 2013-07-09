
  LIBRARIES

This project is using Boost library (headers only): http://www.boost.org/
Warm start:
  svn checkout http://svn.boost.org/svn/boost/trunk ~/boost-trunk # may take long time
  export BOOST_ROOT=~/boost-trunk
  export CPLUS_INCLUDE_PATH="${BOOST_ROOT}" # auto-include for gcc



  COMPILERS
  
Currently supported GCC 4.7 and MinGW GCC 4.7, but it could be compiled with MSVC11 after few fixes



  COMPILING

Linux:
  make all
FreeBSD:
  gmake all 'CXX=g++47' 'CC=gcc47'
Windows/MinGW: TODO
  ./win/configure-mingw
  make -f mingw.mk
CMake: http://www.cmake.org/
  cd cmake
  cmake ./
  make
Cross-Compiling (Ubuntu MinGW32 example)
  sudo apt-get install gcc-mingw-w64
  ./win/configure-mingw --cc i686-w64-mingw32-g++
  make -f mingw.mk



  GCC FLAGS
  
-c -shared
  Control the kind of output. http://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html
-m32
  Compile for x86 platform
-O3
  Max optimization level
-Wall -Wextra -Wconvert
  Max warning level
-fPIC
  google://positional+independent+code
-ffunction-sections -fdata-sections -Wl,--gc-sections
  Remove unused functions and data from binary.
  To see what has been removed: -Wl,--print-gc-sections
-fstrict-aliasing -fmerge-all-constants -fomit-frame-pointer
  Various optimizations.
-static-libstdc++ -static-libgcc
  Link libstdc++ statically. Useful when target machine has older libstdc++.


  DEFINES

WIN32 -- windows api

NDEBUG -- disable asserts

PRINT_INCOMING_CALLBACKS -- on_game_mode_init();
PRINT_OUTCOMING_NATIVES -- add_player_class(1, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0);


