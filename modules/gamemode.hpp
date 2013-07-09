#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include "api/num_players.hpp"

#include <array>


#include "util/singleton.hpp"

class basic_gamemode
{
private:
    api::array_players<bool> in_gamemode;
	
public:
    basic_gamemode()
	{
        in_gamemode.fill(false);
	}
    virtual ~basic_gamemode() {}
    	
protected:
	void join_gm(int playerid)
	{
		in_gamemode.at(playerid) = true;
	}
	void part_gm(int playerid)
	{
		in_gamemode.at(playerid) = false;
	}
	
public:
	virtual bool is_connected(int playerid)
	{
		return in_gamemode.at(playerid);
	}

	virtual void join(int playerid) { join_gm(playerid); }
	virtual void part(int playerid) { part_gm(playerid); }


};

class gamemodes : public util::singleton<gamemodes>
{
    friend class util::singleton<gamemodes>;
    api::array_players<basic_gamemode *> player_gm;

    gamemodes()
    {
        player_gm.fill(NULL);
    }
public:
    void join(int playerid, basic_gamemode * gm)
    {
        if(player_gm[playerid] && player_gm[playerid]->is_connected(playerid))
            player_gm[playerid]->part(playerid);
        gm->join(playerid);
        player_gm[playerid] = gm;
    }
    void part(int playerid, basic_gamemode * gm = NULL) // null - part from any gm
    {
        if(gm && player_gm[playerid] != gm)
            return;
        if(player_gm[playerid] && player_gm[playerid]->is_connected(playerid))
            player_gm[playerid]->part(playerid);
        player_gm[playerid] = NULL;
    }
    
    basic_gamemode * get_gamemode(int playerid)
    {
    	return player_gm.at(playerid);
    }
};

#define GAMEMODESBOX (gamemodes::get_instance())


#endif
