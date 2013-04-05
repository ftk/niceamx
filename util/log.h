#ifndef UTIL_LOG_H
#define UTIL_LOG_H

#ifndef MAX_LOG_LINE
#define MAX_LOG_LINE 512
#endif

#include "config.h"
#include "util/config/attribute.h"

//#include <string>

namespace util {

/*
enum log_level
{
  LOG_NONE = 0,
  LOG_INFO,
  LOG_WARNING,
  LOG_ERROR,
  LOG_NOTICE,
  LOG_DEBUG
};

void log(enum log_level crit, const char * format, ...) __attribute__((format(printf, 2, 3)));
void log_nofmt(enum log_level crit, const char * str);
*/



void log_msg(const char * module, const char * format, ...) __attribute__((format(printf, 2, 3)));

void log_msg_nofmt(const char * module, const char * msg);

// ---
/*

typedef void (*log_fnptr_t)(const char *);

void logger_register(log_fnptr_t fn);

void log_filename(const char * str);

void logger_file(const char * str);

void log_line(const char * str);

extern bool log_rotate;
*/
} //
#endif
