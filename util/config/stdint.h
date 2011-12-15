#ifndef UTIL_CONFIG_STDINT_H
#define UTIL_CONFIG_STDINT_H

#include <boost/cstdint.hpp>

#define _WRAP(type) using boost:: type ; using boost:: u ## type ;

_WRAP(intmax_t)
_WRAP(int8_t)
_WRAP(int16_t)
_WRAP(int32_t)

#ifdef BOOST_HAS_LONG_LONG
_WRAP(int64_t)
#endif


#undef _WRAP


#endif
