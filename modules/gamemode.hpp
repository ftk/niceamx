#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include "api/num_players.hpp"

#include <array>

#include "pawn/natives.h"

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


#endif
