#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <vector>
#include "pawn/natives.h"

class basic_gamemode
{
private:
	std::vector<bool> in_gamemode;
	
public:
	basic_gamemode() : in_gamemode(native::MAX_PLAYERS, false)
	{
	}
	
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

    virtual ~basic_gamemode() {}
};


#endif
