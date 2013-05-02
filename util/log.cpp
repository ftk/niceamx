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


static logger_fun_t loggers[MAX_LOGGERS];
static int num_loggers = 0;

// log functions
void log_msg(const char * module, const char * format, ...)
{
  char buffer[MAX_LOG_LINE];
  va_list args;
  va_start(args, format);
  int len = vsnprintf(buffer, MAX_LOG_LINE-1, format, args);
  buffer[len] = '\0';
  va_end(args);
  
  return log_msg_nofmt(module, buffer);
}

void log_msg_nofmt(const char * module, const char * msg)
{
	for(int i = 0; i < num_loggers; i++)
		loggers[i](module, msg);
}

void log_debug(const char * module, const char * format, ...)
{
#if defined _DEBUG || defined DEBUG
  char buffer[MAX_LOG_LINE];
  va_list args;
  va_start(args, format);
  int len = vsnprintf(buffer, MAX_LOG_LINE-1, format, args);
  buffer[len] = '\0';
  va_end(args);

  return log_msg_nofmt(module, buffer);
#else
  ((void)module);
  ((void)format);
#endif
}
// loggers

void register_logger(logger_fun_t fn)
{
	assert(num_loggers < MAX_LOGGERS);
	loggers[num_loggers++] = fn;
}


void logger_stdout(const char * module, const char * str)
{
	fprintf(stdout, "<%s>: %s\n", module, str);
}
void logger_stderr(const char * module, const char * str)
{
	fprintf(stderr, "<%s>: %s\n", module, str);
}

// rotational logger


static void logger_file_open(const char * str)
{
	if(log_file != NULL)
	{
		fclose(log_file);
		log_file = NULL;
	}
	if(str)
		log_file = fopen(str, "a");
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
	logger_file_open(filename);
	assert(log_file != NULL);
}
static void logger_file(const char * str)
{
	if(log_file != NULL)
	{
		fputs(str, log_file);
		fputc('\n', log_file);
	}
}


void logger_rotational(const char * module, const char * msg)
{
	time_t rawtime;
	struct tm * timeinfo;
	
	time(&rawtime);

	if(rawtime >= log_rotate_time)
	{
		rotate_log();
	}
	
	timeinfo = localtime(&rawtime);
	
	char buffer[MAX_LOG_LINE];
	int len = snprintf(buffer, MAX_LOG_LINE-1, "%02d:%02d:%02d:%08lX:<%s>: ", 
		timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, 
		(unsigned long)rawtime, module);
	
	strncpy(buffer + len, msg, MAX_LOG_LINE - len - 1);
	buffer[MAX_LOG_LINE-1] = '\0';
	//log_line(buffer);
	logger_file(buffer);
}








} // util


