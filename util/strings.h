#ifndef UTIL_STRINGS_H
#define UTIL_STRINGS_H
/*
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>
#include <iterator>
*/
namespace util {
//
/*
template <typename T>
inline T convert_from_string(const std::string& src)
{
  return boost::lexical_cast<T>(src);
}

template <typename T>
inline void convert_from_string(T& obj, const std::string& src)
{
  obj = convert_from_string<T>(src);
}


template <typename T>
inline std::string convert_to_string(T src)
{
  return boost::lexical_cast<std::string>(src);
}


template <typename T>
inline T get_param(const std::string& src, int pos = 0)
{
  boost::tokenizer<> tok(src);
  auto it = tok.begin();
  std::advance(it, pos);
  return boost::lexical_cast<T>(*it);
}
*/

}


#endif
