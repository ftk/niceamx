#include "log.h"

#include <cstdarg>
#include <string>

namespace util {
//

void log(enum log_level crit, const char * format, ...)
{
  char buffer[MAX_LOG_LINE];
  va_list args;
  va_start(args, format);
  int len = vsnprintf(buffer, MAX_LOG_LINE - 1, format, args);
  buffer[len] = '\0';
  va_end(args);
  
  return log_nofmt(crit, buffer);
}

void log_nofmt(enum log_level crit, const char * str)
{
  std::string urgency;  
  switch (crit) 
  {
  case LOG_INFO:
    urgency = "[INFO] ";
    break;
  case LOG_WARNING:
    urgency = "[WARNING] ";
    break;
  case LOG_ERROR:
    urgency = "[ERROR] ";
    break;
  case LOG_NOTICE:
    urgency = "[NOTICE] ";
    break;
  case LOG_DEBUG:
    urgency = "[DEBUG] ";
    break;
  default:
    urgency = "";
  }
  // TODO
}



}