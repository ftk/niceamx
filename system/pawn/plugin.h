#ifndef PAWN_PLUGIN_H
#define PAWN_PLUGIN_H

#include "SDK/amx/amx.h"


#ifndef THREAD_SLEEP_TIME
#define THREAD_SLEEP_TIME 5 // main samp thread ( parameter sleep in server.cfg )
#endif

#ifndef TIMERS_RESOLUTION
#define TIMERS_RESOLUTION 50 // minimum timers resolution ( by default every 10 ticks )
#endif



namespace pawn
{
	enum 
	{
		MAX_PLUGIN_AMX_EXPORT = 44
	};
	
	extern AMX_NATIVE_INFO toexport[]; // array with plugin natives
	extern AMX * gamemode;
	void natives_init(AMX *);
	void init_amx_funcs(void * functable[MAX_PLUGIN_AMX_EXPORT]);
}

#endif

