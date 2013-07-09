#include "gvote.hpp"

#include "signals.hpp"


#include "api/cmd2.hpp"
#include "api/dialogs.hpp"


vote_container * gvotes = NULL;

/*
void show_gvote_dialog(int playerid)
{
    SHOW_DIALOG(api::dialog_list, ([](int, bool succ, int item)
    {
        if(succ)
        {
            gvotes.vote(item);
        }
    }), playerid, "title", gvotes.join('\n'), "Y", "N");
}*/

bool vote_option::execute_command(int pipe, unsigned flags)
{
    return INVOKE_COMMANDS(pipe, flags, this->cmd);
}


INIT
{
    if(!gvotes) gvotes = new vote_container;
    //REGISTER_CALLBACK(plugin_load, ([](){ if(!gvotes) gvotes = new vote_container; }));
    REGISTER_CALLBACK(plugin_unload, ([](){ if(gvotes) delete gvotes; gvotes = NULL; }));

    using namespace api::cmdflag;
    REGISTER_COMMAND("gvote_add", CONFIG | RCON | ADMIN, ([](api::cmdinfo_t info)
    {
        api::parser_cmd p("sr", info);
        gvotes->add({p.get_string(0), p.get_string(1)});
    }));
    REGISTER_COMMAND("gvote_clear", CONFIG | RCON | ADMIN, ([](api::cmdinfo_t)
    {
        gvotes->clear();
    }));
}


