#ifndef UTIL_UTILS_HPP
#define UTIL_UTILS_HPP

#include <string>


namespace util {
//

typedef unsigned long hash_t;

hash_t hash(const char *);
hash_t hash(const std::string &);


typedef unsigned long walltime_t;
walltime_t get_walltime();
walltime_t get_walltime_s(); // in seconds


void sleep(long ms);


}
#endif
