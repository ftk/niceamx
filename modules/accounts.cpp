#include "samp.h"

#include "api/playerpool.hpp"
#include "api/cmd2.hpp"
#include "api/pipes.hpp"
#include "api/accounts.hpp"
#include "api/gconfig.hpp"
#include "accounts.h"

#include <cstring>


static const std::string default_hdr = "data/accounts_hdr.bin",
    default_db = "data/accounts_db.bin";
static api::accounts_manager<player_account> accounts;//(default_hdr, default_db);

bool account_registered(const std::string& name)
{
    return accounts.count(name);
}

void account_create(const std::string& name, player_account& acc)
{
    return accounts.create(name, acc);
}

player_account account_get(const std::string& name)
{
    return accounts.get(name);
}

void account_set(const std::string& name, player_account& acc)
{
    return accounts.set(name, acc);
}

void account_remove(const std::string& name)
{
    return accounts.remove(util::hash_rt(name.c_str()));
}



INIT
{
    REGISTER_COMMAND("register", api::cmdflag::PLAYER, [](api::cmdinfo_t info)
    {
        auto i = PLAYERBOX->get_info(info.caller);
        if(account_registered(i.name))
        {
            api::send_pipe_msg(info.caller, "Already registered!");
            return;
        }
        api::parser_cmd p("r", info);
        player_account acc;
        acc.set_password(p.get_string(0));

        account_create(i.name, acc);


        api::send_pipe_msgf(info.caller, "Account created! Password: \"%s\"",
                            p.get_string(0));
    });


    CONFIGBOX->set("accounts_hdr", default_hdr);
    CONFIGBOX->set("accounts_db", default_db);

    REGISTER_CALLBACK(on_game_mode_init, []()
    {
        accounts.reopen(CONFIGBOX->get("accounts_hdr"),
                        CONFIGBOX->get("accounts_db"));

    });
    REGISTER_CALLBACK(on_player_disconnect, [](int /*id*/, int)
    {
    	if(PLAYERBOX->size() == 1)
    	{
    		// last player
    		// sync
    		accounts.flush();
    	}
    });
}


