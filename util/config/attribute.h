#ifndef UTIL_CONFIG_ATTRIBUTE_H
#define UTIL_CONFIG_ATTRIBUTE_H

#ifndef __GNUC__
#define  __attribute__(x)  /* nothing */
#endif

#define _attribute(...) __attribute__(__VA_ARGS__)

#define PURE _attribute((const)) // pure function
#define NORETURN _attribute((noreturn))
#define INLINE _attribute((always_inline)) inline

#endif
