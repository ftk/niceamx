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

#ifndef BOOST_NO_VARIADIC_TEMPLATES 
#include "signal.hpp"
#else
#include <boost/signals2.hpp>
#endif

#include "timers.hpp"


#include <boost/preprocessor/cat.hpp>

#include <string>

#ifndef BOOST_NO_VARIADIC_TEMPLATES 
#define SIGNALS_SIGNAL_TYPE signals::signal
#define SIGNALS_SIGNAL_WRAPPER(...) SIGNALS_SIGNAL_TYPE<  __VA_ARGS__ >
#define SIGNALS_SIGNAL_SIMPLE_WRAPPER(...) signals::signal_simple < __VA_ARGS__ >
#else
#define SIGNALS_SIGNAL_TYPE boost::signals2::signal
#define SIGNALS_SIGNAL_WRAPPER(...) SIGNALS_SIGNAL_TYPE< void ( __VA_ARGS__ ) >
#define SIGNALS_SIGNAL_SIMPLE_WRAPPER(...) SIGNALS_SIGNAL_WRAPPER( __VA_ARGS__ )
#endif


#ifdef __GNUC__ // supports __attribute__((constructor))
// unsafe (?)
//#define HAS_CONSTRUCTOR
//#define CONSTRUCTOR __attribute__((constructor))
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
      #ifndef HAS_CONSTRUCTOR
      SIGNALS_SIGNAL_SIMPLE_WRAPPER() init_container;
      #endif
      
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

#define GET_CALLBACK(cb) (MAINBOX->cb) // returns signal object ( for internal use )

// very simple signal library replacement
#define INVOKE_CALLBACK(cb,...) GET_CALLBACK(cb)(__VA_ARGS__) //MAINBOX->cb(__VA_ARGS__)

#ifdef HAS_CONSTRUCTOR
#define INVOKE_INIT() (static_cast<void>(0)) // do nothing
#define INITBOX 
#else
#define INVOKE_INIT() ((*INITBOX)())
#define INITBOX (&(MAINBOX->init_container))
#endif


#define SIGNALS_LOCAL_FN static // do not export


#define REGISTER_MODULE(f) \
SIGNALS_LOCAL_FN const bool BOOST_PP_CAT(_is_registered_, __LINE__) = (INITBOX->connect(f), true) \
/* */
/*
 * Usage:
 * * void func();
 * * REGISTER_MODULE(&func);
 */

#ifdef HAS_CONSTRUCTOR
#define INIT \
CONSTRUCTOR SIGNALS_LOCAL_FN void BOOST_PP_CAT(_init_func_, __LINE__)(); \
CONSTRUCTOR SIGNALS_LOCAL_FN void BOOST_PP_CAT(_init_func_, __LINE__)() \
/* */
#else
#define INIT \
SIGNALS_LOCAL_FN void BOOST_PP_CAT(_init_func_, __LINE__)(); \
REGISTER_MODULE(BOOST_PP_CAT(&_init_func_, __LINE__)); \
SIGNALS_LOCAL_FN void BOOST_PP_CAT(_init_func_, __LINE__)() \
/* */
#endif
/*
 * Usage: INIT { code(); }
 */

#define REGISTER_CALLBACK(cb,fn) \
MAINBOX->cb.connect(fn) \
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

