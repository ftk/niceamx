#ifndef CONFIG_H
#define CONFIG_H

#ifndef __cplusplus
#error c++ compiler required
#endif


#if !defined(LINUX) && (defined(__linux) || defined(__linux__) || defined(linux))
#define LINUX
#elif !defined(WIN32) && (defined(_WIN32) || defined(__WIN32__))
#define WIN32
#endif

#include <boost/config.hpp>

/*
#if (defined __GXX_EXPERIMENTAL_CXX0X__ || defined CXX0X_ENABLED) && !defined CXX0X_DISABLED
#define CPP_0X // vs2010 doesnt support variadic templates
#endif
*/

#ifndef NULL

#ifndef BOOST_NO_NULLPTR
#define NULL ( (nullptr_t) nullptr )
#else
#define NULL ( (void*) 0 )
#endif

#endif // null



#endif // config.h

