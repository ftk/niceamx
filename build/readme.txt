
  LIBRARIES

This project is using Boost library (headers only): http://www.boost.org/
Warm start:
  svn checkout http://svn.boost.org/svn/boost/trunk ~/boost-trunk # may take long time
  export BOOST_ROOT=~/boost-trunk
  export CPLUS_INCLUDE_PATH="${BOOST_ROOT}" # auto-include for gcc



  COMPILERS
  
Currently supported GCC 4.6 only, but it could be compiled with MSVC10 or MinGW after small fixes



  COMPILING

Linux:
  make all
FreeBSD:
  gmake all 'CXX=g++46' 'CC=gcc46'
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

WIN32

NDEBUG -- disable asserts and internal profiler(called "overtimer")

OVERTIMER_ENABLE
OVERTIMER_DISABLE

MAX_EXEC_TIME=3
MAX_CB_EXEC_TIME=3 -- if callback runs longer, it will be notified
MAX_NATIVE_EXEC_TIME=3
MAX_TIMER_EXEC_TIME=3

PRINT_INCOMING_CALLBACKS -- on_game_mode_init();
PRINT_OUTCOMING_NATIVES -- add_player_class(1, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0);

THREAD_SLEEP_TIME=5 -- 'sleep' option in server.cfg
TIMERS_RESOLUTION=100 -- timers resolution



  
  TROUBLESHOOTING

If you are getting "ELF file OS ABI invalid" error, do:
  elfedit --output-osabi=none niceamx.so
OR (freebsd):
  brandelf -f 0 niceamx.so
  
This will change ELF OS/ABI header to System V

