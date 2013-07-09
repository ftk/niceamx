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
    typedef long long rep;
#ifdef WIN32
    typedef std::micro period;
#else
    typedef std::nano period;
#endif
    typedef std::chrono::duration<rep, period> duration;
    typedef std::chrono::time_point<fast_steady_clock> time_point;

    static const bool is_steady = true;


    // win32: QueryPerformaceCounter
    // posix: clock_gettime(CLOCK_MONOTONIC)
    static time_point now();

    //static time_point from_time_t(std::time_t t);
    //static std::time_t to_time_t(const time_point& t);
private:
#ifdef WIN32
    static long long freq;// = 0LL;
#endif
};

class fast_realtime_clock
{
public:
    typedef long long rep;
#ifdef WIN32
    typedef std::milli period;
#else
    typedef std::nano period;
#endif
    typedef std::chrono::duration<rep, period> duration;
    typedef std::chrono::time_point<fast_realtime_clock> time_point;

    static const bool is_steady = false;


    // win32: gettickcount
    // posix: clock_gettime(CLOCK_REALTIME)
    static time_point now();

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


} // chrono

#endif // UTIL_CHRONO_HPP
