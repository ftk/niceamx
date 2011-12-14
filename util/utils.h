#ifndef UTIL_UTILS_HPP
#define UTIL_UTILS_HPP

#include "config.h"
#include <string>


namespace util {
//

typedef unsigned long hash_t;

hash_t hash(const char *);
hash_t hash(const std::string &);

// http://stackoverflow.com/questions/2111667/compile-time-string-hashing
inline BOOST_CONSTEXPR hash_t const_hash(const char *s, int off = 0) 
{
    return !s[off] ? 5381 : (const_hash(s, off+1)*33) ^ s[off];
}



typedef unsigned long walltime_t;
walltime_t get_walltime();
walltime_t get_walltime_s(); // in seconds


void sleep(long ms);



}
#endif
