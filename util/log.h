#ifndef UTIL_LOG_H
#define UTIL_LOG_H

#ifndef MAX_LOG_LINE
#define MAX_LOG_LINE 256
#endif

#include "config.h"
#include "util/config/attribute.h"

#include <string>

namespace util {

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


} //
#endif