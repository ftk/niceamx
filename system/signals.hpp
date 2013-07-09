/* 
 * File:   signals.hpp
 * Author: Fotyev
 *
 * Created on 25 Сентябрь 2010 г., 21:51
 */

#ifndef SIGNALS_HPP
#define	SIGNALS_HPP

#include "config.h"
//#include "basic_signal.hpp"
#include "util/singleton.hpp"

#include "signal.hpp"

#include "timers.hpp"


#include <boost/preprocessor/cat.hpp>
//#include <boost/preprocessor.hpp>

#include <string>





namespace signals
{


    // mainbox -------------------------------------------------------
    class box_t : public util::singleton<box_t>
    {
    private:
        box_t();
        ~box_t();
        friend class util::singleton<box_t>;

    public:
    #define SIGNAL(name,...) signals::signal<__VA_ARGS__> name;

    #include "events.inl"

    #undef SIGNAL

    public:
        signals::signal_funptr<> init_container;

    public:
      
        timers_container_t timers;
      

    public:
        void clear();
        bool empty() const;
    };

}


#define MAINBOX (signals::box_t::get_instance())


#define INVOKE_CALLBACK(cb,...) (MAINBOX->cb(__VA_ARGS__)) //MAINBOX->cb(__VA_ARGS__)


#define INVOKE_INIT() ((MAINBOX->init_container)())
#define INITBOX (&(MAINBOX->init_container))



// register init callback
#define REGISTER_MODULE(f) \
    static const bool BOOST_PP_CAT(_is_registered_, __LINE__) = \
    (REGISTER_CALLBACK(init_container, f), true) \
/* */
/*
 * Usage:
 * * void func();
 * * REGISTER_MODULE(&func);
 */


// create and register callback to init_container
#define INIT \
static void BOOST_PP_CAT(_init_func_, __LINE__)(); \
REGISTER_MODULE(BOOST_PP_CAT(&_init_func_, __LINE__)); \
static void BOOST_PP_CAT(_init_func_, __LINE__)() \
/* */
/*
 * Usage: INIT { code(); }
 */

#define REGISTER_CALLBACK(cb,...) \
MAINBOX->cb.connect(__VA_ARGS__) \
/* */

#define REGISTER_CB(cb) REGISTER_CALLBACK(cb, &cb) // register callback with the same name



/*
//#define _MAKE_CB(fnname,args,cb) \
BOX_LOCAL_FN bool fnname args; \
INIT \
{ \
REGISTER_CALLBACK(cb, fnname); \
} \
BOX_LOCAL_FN bool fnname args
*/

//#define OnGameModeInit() _MAKE_CB(OnGameModeInit, (), on_game_mode_init)
//#define OnPlayerConnect(...) _MAKE_CB(OnPlayerConnect, (__VA_ARGS__), on_player_connect)

#endif	/* BOX_HPP */

