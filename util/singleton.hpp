#ifndef UTIL_SINGLETON_HPP
#define UTIL_SINGLETON_HPP

#include <boost/noncopyable.hpp>

/*#ifdef MULTITHREADED
#define _QUALIFIER volatile
#else
#define _QUALIFIER
#endif*/

namespace util {
//
/*
template <typename T>
class singleton : private boost::noncopyable
{
private:
  static _QUALIFIER T * instance;
protected:
  singleton() {}
  virtual ~singleton() {}
public:
  inline static T * get_instance()
  {
    if(instance == NULL)
    {
      instance = new T;
    }
    return const_cast<T *>(instance);
  }
  inline static void rm_instance()
  {
    if(instance != NULL)
    {
      delete const_cast<T *>(instance);
      instance = NULL;
    }
  }
};


template  <typename T>
_QUALIFIER T * singleton<T>::instance = NULL;
*/

template <typename T>
class singleton : private boost::noncopyable
{
public:
	inline static T * get_instance()
	{
		static T inst;
		return &inst;
	}
	inline static void rm_instance()
	{
	}
protected:
    singleton() {}

};

}

//#undef _QUALIFIER


#endif
