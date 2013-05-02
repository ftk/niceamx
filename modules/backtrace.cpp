#ifndef WIN32
// glibc only (?)

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_TRACE 50

#include "signals.hpp"

#include "util/log.h"

#include <exception>


static void print_stack() 
{
    void *array[MAX_TRACE];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace (array, MAX_TRACE);
    strings = backtrace_symbols (array, size);

    fprintf(stderr, "Obtained %d stack frames.\n", size);

    for (i = 0; i < size; i++)
    {
        fprintf(stderr, "%d: %s\n", i, strings[i]);
        util::log_msg("backtrace", "%02d: %s", i, strings[i]);
    }

    free(strings);
}

static void signal_handler(int sig) 
{
	fprintf(stderr, "Caught signal %d.\n", sig);
	print_stack();
	exit(sig);
}

static void terminate_handler() 
{
	fprintf(stderr, "Caught unhandled exception\n", sig);
	print_stack();
	std::abort();
}



INIT
{
    signal(SIGSEGV, &signal_handler);
    //signal(SIGABRT, &handler);
    std::set_terminate(&terminate_handler);
}

#endif

