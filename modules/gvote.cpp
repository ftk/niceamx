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

bool vote_option::execute_command(int pipe, int flags)
{
    return INVOKE_COMMANDS(pipe, flags, this->cmd);
}


INIT
{
    REGISTER_CALLBACK(plugin_load, ([](){ if(!gvotes) gvotes = new vote_container; }));
    REGISTER_CALLBACK(plugin_unload, ([](){ if(gvotes) delete gvotes; gvotes = NULL; }));

    using namespace api::cmdflag;
    REGISTER_COMMAND("gvote_add", CONFIG | RCON | ADMIN, ([](int /*pipe*/, const std::string& params)
    {
        api::parser p("*ssr", params);
        gvotes->add({p.get_string(0), p.get_string(1)});
        return true;
    }));
    REGISTER_COMMAND("gvote_clear", CONFIG | RCON | ADMIN, ([](int /*pipe*/, const std::string&)
    {
        gvotes->clear();
        return true;
    }));
}


