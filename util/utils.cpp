#include "utils.h"

#include <cstring>
#include <ctime>
//#include <time.h>

#ifdef WIN32
#include <windows.h>
#else
//#include <unistd.h>
#include <sys/time.h>
#endif


namespace util {
//

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
}

walltime_t get_walltime()
{
  using namespace std;
  //return clock();
#ifndef WIN32
  // TODO: replace with clock_gettime(CLOCK_MONOTONIC, timespec *)
  timeval tim;
  gettimeofday(&tim, NULL);
  return((tim.tv_sec*1000) + (tim.tv_usec/1000));
  /* 
  // undefined reference, even with -lrt
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return((ts.tv_sec*1000) + (ts.tv_nsec/1000000L));
  */
#else
  return GetTickCount();
#endif
}

walltime_t get_walltime_s() // unix timestamp
{
  using namespace std;
  return (walltime_t) time(NULL);
}

void sleep(long ms)
{
#ifdef WIN32
  Sleep(ms);
#else
  usleep(ms * 1000);
#endif
}

}
