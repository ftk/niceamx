#ifndef UTIL_LOG_H
#define UTIL_LOG_H

#ifndef MAX_LOG_LINE
#define MAX_LOG_LINE 512
#endif

#include "config.h"
#include "util/config/attribute.h"

//#include <string>

namespace util {



void log_msg(const char * module, const char * format, ...) __attribute__((format(printf, 2, 3)));

void log_msg_nofmt(const char * module, const char * msg);

void log_debug(const char * module, const char * format, ...) __attribute__((format(printf, 2, 3)));

// ---


typedef void (*logger_fun_t)(const char *, const char *); // module, msg

void register_logger(logger_fun_t fn);

void logger_rotational(const char * module, const char * str);
void logger_stdout(const char * module, const char * str);
void logger_stderr(const char * module, const char * str);

} //
#endif
