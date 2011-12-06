/* 
 * File:   notify.h
 * Author: Fotyev
 *
 * Created on 26 Сентябрь 2010 г., 0:32
 */

#ifndef UTIL_NOTIFY_H
#define	UTIL_NOTIFY_H

#include <string>
#include <boost/current_function.hpp>

// TODO: add function detect (boost/current_function.hpp)

namespace util
{

    void notify(const std::string& s);
    void notify(const char * file, int line, const char * func, const std::string& s);
    void warning(const std::string& s);
    void warning(const char * file, int line, const char * func, const std::string& s);
    void error(const std::string& s);
    void error(const char * file, int line, const char * func, const std::string& s);
    void abort(const std::string& s, int level = 1);
}

#define CALL_LOG_EVENT(ev, s) ::util:: ev (__FILE__, __LINE__, BOOST_CURRENT_FUNCTION, s)

#define NOTIFY(s) CALL_LOG_EVENT(notify, s)
#define WARNING(s) CALL_LOG_EVENT(warning, s)
#define ERROR(s) CALL_LOG_EVENT(error, s)


#endif	/* NOTIFY_H */

