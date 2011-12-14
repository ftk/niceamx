#ifndef UTIL_CONFIG_SLIST_H
#define UTIL_CONFIG_SLIST_H

#ifndef SLIST

#include <boost/config.hpp>

#ifdef BOOST_HAS_SLIST
#include BOOST_SLIST_HEADER
#define SLIST BOOST_STD_EXTENSION_NAMESPACE ::slist
#else
#include <list>
#define SLIST std::list
#endif
#endif


#endif