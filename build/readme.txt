
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



  FLAGS
  
  ...
  
  
  
  TROUBLESHOOTING

If you are getting "ELF file OS ABI invalid" error, do:
  elfedit --output-osabi=none niceamx.so
OR (freebsd):
  brandelf -f 0 niceamx.so
  
This will change ELF OS/ABI header to System V

