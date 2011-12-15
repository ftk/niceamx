/* 
 * File:   notify.h
 * Author: Fotyev
 *
 * Created on 26 Сентябрь 2010 г., 0:32
 */

#ifndef UTIL_NOTIFY_H
#define	UTIL_NOTIFY_H

#include <string>

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define CURRENT_FUNCTION __func__
#else
#include <boost/current_function.hpp> // __PRETTY_FUNCTION__ instead of __FUNCTION__
#define CURRENT_FUNCTION BOOST_CURRENT_FUNCTION
#endif

#include <boost/preprocessor/stringize.hpp>

#include "util/config/attribute.h"

namespace util
{

    void notify(const std::string& s);
    void notify(const char * file, const char * func, const std::string& s);
    void notify(const char * format, ...) __attribute__(( format(printf, 1, 2) ));
    
    void warning(const std::string& s);
    void warning(const char * file, const char * func, const std::string& s);
    void warning(const char * format, ...) __attribute__(( format(printf, 1, 2) ));
    
    void error(const std::string& s);
    void error(const char * file, const char * func, const std::string& s);
    void error(const char * format, ...) __attribute__(( format(printf, 1, 2) ));
    
    NORETURN void abort(const std::string& s, int errorlevel = 1);
}

#define CALL_LOG_EVENT(ev, s) ::util:: ev (__FILE__ ":" BOOST_PP_STRINGIZE(__LINE__), CURRENT_FUNCTION, s)

#define NOTIFY(s) CALL_LOG_EVENT(notify, s)
#define WARNING(s) CALL_LOG_EVENT(warning, s)
#define ERROR(s) CALL_LOG_EVENT(error, s)


#endif	/* NOTIFY_H */

