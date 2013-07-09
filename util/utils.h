#ifndef UTIL_UTILS_H
#define UTIL_UTILS_H

#include "config.h"
#include <string>
#include <cstddef>
#include <cstdarg>
#include <cstdio>
#include <functional>

#include <boost/noncopyable.hpp>

#include "util/config/attribute.h"


namespace util {
//
/*
typedef unsigned long long hash_t;

hash_t hash(const char *);
hash_t hash(const std::string &);
*/

typedef long long walltime_t;
walltime_t get_walltime();
walltime_t get_walltime_s(); // in seconds


void sleep(long ms);

inline char * str_skip_to_whitespace(char *str)
{
    while(*str && (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r'))
        str++;
    return str;
}

inline char *str_skip_whitespaces(char *str)
{
    while(*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'))
        str++;
    return str;
}


std::string sprintf(const char * format, ...) __attribute__(( format(printf, 1, 2) ));
std::string vsprintf(const char * format, va_list args) __attribute__(( format(printf, 1, 0) ));
//int snprintf(std::string& out, std::size_t size, const char * format, ...) __attribute__(( format(printf, 3, 4) ));


template<typename T, std::size_t N>
inline constexpr std::size_t arrayof(const T (&)[N])
{
    return N;
}

template <typename To, typename From>
inline constexpr To ptr_cast(From f)
{
    return reinterpret_cast<To>(reinterpret_cast<std::ptrdiff_t>(f));
}


class scope_exit : boost::noncopyable
{
private:
    std::function<void()> fn;

public:
    scope_exit(std::function<void()> fn_) : fn(std::move(fn_)) {}
    ~scope_exit()
    {
        fn();
    }
};

template<typename T, typename U = T>
T exchange(T& obj, U&& new_val)
{
    T old_val = std::move(obj);
    obj = std::forward<U>(new_val);
    return old_val;
}


template <typename T>
T fread(FILE * fp)
{
    T obj;
    ::fread(&obj, sizeof(T), 1, fp);
    return obj;
}
template <typename T, std::size_t N>
void fread(FILE * fp, T (&objs)[N])
{
    T obj;
    ::fread(&objs, sizeof(T), N, fp);
    return obj;
}

template <typename T>
void fwrite(FILE * fp, const T& obj)
{
    ::fwrite(&obj, sizeof(T), 1, fp);
}
template <typename T, std::size_t N>
void fwrite(FILE * fp, const T (&objs)[N])
{
    ::fwrite(&objs, sizeof(T), N, fp);
}
} // util
#endif
