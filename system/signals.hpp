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

#ifdef CPP_0X
#include "signal.hpp"
#else
#include <boost/signals2.hpp>
#endif

#include "timers.hpp"


#include <boost/preprocessor/cat.hpp>
#include <list>

#include <string>

#ifdef CPP_0X
#define SIGNALS_SIGNAL_TYPE signals::signal
#define SIGNALS_SIGNAL_WRAPPER(...) SIGNALS_SIGNAL_TYPE<  __VA_ARGS__ >
#define SIGNALS_SIGNAL_SIMPLE_WRAPPER(...) signals::signal_simple < __VA_ARGS__ >
#else
#define SIGNALS_SIGNAL_TYPE boost::signals2::signal
#define SIGNALS_SIGNAL_WRAPPER(...) SIGNALS_SIGNAL_TYPE< void ( __VA_ARGS__ ) >
#define SIGNALS_SIGNAL_SIMPLE_WRAPPER(...) SIGNALS_SIGNAL_WRAPPER( __VA_ARGS__ )
#endif

namespace signals
{

    /*
    // initbox --------------------------------------------------------
    class init_container_t : public SIGNALS_SIGNAL_WRAPPER()//basic_container_t<void (*)()>
    {

    public:

	init_container_t() {}

    };*/


    // mainbox -------------------------------------------------------
    class box_t : public util::singleton<box_t>
    {
      
    private:
	// singleton
        //static box_t * instance;

    protected:
        //box_t() {}

    public:
        //static box_t * get_instance();
	//static void rm_instance();

    public:
	#define SIG(...) SIGNALS_SIGNAL_WRAPPER( __VA_ARGS__ )

	#include "events.inl"
        
    #undef SIG

    public:
      
      SIGNALS_SIGNAL_SIMPLE_WRAPPER() init_container;
      
    public:
      /*
      timer_container_t timer100;
      timer_container_t timer500;
      timer_container_t timer1000;
      */
      
      timers_container_t timers;
      
    };

}


#define MAINBOX (signals::box_t::get_instance())
#define INITBOX (&(MAINBOX->init_container))

#define GET_CALLBACK(cb) (MAINBOX->cb) // returns signal object ( for internal use )

// very simple signal library replacement
#define INVOKE_CALLBACK(cb,...) GET_CALLBACK(cb)(__VA_ARGS__) //MAINBOX->cb(__VA_ARGS__)
#define INVOKE_INIT() ((*INITBOX)())



#define SIGNALS_LOCAL_FN static // do not export

#define REGISTER_MODULE(f) \
SIGNALS_LOCAL_FN bool BOOST_PP_CAT(_is_registered_, __LINE__) = (INITBOX->connect(f), true) \
/* */
/*
 * Usage:
 * * void func();
 * * REGISTER_MODULE(&func);
 */

#define INIT \
SIGNALS_LOCAL_FN void BOOST_PP_CAT(_init_func_, __LINE__)(); \
REGISTER_MODULE(BOOST_PP_CAT(&_init_func_, __LINE__)); \
SIGNALS_LOCAL_FN void BOOST_PP_CAT(_init_func_, __LINE__)() \
/* */
/*
 * Usage: INIT { code(); }
 */

#define REGISTER_CALLBACK(cb,fn) \
MAINBOX->cb.connect(fn) \
/* */

#define REGISTER_CB(cb) REGISTER_CALLBACK(cb, &cb) // register callback with the same name


/*
//#define REGISTER_TIMER(ms,fn) \
MAINBOX->BOOST_PP_CAT(timer, ms).connect(fn)
*/

#define MAKE_TIMER(ms,fn) signals::timers_container_t::timer(ms, fn) // calling constructor to make timer ( for internal use )

#define REGISTER_TIMER2(obj) REGISTER_CALLBACK(timers, obj)
#define REGISTER_TIMER(ms,fn) REGISTER_TIMER2(MAKE_TIMER(ms, fn))

#define REMOVE_TIMER2(obj) MAINBOX->timers.remove(obj)
#define REMOVE_TIMER(ms,fn) REMOVE_TIMER2(MAKE_TIMER(ms, fn))

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
