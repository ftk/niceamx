#include "tdm_gm.hpp"
#include "signals.hpp"

#include "api/cmd2.hpp"

static tdm_gm gamemode;

INIT
{
    using namespace api::cmdflag;
    // config
    REGISTER_COMMAND("tdm_add_team", CONFIG, [](api::cmdinfo_t info)
    {
        api::parser p("?x", info);
        gamemode.teams.push_back({static_cast<unsigned>(p.get<long long>(0))});
    });
    REGISTER_COMMAND("tdm_team_add_spawn", CONFIG, [](api::cmdinfo_t info)
    {
        api::parser p("dfff?fd", info);
        const int teamid = p.get<int>(0);
        gamemode.teams[teamid].spawns.push_back({p.get<float>(1), p.get<float>(2), p.get<float>(3), p.get(4, 0.f), p.get(5, 0)});
    });

    REGISTER_COMMAND("tdm_weapons", CONFIG, [](api::cmdinfo_t info)
    {
        api::parser p("?d+", info);
        gamemode.weaponset.reset();
        for(std::size_t i = 0; i < (p.size()/2); i++)
        {
            const int id = p.get<int>(i*2),
                    ammo = p.get<int>(i*2+1);
            gamemode.weaponset.set_weapon(id, ammo);
        }
    });

    REGISTER_COMMAND("tdm_join", PLAYER, [](api::cmdinfo_t info)
    {
        GAMEMODESBOX->join(info.caller, &gamemode);
        gamemode.setup(info.caller);
    });
    REGISTER_COMMAND("tdm_part", PLAYER, [](api::cmdinfo_t info)
    {
        GAMEMODESBOX->part(info.caller, &gamemode);
    });


    REGISTER_CALLBACK(on_player_death, [](int victim, int killer, int weapon)
    {
        if(gamemode.is_connected(killer) && gamemode.is_connected(victim))
        {
            gamemode.on_kill(killer, victim);
            native::send_death_message(killer, victim, weapon);
        }
    });
    REGISTER_CALLBACK(on_player_spawn, [](int player)
    {
        if(gamemode.is_connected(player))
            gamemode.setup(player);
    });

    REGISTER_CALLBACK(on_player_connect, [](int player)
    {
        GAMEMODESBOX->join(player, &gamemode);
    });
    REGISTER_CALLBACK(on_player_disconnect, [](int player, int)
    {
        GAMEMODESBOX->part(player, &gamemode);
    });

}
