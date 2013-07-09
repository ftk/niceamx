#include "samp.h"
#include "api/cmd2.hpp"
#include "api/pipes.hpp"

#include <string>

#include <boost/lexical_cast.hpp>

#include "util/utils.h"

INIT
{
    REGISTER_COMMAND("radio", api::cmdflag::PLAYER,
                      ([](api::cmdinfo_t info)
    {
        api::parser_cmd p("?r", info);
        if(p.empty())
        {
            native::stop_audio_stream_for_player(info.caller);
        }
        else
        {
            native::play_audio_stream_for_player(info.caller, p.get_string(0), 0.f, 0.f, 0.f, 0.f, false);
        }
    }));
    REGISTER_COMMAND("shoutcast", api::cmdflag::PLAYER,
                      ([](api::cmdinfo_t info)
    {
        api::parser_cmd p("d", info);
        INVOKE_COMMANDS(info.caller, info.flags,
                        "radio http://yp.shoutcast.com/sbin/tunein-station.pls?id="
                        + boost::lexical_cast<std::string>(p.get<int>(0)));
    }));

}
