#ifndef TDM_GM_HPP
#define TDM_GM_HPP

#include "api/num_players.hpp"
#include "api/weapons.hpp"
#include "gamemode.hpp"
#include "api/playerpool.hpp"

#include "api/location.hpp"

#include "samp.h"

#include <vector>

struct team
{
    unsigned color;
    int total_score = 0;
    int players = 0;

    std::vector<api::location> spawns;

    team(unsigned color) : color(color) {}

    api::location get_rand_spawn()
    {
        if(spawns.empty())
            return {};
        return spawns[rand() % spawns.size()];
    }
};

struct player
{
    int teamid = -1;
    int score;

};

class tdm_gm : public basic_gamemode
{
public:
    std::vector<team> teams;
    api::array_players<player> players;

    api::weapons weaponset;

    tdm_gm() {}

    int get_unbalanced_team() const
    {
        int min_players = INT_MAX;
        int teamid = -1;
        // TODO: balance by score
        for(unsigned i = 0; i < teams.size(); i++)
        {
            if(teams[i].players < min_players)
            {
                min_players = teams[i].players;
                teamid = i;
            }
        }
        return teamid;
    }
    team& player_team(int player)
    {
        return teams.at(players.at(player).teamid);
    }

    void setup(int playerid)
    {
        // tp
        player_team(playerid).get_rand_spawn().teleport_player(playerid);

        // weap
        weaponset.setup(playerid);
        // color
        //native::set_player_color(playerid, player_team(playerid).color);
        PLAYERBOX->get_info(playerid).set_color(player_team(playerid).color);
        // ...
        // TODO: magic
        native::set_player_health(playerid, 100.f);
        native::set_player_armour(playerid, 0.f);

        native::reset_player_money(playerid);
    }

    void join(int playerid) override
    {
        join_gm(playerid);

        const int newteam = get_unbalanced_team();
        assert(newteam != -1);

        players[playerid].teamid = newteam;
        teams.at(newteam).players++;

        //setup(playerid);
    }

    void part(int playerid) override
    {
        player_team(playerid).players--;
        players[playerid].teamid = -1;

        part_gm(playerid);
    }

    void on_kill(int killer, int victim)
    {
        int score = 1;
        if(players[killer].teamid == players[victim].teamid)
            score = -1; // teamkill
        players[killer].score += score;
        native::set_player_score(killer, players[killer].score);
        native::give_player_money(killer, score);

        player_team(killer).total_score += score;
        // ...
    }



};

#endif // TDM_GM_HPP
