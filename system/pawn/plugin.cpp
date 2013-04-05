#include "config.h"
#include "SDK/plugin.h"

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "pawnlog.hpp"
#include "signals.hpp"

#include "destruct.h"

#include "util/utils.h"
#include "util/log.h"

#include "plugin.h"

//typedef std::list<AMX*> amxs_t;
//static amxs_t amxs;
#ifndef THREAD_SLEEP_TIME
#define THREAD_SLEEP_TIME 5 // main samp thread 
#endif

#ifndef TIMERS_SLEEP_TIME
#define TIMERS_SLEEP_TIME 100
#endif


extern void *pAMXFunctions;

namespace pawn
{
	AMX * gamemode;
}


PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() 
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

//Загрузка плагина
PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData) 
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];

    pawn::logprintf = reinterpret_cast<pawn::logprintf_t>(reinterpret_cast<std::ptrdiff_t>(ppData[PLUGIN_DATA_LOGPRINTF]));
    
    srand((unsigned)time(NULL));
    
    //INITBOX->execute();
    INVOKE_INIT();

    MAINBOX->plugin_load();

    return true;
}

//Выгрузка плагина
PLUGIN_EXPORT void PLUGIN_CALL Unload() 
{
    // Вызываем обработчик события
    MAINBOX->plugin_unload();

    //pawn::logprint("plugin unload");
    INVOKE_DESTRUCTOR();
    pawn::logprintf = 0;
}

// Подгрузка виртуальной машины
PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) 
{
    amx_Register(amx, pawn::toexport, -1);
    
    return AMX_ERR_NONE;
}

// Выгрузка виртуальной машины
PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) 
{
    return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
  static unsigned int ticks = 0;


  //if(util::get_walltime() > ticks)
  if(ticks == (TIMERS_SLEEP_TIME / THREAD_SLEEP_TIME))
  {
  	try
  	{
      MAINBOX->timers(TIMERS_SLEEP_TIME);
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
