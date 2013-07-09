#include "config.h"
#include "SDK/plugin.h"

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdexcept>

#include "pawnlog.hpp"
#include "signals.hpp"


#include "util/utils.h"
#include "util/log.h"

#include "plugin.h"

#include "hooks.h"

//typedef std::list<AMX*> amxs_t;
//static amxs_t amxs;


namespace pawn
{
    AMX * gamemode = NULL;
}


PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

//Загрузка плагина
PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData) 
{
    ::srand((unsigned)::time(NULL));

    //pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    pawn::init_amx_funcs(reinterpret_cast<void **>(ppData[PLUGIN_DATA_AMX_EXPORTS]));
    
    pawn::logprintf = util::ptr_cast<pawn::logprintf_t>(ppData[PLUGIN_DATA_LOGPRINTF]);

    if(!pawn::is_hooked_logprintf())
        pawn::rehook_logprintf();
    
    
    util::register_logger(&util::logger_rotational);
#if defined(_DEBUG) || defined(WIN32)
    if(!pawn::is_hooked_logprintf())
        util::register_logger(&pawn::logger_serverlog); // will cause inf loop if hooked
    else
        util::register_logger(&util::logger_stdout);
#endif
    util::log_msg_nofmt("plugin/load", "Initializing...");
    
    //INITBOX->execute();
    INVOKE_INIT();

    util::log_msg_nofmt("plugin/load", "Initializing done");

    MAINBOX->plugin_load();

    return true;
}

//Выгрузка плагина
PLUGIN_EXPORT void PLUGIN_CALL Unload() 
{
    // Вызываем обработчик события
    MAINBOX->plugin_unload();

    if(pawn::is_hooked_logprintf())
        pawn::rehook_logprintf();


    pawn::logprint("  Unloaded.");
    pawn::logprintf = 0;
}

// Подгрузка виртуальной машины
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) 
{
    amx_Register(amx, pawn::toexport, -1);
    
    return AMX_ERR_NONE;
}

// Выгрузка виртуальной машины
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX * /*amx*/)
{
    return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
    static unsigned int ticks = 0;


    //if(util::get_walltime() > ticks)
    if(ticks == (TIMERS_RESOLUTION / THREAD_SLEEP_TIME))
    {
        try
        {
            MAINBOX->timers();
        }
        catch(std::exception& e)
        {
            std::cerr << "Caught exception while processing timers: ";
            std::cerr << e.what() << std::endl;
            util::log_msg_nofmt("timers/exception", e.what());
        }
        //ticks = util::get_walltime() + TIMERS_SLEEP_TIME;
        ticks = 0;
    }
    ++ticks;
    return;
}
/*
INIT
{
    REGISTER_CALLBACK(on_game_mode_init, -1000000, []()
    {
        pawn::gamemode =
    });
}*/
