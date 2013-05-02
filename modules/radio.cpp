#include "samp.h"
#include "api/cmd2.hpp"
#include "api/pipes.hpp"

#include <string>

#include <boost/lexical_cast.hpp>

#include "util/utils.h"

INIT
{
    REGISTER_COMMAND2("radio", api::cmdflag::PLAYER,
                      ([](int player, const std::string& params) -> bool
    {
        api::parser p("*sr", params);
        std::string str = p.get_string(0);
        if(str == "stop")
        {
            native::stop_audio_stream_for_player(player);
        }
        else
        {
            native::play_audio_stream_for_player(player, str, 0.f, 0.f, 0.f, 0.f, false);
        }
        return true;
    }));
    REGISTER_COMMAND2("shoutcast", api::cmdflag::PLAYER,
                      ([](int player, const std::string& params) -> bool
    {
        api::parser p("*sd", params);
        if(p.error)
        {
            api::send_pipe_msg(player, "Usage: /shoutcast [id]");
            return true;
        }

        return INVOKE_COMMANDS(player, api::cmdflag::PLAYER,
                        "radio http://yp.shoutcast.com/sbin/tunein-station.pls?id="
                        + boost::lexical_cast<std::string>(p.get_int(0)));
    }));

}
