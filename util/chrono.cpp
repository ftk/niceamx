#include "chrono.hpp"

#ifdef WIN32
//#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#if defined _WIN32_WINNT && _WIN32_WINNT >= 0x6000 && defined __GNUC__
extern "C" WINBASEAPI ULONGLONG WINAPI GetTickCount64(VOID);
#endif

#else
#include <unistd.h>
#include <sys/time.h>
#endif




namespace chrono {

#ifdef WIN32
long long fast_steady_clock::freq = 0LL;
#endif

fast_steady_clock::time_point fast_steady_clock::now()
{
#ifndef WIN32
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC/*_COARSE*/, &ts);
    nanoseconds dur((ts.tv_sec*1000000000LL) + (ts.tv_nsec));
#else
    static_assert(sizeof(long long) == sizeof(_LARGE_INTEGER), "fixme:wrong llong size");
    long long cnt;
    QueryPerformanceCounter(reinterpret_cast<PLARGE_INTEGER>(&cnt));
    if(!freq)
    {
        QueryPerformanceFrequency(reinterpret_cast<PLARGE_INTEGER>(&freq)); // ticks per second
        freq /= 1000000LL; // ticks per microsecond
    }
    microseconds dur(cnt / freq);
#endif

    return time_point(dur);

}

fast_realtime_clock::time_point fast_realtime_clock::now()
{
#ifndef WIN32
    timespec ts;
    clock_gettime(CLOCK_REALTIME/*_COARSE*/, &ts);
    nanoseconds dur((ts.tv_sec*1000000000LL) + (ts.tv_nsec));
#elif defined _WIN32_WINNT && _WIN32_WINNT >= 0x6000
    milliseconds dur(GetTickCount64());
#else
    milliseconds dur(GetTickCount());
#endif
    return time_point(dur);
}






} //chrono
