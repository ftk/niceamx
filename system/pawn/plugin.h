#ifndef PAWN_PLUGIN_H
#define PAWN_PLUGIN_H

#include "SDK/amx/amx.h"

namespace pawn
{
	extern AMX_NATIVE_INFO toexport[]; // array with plugin natives
	extern AMX * gamemode;
	void natives_init(AMX *);
}

#endif

