#ifndef NUM_PLAYERS_HPP
#define NUM_PLAYERS_HPP

#include "config.h"

#include <array>
#include <bitset>

#ifndef CONFIG_NUM_PLAYERS
#define CONFIG_NUM_PLAYERS 32
#endif


namespace api {


enum
{
    NUM_PLAYERS = CONFIG_NUM_PLAYERS
};

// const-size containers

template <typename Value>
using array_players = std::array<Value, NUM_PLAYERS>;


using bitset_players = std::bitset<NUM_PLAYERS>;


} // api


#endif // NUM_PLAYERS_HPP
