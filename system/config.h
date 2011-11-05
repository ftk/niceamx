#ifndef CONFIG_H
#define CONFIG_H

#ifndef __cplusplus
#error c++ required
#endif


#if !defined(LINUX) && (defined(__linux) || defined(__linux__) || defined(linux))
#define LINUX
#elif !defined(WIN32) && (defined(_WIN32) || defined(__WIN32__))
#define WIN32
#endif

#if (defined __GXX_EXPERIMENTAL_CXX0X__ || defined CXX0X_ENABLED) && !defined CXX0X_DISABLED
#define CPP_0X // vs2010 doesnt support variadic templates
#endif


#ifndef NULL

#ifdef CPP_0X
#define NULL nullptr
#else
#define NULL 0
#endif

#endif // null



#endif // config.h

