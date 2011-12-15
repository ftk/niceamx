#ifndef UTIL_CONFIG_ATTRIBUTE_H
#define UTIL_CONFIG_ATTRIBUTE_H

#ifndef __GNUC__
#define  __attribute__(x)  /* nothing */
#endif

#define attribute(...) __attribute__((__VA_ARGS__))

#define PURE __attribute__((const)) // pure function
#define NORETURN __attribute__((noreturn))

#endif
