
#include "hooks.h"
#include <cstdarg>

#include <algorithm>

#include "util/utils.h"
#include "util/log.h"

#include "pawn/pawnlog.hpp"

#ifdef HOOK_PAWNLOG
#include "util/hook86.h"

static char logprintf_header[5];

#endif

namespace pawn {


static void logprintf_impl(const char * format, ...)
{
    va_list ap;
    char dst[MAX_LOG_LINE];
    va_start(ap, format);
    int n = vsnprintf(dst, util::arrayof(dst), format, ap);
    va_end(ap);

    if(n < 0 || static_cast<unsigned>(n) >= util::arrayof(dst))
    {
        util::log_msg("serverlog/error", "wrong format string \'%s\'", format);
        return;
    }

    //util::log_msg_nofmt("serverlog/format", format);
    util::log_msg_nofmt("serverlog/msg", dst);
}

static pawn::logprintf_t new_logprintf = &logprintf_impl;

static unsigned hooks_num = 0;


bool is_hooked_logprintf()
{
    return hooks_num & 1; // % 2
}


bool rehook_logprintf()
{
#ifdef HOOK_PAWNLOG
    if(logprintf == NULL)
        return false;

    if(!hooks_num)
    {
        pawn::logprintf("%s", "hooking logprintf...");
        bool ok = util::set_hook_x86(util::ptr_cast<void*>(logprintf),
                                     util::ptr_cast<void*>(new_logprintf),
                                     logprintf_header);
        if(!ok)
        {
            pawn::logprintf("hooking logprintf... failed");
            return false;
        }
        ++hooks_num;
        return true;
    }
    // swap logprintf header
    std::swap_ranges(logprintf_header, logprintf_header + 5,
                     util::ptr_cast<char*>(logprintf));
    ++hooks_num;
    return true;

#else
    return false;
#endif
}

} // pawn
