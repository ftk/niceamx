/* 
 * File:   overtimer.hpp
 * Author: Fotyev
 *
 * Created on 26 Сентябрь 2010 г., 0:14
 */

#ifndef UTIL_OVERTIMER_HPP
#define	UTIL_OVERTIMER_HPP

#if (!defined NDEBUG || defined OVERTIMER_ENABLE) && !defined OVERTIMER_DISABLE
#define _OVERTIMER_ENABLED
#endif

#ifdef _OVERTIMER_ENABLED

#include <boost/current_function.hpp>
#include <boost/format.hpp>
#include <boost/preprocessor/cat.hpp>


#include <string>

#include "util/notify.h"
#include "util/utils.h"

#endif

namespace util
{
#ifdef _OVERTIMER_ENABLED

    class overtimer
    {
    public: // walltime - time started from unknown point, used to compare;
            // in this case: 1 = 1ms
        typedef util::walltime_t walltime_t;
    private:
        const std::string func; // holds current function or/and file name
        walltime_t wall_limit; //
        const walltime_t max_over;
        
    public:
        static inline walltime_t get_walltime()
	{
	    return util::get_walltime();
	}
    public:

        inline void yield(walltime_t maxover = 5)
        {
            wall_limit = get_walltime() + maxover;
        }

        inline bool late() const // 
        {
            return(get_walltime() > wall_limit);
        }

        explicit overtimer(const char * func_, walltime_t maxover = 5) : func(func_), max_over(maxover)
        {
            this->yield(maxover);
        }

        // main action
        ~overtimer()
        {
            if(this->late())
            {
                // action

                notify((boost::format
                        ("Function \'%1%\' took long execution time: %2% ms")
                        % func
                        % (get_walltime() - wall_limit + max_over)).str());
            }
        }


    };

#endif // _OVERTIMER_ENABLED

}

#ifdef _OVERTIMER_ENABLED

#define MAKE_OVERTIMER(ms) \
util::overtimer BOOST_PP_CAT(_timer_, __LINE__) \
(BOOST_CURRENT_FUNCTION, ms) \
/* calling constructor */

#else // _OVERTIMER_ENABLED

#define MAKE_OVERTIMER(ms) (static_cast<void> (0))/* empty */

#endif // _OVERTIMER_ENABLED



#endif	/* OVERTIMER_HPP */

