#ifndef UTIL_THREAD_HPP
#define UTIL_THREAD_HPP

#ifndef MULTITHREADED
#error define MULTITHREADED to use threads 
#endif

//#include "config.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <pthread.h>
#endif

namespace util {
//

#ifdef WIN32
typedef HANDLE thread_t;
typedef DWORD thread_return_t;
typedef LPTHREAD_START_ROUTINE thread_func_t;
#else
typedef pthread_t thread_t;
typedef void * thread_return_t;
typedef thread_return_t (*thread_func_t)(void *);
#endif


int start_thread(thread_t * obj, thread_func_t func, void * arg = NULL);

class mutex
{
private:
  //bool locked;
#ifdef WIN32
  typedef HANDLE mutex_t;
#else
  typedef pthread_mutex_t mutex_t;
#endif
  mutex_t obj;
public:
  mutex() //: locked(false)
  {
    init();
  }
  ~mutex() {}

  int lock();
  int unlock();
protected:
  int init();
};
class mutex_scope_lock
{
private:
  mutex * m;
public:
  mutex_scope_lock(mutex * m_) : m(m_)
  {
    m->lock();
  }
  ~mutex_scope_lock()
  {
    m->unlock();
  }
};

}

#ifdef WIN32
#define THREAD_FUNC_PREFIX util::thread_return_t WINAPI
#define THREAD_FUNC_END return(1)
#define THREAD_FUNC_DECL(name) THREAD_FUNC_PREFIX name (LPVOID arg)
#else
#define THREAD_FUNC_PREFIX util::thread_return_t
#define THREAD_FUNC_END return(NULL)
#define THREAD_FUNC_DECL(name) THREAD_FUNC_PREFIX name (void * arg)
#endif


#endif
