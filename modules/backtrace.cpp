#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_TRACE 15

#include "signals.hpp"

static void handler(int sig) 
{
  void *array[MAX_TRACE];
  size_t size;
  char **strings;
  size_t i;

  size = backtrace (array, MAX_TRACE);
  strings = backtrace_symbols (array, size);

  printf ("Obtained %d stack frames.\n", size);

  for (i = 0; i < size; i++)
    fprintf(stderr, "%d: %s\n", i, strings[i]);

  free(strings);
  exit(sig);
}

/*
void tt()
{
  int * ptr = (int *) 0;
  printf("%d", *ptr);
  
}
*/
INIT
{
  signal(SIGSEGV, &handler);
  //tt();
}
