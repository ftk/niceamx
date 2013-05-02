#include "api/pipes.hpp"
#include "api/playerpool.hpp"

#include <boost/circular_buffer.hpp>
#include <string>

#include "signals.hpp"



static boost::circular_buffer<std::string> global_chat(10);



INIT
{
    // hook pipe handler
    api::on_pipe_message.connect([](int pipe, const std::string& msg)
    {
        if(pipe == api::pipe::ALL)
        {
            global_chat.push_back(msg);
        }
    });
    
    REGISTER_CALLBACK(on_player_text, 100000, ([](int player, std::string& text)
    {
        global_chat.push_back(PLAYERBOX->get_info(player).name + ": " + text);
    }));
    // execute first

    REGISTER_CALLBACK(on_player_connect, -100000, ([](int player)
    {
        for(const auto& it : global_chat)
            api::send_pipe_msg(player, it);
    }));
}



