#ifndef UTIL_STRINGS_H
#define UTIL_STRINGS_H

#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>


namespace util {
//

typedef std::vector<std::string> strings;

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

template <typename T, int num>
inline T convert_from_strings(const strings& src)
{
  return convert_from_string<T>(src.at(num));
}


template <typename T>
inline std::string convert_to_string(T src)
{
  return boost::lexical_cast<std::string>(src);
}



}


#endif
