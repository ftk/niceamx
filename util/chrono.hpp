#ifndef UTIL_CHRONO_HPP
#define UTIL_CHRONO_HPP
#include "config.h"

//TODO

#include <chrono>
#include <ratio>
#include <ctime>


namespace chrono {

using namespace std::chrono;



class fast_steady_clock
{
public:
#ifdef WIN32
    typedef microseconds duration;
#else
    typedef nanoseconds duration;
#endif
    typedef duration::rep rep;
    typedef duration::period period;
    typedef std::chrono::time_point<fast_steady_clock> time_point;

    static constexpr bool is_steady = true;


    // win32: QueryPerformaceCounter
    // posix: clock_gettime(CLOCK_MONOTONIC)
    static time_point now() noexcept;

private:
#ifdef WIN32
    static long long freq;// = 0LL;
#endif
};

class fast_realtime_clock
{
public:
#ifdef WIN32
    typedef milliseconds duration;
#else
    typedef nanoseconds duration;
#endif
    typedef duration::rep rep;
    typedef duration::period period;
    typedef std::chrono::time_point<fast_realtime_clock> time_point;

    static constexpr bool is_steady = false;


    // win32: gettickcount
    // posix: clock_gettime(CLOCK_REALTIME)
    static time_point now() noexcept;

    //static time_point from_time_t(std::time_t t);
    //static std::time_t to_time_t(const time_point& t);
};

#ifdef WIN32
using fast_clock = fast_realtime_clock;
//typedef fast_realtime_clock fast_clock;
#else
using fast_clock = fast_steady_clock; // prefer monotonic
//typedef fast_monotonic_clock fast_clock;
#endif


class process_real_cpu_clock
{
public:
    typedef nanoseconds                          duration;
    typedef duration::rep                        rep;
    typedef duration::period                     period;
    typedef chrono::time_point<process_real_cpu_clock>    time_point;
    static constexpr bool is_steady =             true;

    static time_point now() noexcept;
};

class process_user_cpu_clock
{
public:
    typedef nanoseconds                          duration;
    typedef duration::rep                        rep;
    typedef duration::period                     period;
    typedef chrono::time_point<process_user_cpu_clock>    time_point;
    static constexpr bool is_steady =             true;

    static time_point now() noexcept;
};

class process_system_cpu_clock
{
public:
    typedef nanoseconds                          duration;
    typedef duration::rep                        rep;
    typedef duration::period                     period;
    typedef chrono::time_point<process_system_cpu_clock>    time_point;
    static constexpr bool is_steady =             true;

    static time_point now() noexcept;
};


class thread_clock
{
public:
    typedef nanoseconds                          duration;
    typedef duration::rep                        rep;
    typedef duration::period                     period;
    typedef chrono::time_point<thread_clock>    time_point;
    static constexpr bool is_steady = true;

    static time_point now( ) noexcept;
};

} // chrono

#endif // UTIL_CHRONO_HPP
