#ifdef MULTITHREADED
#include "thread.hpp"


#include <cassert>

namespace util {
//

int start_thread(thread_t * obj, thread_func_t func, void * arg)
{
#ifdef WIN32
  DWORD ret;
  *obj = CreateThread(NULL, 0, func, arg, 0, &ret);
  return (int)ret;
#else
  return pthread_create(obj, NULL, func, arg);
#endif
}

int mutex::init()
{
#ifdef WIN32
  obj = CreateMutex(NULL, FALSE, NULL);
  return (obj == NULL);
#else
  return pthread_mutex_init(&obj, NULL);
#endif
}

int mutex::lock()
{
  //if(!locked)
  {
    //locked = true;
#ifdef WIN32
    return(WaitForSingleObject(obj, INFINITE) == WAIT_FAILED);
#else
    return pthread_mutex_lock(&obj);
#endif
  }
  return -1;
}

int mutex::unlock()
{
  //if(locked)
  {
    //locked = false;
#ifdef WIN32
    return(ReleaseMutex(obj) == 0);
#else
    return pthread_mutex_unlock(&obj);
#endif
  }
  return -1;
}

}
#endif
