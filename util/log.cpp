#include "log.h"

#include <cstdarg>
#include <ctime>
#include <cassert>
#include <cstring>
#include <cstdio>

//#include <string>


#ifndef LOG_FILENAME
#define LOG_FILENAME "logs/%Y_%m_%d.txt"
#endif

#define MAX_LOGGERS 16


namespace util {
//

static time_t log_rotate_time = 0;
static FILE * log_file = NULL;

/*
static log_fnptr_t loggers[MAX_LOGGERS];
static int num_loggers = 0;

bool rotate_log = true;

void log_line(const char * str)
{
	for(int i = 0; i < num_loggers; i++)
		loggers[i](str);
}

void logger_register(log_fnptr_t fn)
{
	if(num_loggers < MAX_LOGGERS)
		loggers[num_loggers++] = fn;
}*/

static void log_filename(const char * str)
{
	if(log_file != NULL)
	{
		fclose(log_file);
		log_file = NULL;
	}
	if(str)
		log_file = fopen(str, "a");
}

static void logger_file(const char * str)
{
	if(log_file != NULL)
	{
		fputs(str, log_file);
		fputc('\n', log_file);
		//fprintf(log_file, "%s\n", str);
		
		#ifndef NDEBUG
		fflush(log_file);
		
		fputs(str, stdout);
		fputc('\n', stdout);
		
		#endif
	}
}

static void rotate_log()
{
	time_t rawtime;
	struct tm * timeinfo;
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	// rotate log next day at 00:00:00
	timeinfo->tm_hour = timeinfo->tm_min = timeinfo->tm_sec = 0;
	
	log_rotate_time = mktime(timeinfo);
	log_rotate_time += 60 * 60 * 24; // +24h
	
	// change filename
	
	char filename[256];
	strftime(filename, sizeof(filename), LOG_FILENAME, timeinfo);
	log_filename(filename);
	assert(log_file != NULL);
}


void log_msg(const char * module, const char * format, ...)
{
  char buffer[MAX_LOG_LINE];
  va_list args;
  va_start(args, format);
  int len = vsnprintf(buffer, MAX_LOG_LINE, format, args);
  buffer[len] = '\0';
  va_end(args);
  
  return log_msg_nofmt(module, buffer);
}

void log_msg_nofmt(const char * module, const char * msg)
{
	time_t rawtime;
	struct tm * timeinfo;
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if(rawtime >= log_rotate_time)
	{
		rotate_log();
	}
	char buffer[MAX_LOG_LINE];
	int len = snprintf(buffer, MAX_LOG_LINE, "%02d:%02d:%02d:%08lX:<%s>: ", 
		timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, 
		(unsigned long)rawtime, module);
	
	strncpy(buffer + len, msg, MAX_LOG_LINE - len - 1);
	
	//log_line(buffer);
	logger_file(buffer);
}


/*
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
    //urgency = "";
  }
  // TODO
}*/



}