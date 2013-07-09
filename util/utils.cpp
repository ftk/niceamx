#include "utils.h"

#include <cstring>
#include <ctime>
#include <cstdio>
#include <cstdarg>
//#include <time.h>

#ifdef WIN32
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif

#include "chrono.hpp"


namespace util {
//
/*
hash_t hash(const char * str)
{
  std::size_t len = strlen(str);
  hash_t hash = 2166136261UL;
  while (len--)
  {
	int
		ch = str[len];
	if ('a' <= ch && ch <= 'z')
	{
		ch &= ~0x20;
	}
	hash = (hash ^ ch) * 16777619UL;
  }
  return hash;
}


hash_t hash(const std::string & str)
{
  std::size_t len = str.size();
  hash_t hash = 2166136261UL;
  while (len--)
  {
	int
		ch = str.at(len);
	if ('a' <= ch && ch <= 'z')
	{
		ch &= ~0x20;
	}
	hash = (hash ^ ch) * 16777619UL;
  }
  return hash;
}*/


walltime_t get_walltime() // deprecated
{
#if 0
  using namespace std;
  //return clock();
#ifndef WIN32
  // TODO: replace with clock_gettime(CLOCK_MONOTONIC, timespec *)
  timeval tim;
  gettimeofday(&tim, NULL);
  return((tim.tv_sec*1000ULL) + (tim.tv_usec/1000ULL));
  /* 
  // undefined reference, even with -lrt
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return((ts.tv_sec*1000) + (ts.tv_nsec/1000000L));
  */
//#elif defined _WIN32_WINNT && _WIN32_WINNT >= 0x6000
//  return GetTickCount64();
#else
  return GetTickCount();
#endif
#else
    return chrono::duration_cast<chrono::milliseconds>(
                chrono::fast_steady_clock::now().time_since_epoch()).count();
#endif
}

walltime_t get_walltime_s() // unix timestamp
{
  //using namespace std;
  return (walltime_t) std::time(NULL);
}

void sleep(long ms)
{
#ifdef WIN32
  Sleep(ms);
#else
  usleep(ms * 1000L);
#endif
}
/*
std::string sprintf(const char * format, ...)
{
  char buffer[256];
  va_list args;
  va_start(args, format);
  int len = vsnprintf(buffer, 255, format, args);
  buffer[len] = '\0';
  va_end(args);
  return buffer;
}*/


/* http://stackoverflow.com/a/8098080 */
std::string sprintf(const char * format, ...)
{
    int size = 128;
    std::string str;
    va_list ap;
    while(true)
    {
        str.resize(size);
        va_start(ap, format);
        int n = ::vsnprintf(&(str[0]), size, format, ap);
        va_end(ap);
        if (n > -1 && n < size)
        {
            str.resize(n);
            return std::move(str);
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return std::move(str);
}

std::string vsprintf(const char * format, va_list args)
{
    int size = 128;
    std::string str;
    va_list ap;
    while(true)
    {
        str.resize(size);
        va_copy(ap, args);
        int n = ::vsnprintf(&(str[0]), size, format, ap);
        va_end(ap);
        if (n > -1 && n < size)
        {
            str.resize(n);
            return std::move(str);
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return std::move(str);
}
/*
int snprintf(std::string& out, std::size_t size, const char * format, ...)
{
    out.resize(size);
    va_list ap;
    va_start(ap, format);
    int n = vsnprintf(&(out[0]), size, format, ap);
    va_end(ap);
    if (n >= 0 && static_cast<unsigned>(n) < size)
    {
        out.resize(n);
    }
    else if(n < 0)
        out.clear();
    return n;
}*/



}

