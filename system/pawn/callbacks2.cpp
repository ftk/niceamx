#include "demarh_var.hpp"
#include "signals.hpp"
#include "plugin.h"


#include <iostream>

#include <boost/preprocessor/stringize.hpp>
#include "util/config/attribute.h"

#include "util/log.h"

#define NATIVE_DECL(fn) __attribute__((flatten)) static cell  AMX_NATIVE_CALL fn (AMX * amx, cell * params)
#define CALL_SIGNAL(sig) pawn::arg_pack_helper(MAINBOX->sig, amx, params)

namespace pawn {

NATIVE_DECL(GameModeInit)
{
    pawn::gamemode = amx;
    pawn::natives_init(amx);
    return CALL_SIGNAL(on_game_mode_init);
}

NATIVE_DECL(GameModeExit)
{
    cell R = CALL_SIGNAL(on_game_mode_exit);
    pawn::gamemode = NULL;
    return R;
}


#define EVENT(sampname,sig) \
    NATIVE_DECL(sampname) \
    { \
    try { \
    return CALL_SIGNAL(sig); \
    } \
    catch(std::exception& e) { \
    std::cerr << "Exception while processing event On" << \
    BOOST_PP_STRINGIZE(sampname) << ": " << e.what(); \
    util::log_msg_nofmt("callback/exception", e.what()); \
    } \
    return 0; \
    } \
    /* */

#include "events_tr.inl"

#undef EVENT

#define EVENT(sampname,sig) \
    { "_" BOOST_PP_STRINGIZE(sampname), & sampname }, \
    /* */


AMX_NATIVE_INFO toexport[] =
{
    EVENT(GameModeInit, on_game_mode_init)
    EVENT(GameModeExit, on_game_mode_exit)
    #include "events_tr.inl"
    {NULL, NULL}
};

#undef EVENT

} // pawn


