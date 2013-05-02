#ifndef UTIL_UTILS_HPP
#define UTIL_UTILS_HPP

#include "config.h"
#include <string>

//#include <boost/config.hpp>

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


std::string sprintf(const char * format, ...) __attribute__(( format(printf, 1, 2) ));

}
#endif
