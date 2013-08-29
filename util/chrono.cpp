#include "config.h"
#include "chrono.hpp"

#ifdef WIN32
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// workaround for mingw 4.7
#if defined _WIN32_WINNT && _WIN32_WINNT >= 0x6000 && defined __GNUC__ && (__GNUC__ * 100 + __GNUC_MINOR__) < 408
extern "C" WINBASEAPI ULONGLONG WINAPI GetTickCount64(VOID);
#endif

#else
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#endif

#include <utility>
#include <cassert>
#include <ctime>


namespace chrono {

#ifdef WIN32
long long fast_steady_clock::freq = 0LL;
#endif

fast_steady_clock::time_point fast_steady_clock::now() noexcept
{
#ifndef WIN32
    timespec ts;
    if(clock_gettime(CLOCK_MONOTONIC/*_COARSE*/, &ts))
    {
    	assert(false && "clock_gettime(CLOCK_MONOTONIC) failed");
    }
    nanoseconds dur((static_cast<rep>(ts.tv_sec)*1000000000) + (ts.tv_nsec));
#else
    static_assert(sizeof(long long) == sizeof(_LARGE_INTEGER), "fixme:wrong llong size");
    long long cnt;
    if(!QueryPerformanceCounter(reinterpret_cast<PLARGE_INTEGER>(&cnt)))
    {
    	assert(false && "QPC failed");
    }
    if(!freq)
    {
        if(!QueryPerformanceFrequency(reinterpret_cast<PLARGE_INTEGER>(&freq))) // ticks per second
        {
        	assert(false && "QPF failed");
        }
        freq /= 1000000LL; // ticks per microsecond
    }
    microseconds dur(cnt / freq);
#endif

    return time_point(std::move(dur));

}

fast_realtime_clock::time_point fast_realtime_clock::now() noexcept
{
#ifndef WIN32
    timespec ts;
    if(clock_gettime(CLOCK_REALTIME/*_COARSE*/, &ts))
    {
    	assert(false && "clock_gettime(CLOCK_REALTIME) failed");
    }
    nanoseconds dur((static_cast<rep>(ts.tv_sec)*1000000000) + (ts.tv_nsec));
#elif defined _WIN32_WINNT && _WIN32_WINNT >= 0x6000
    milliseconds dur(GetTickCount64());
#else
    milliseconds dur(GetTickCount());
#endif
    return time_point(std::move(dur));
}


process_real_cpu_clock::time_point process_real_cpu_clock::now() noexcept
{
    clock_t c = ::clock();
    if(c == clock_t(-1)) // error
    {
        assert(false && "clock() failed");
    }
    typedef std::ratio_divide<std::giga, std::ratio<CLOCKS_PER_SEC> >::type R;
    return time_point(
      duration(static_cast<rep>(c)*R::num/R::den)
    );
}

#ifdef WIN32

process_user_cpu_clock::time_point process_user_cpu_clock::now() noexcept
{

    //  note that Windows uses 100 nanosecond ticks for FILETIME
    _FILETIME creation, exit, user_time, system_time;

    if (GetProcessTimes(
            GetCurrentProcess(), &creation, &exit,
            &system_time, &user_time ))
    {
        return time_point(duration(
                ((static_cast<process_user_cpu_clock::rep>(user_time.dwHighDateTime) << 32)
                  | user_time.dwLowDateTime) * 100
                ));
    }
    else
    {
        assert(false && "GetProcessTimes failed");
        return time_point();
    }

}


process_system_cpu_clock::time_point process_system_cpu_clock::now() noexcept
{
    //  note that Windows uses 100 nanosecond ticks for FILETIME
    _FILETIME creation, exit, user_time, system_time;

    if (GetProcessTimes(
            GetCurrentProcess(), &creation, &exit,
            &system_time, &user_time))
    {
        return time_point(duration(
                ((static_cast<process_system_cpu_clock::rep>(system_time.dwHighDateTime) << 32)
                                    | system_time.dwLowDateTime) * 100
                ));
    }
    else
    {
        assert(false && "GetProcessTimes failed");
        return time_point();
    }
}

thread_clock::time_point thread_clock::now() noexcept
{

    //  note that Windows uses 100 nanosecond ticks for FILETIME
    _FILETIME creation, exit, user_time, system_time;

    if (GetThreadTimes(
            GetCurrentThread(), &creation, &exit,
            &system_time, &user_time))
    {
        duration user   = duration(
                ((static_cast<duration::rep>(user_time.dwHighDateTime) << 32)
                        | user_time.dwLowDateTime) * 100 );

        duration system = duration(
                ((static_cast<duration::rep>(system_time.dwHighDateTime) << 32)
                        | system_time.dwLowDateTime) * 100 );

        return time_point(system+user);
    }
    else
    {
        assert(false && "GetThreadTimes failed");
        return time_point();
    }
}



#else
// posix
static inline long tick_factor()        // multiplier to convert ticks
                          //  to nanoseconds; -1 if unknown
{
  static long factor = 0;
  if ( !factor )
  {
    if ((factor = ::sysconf( _SC_CLK_TCK )) <= 0)
      factor = -1;
    else
    {
      assert( factor <= 1000000000l ); // doesn't handle large ticks
      factor = 1000000000l / factor;  // compute factor
      if ( !factor ) factor = -1;
    }
  }
  return factor;
}

process_real_cpu_clock::time_point process_real_cpu_clock::now() noexcept
{
    tms tm;
    clock_t c = ::times( &tm );
    if (c == clock_t(-1)) // error
    {
      assert(false && "times() failed");
    }
    else
    {
        if(tick_factor() != -1)
        {
            return time_point(
                    nanoseconds(c*chrono_detail::tick_factor()));
        }
        else
        {
            assert(false && "CLK_TCK failed");
        }
    }
    return time_point();
}

process_user_cpu_clock::time_point process_user_cpu_clock::now() noexcept
{
    tms tm;
    clock_t c = ::times( &tm );
    if (c == clock_t(-1)) // error
    {
      assert(false && "times() failed");
    }
    else
    {
        if(tick_factor() != -1)
        {
            return time_point(
                nanoseconds((tm.tms_utime + tm.tms_cutime)*tick_factor()));
        }
        else
        {
            assert(false && "CLK_TCK failed");
        }
    }
    return time_point();
}


process_system_cpu_clock::time_point process_system_cpu_clock::now() noexcept
{
    tms tm;
    clock_t c = ::times( &tm );
    if (c == clock_t(-1)) // error
    {
      assert(false && "times() failed");
    }
    else
    {
        if(tick_factor() != -1)
        {
            return time_point(
                nanoseconds((tm.tms_stime + tm.tms_cstime)*tick_factor()));
        }
        else
        {
            assert(false && "CLK_TCK failed");
        }
    }
    return time_point();
}

thread_clock::time_point thread_clock::now( ) BOOST_NOEXCEPT
{
    struct timespec ts;
#if defined CLOCK_THREAD_CPUTIME_ID
    // get the timespec associated to the thread clock
    if(::clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts))
#else
    // get the current thread
    pthread_t pth = pthread_self();
    // get the clock_id associated to the current thread
    clockid_t clock_id;
    pthread_getcpuclockid(pth, &clock_id);
    // get the timespec associated to the thread clock
    if(::clock_gettime(clock_id, &ts))
#endif
    {
        assert(false && "clock_gettime failed")
    }

    // transform to nanoseconds
    return time_point(duration(
        static_cast<thread_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));

}


#endif



} //chrono
