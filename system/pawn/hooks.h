#ifndef PAWN_HOOKS_H
#define PAWN_HOOKS_H


#if !defined (NO_HOOK_PAWNLOG) && !defined (TEST_MODE) //&& (sizeof(char *) == 4)
#define HOOK_PAWNLOG
#endif


#include "pawn/pawnlog.hpp"


namespace pawn {

//int logprintf_impl(const char * format, ...);


bool is_hooked_logprintf();


bool rehook_logprintf();


} // pawn

#endif

