#include "gamemode.hpp"
#include "system/samp.h"
#include <functional>

class test_gamemode : public basic_gamemode
{
public:
	void on_spawn(int playerid) {}
};
static test_gamemode a;
INIT
{
	
	//REGISTER_CALLBACK(on_player_spawn, std::bind(&test_gamemode::on_spawn, &a, std::placeholders::_1));

	test_gamemode * ptr = &a;
	REGISTER_CALLBACK(on_player_spawn, ([ptr](int p) {ptr->on_spawn(p);}));
}
