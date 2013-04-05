//# -*- coding: cp1251 -*-

#include "samp.h"

#include "api/pipes.hpp"
#include "api/counter.hpp"
//#include "api/dialogs.hpp"
#include "api/cmd2.hpp"
#include "api/playerpool.hpp"

#include "gamemode.hpp"

#include "util/rotation.hpp"
#include "util/log.h"


#include <map>
#include <list>
#include <cmath>
#include <fstream>

#include <boost/utility.hpp>

struct checkpoint
{
	float x, y, z;
};

struct vehicle_pos
{
	float x, y, z;
	float angle;
};

struct race_checkpoints_t
{
	typedef std::list<checkpoint> checkpoints_t;
	typedef checkpoints_t::iterator iterator;
	
	checkpoints_t list;
	
    void import_stream(std::istream & s)
    {
      while(!s.eof())
      {
        checkpoint pos;
        s >> pos.x >> pos.y >> pos.z;
        if(pos.x != 0.f && pos.y != 0.f && pos.z != 0.f)
			list.push_back(pos);
      }
    }
    void export_stream(std::ostream & s)
    {
      for(auto& it : list)
      {
        s << it.x << ' ' << it.y << ' ' << it.z << '\n';
      }
    }
    iterator begin()
    {
        return list.begin();
    }
    iterator end()
    {
        return list.end();
    }
};

static int create_vehicle_for_player(int playerid, int model, const vehicle_pos& pos)
{
  if(model != 0)
  {
    native::set_player_pos(playerid, pos.x + 5, pos.y, pos.z + 3);
    int vehid = native::create_vehicle(model, pos.x, pos.y, pos.z, pos.angle, -1, -1, 1200);
    if(vehid < 0 || vehid == native::INVALID_VEHICLE_ID)
      return(0);
    REGISTER_TIMER(2000, ([playerid, vehid]()
    {
      native::put_player_in_vehicle(playerid, vehid, 0);
      throw(signals::timer_stop());
    }));
    return vehid;
  }
  else
  {
    native::set_player_pos(playerid, pos.x, pos.y, pos.z);
    native::set_player_facing_angle(playerid, pos.angle);
    return 0;
  }
}

static void toggle_vehicle_engine(int vehicle, bool toggle)
{
	if(!vehicle)
		return;
    int engine, lights, alarm, doors, bonnet, boot, objective;
    native::get_vehicle_params_ex(vehicle, engine, lights, alarm, doors, bonnet, boot, objective);
    lights = engine = toggle;
    native::set_vehicle_params_ex(vehicle, engine, lights, alarm, doors, bonnet, boot, objective);
}

class race_gamemode : public basic_gamemode
{
public:
	struct player_state
	{
		enum
		{
			DEAD = 0,
			NEWRACE,
			PREPARING,
			COUNTDOWN,
			PLAYING,
			FINISHED
		};
		int state = DEAD;
		
		int vehicle = 0;
		
		race_checkpoints_t::iterator checkpoint;
		int lap = 0;
		
        race_checkpoints_t::iterator get_next_cp() const
		{
			return boost::next(checkpoint);
		}
	};
	enum
	{
		NONE = 0,
		PREPARING,
		COUNTDOWN,
		RACING,
		FINISHED,
		FINISHED_ALL
	};
	int race_state = NONE;
	
	// checkpoints 
	race_checkpoints_t checkpoints;
private:
	std::map<int, player_state> players_states;
	
	int model;
	vehicle_pos p1, p2;
	float row_distance;
	
	int finished_players;

    float size = 14.f;
	
	void setup(int playerid, const vehicle_pos& pos)
	{
		player_state& state = players_states.at(playerid);
		if(state.vehicle != 0)
			native::destroy_vehicle(state.vehicle);
        state.vehicle = create_vehicle_for_player(playerid, model, pos);
		
	}
	
    vehicle_pos get_vehicle_start_position(int place)
	{
		vehicle_pos & root = (place % 2) ? p2 : p1;
		// first = left, second = right, third = behind left 
		int row = place / 2; // row
		float dist = row * row_distance; // distance away from start
		// getting coords
		float angle = util::deg_to_rad(root.angle); // in radians
		vehicle_pos position = root;
		position.x += sin(angle) * dist;
		position.y += cos(angle) * dist;
		return position;
	}
    vehicle_pos get_vehicle_position(const player_state& st)
	{
		vehicle_pos pos;
        pos.x = st.checkpoint->x;
        pos.y = st.checkpoint->y;
        pos.z = st.checkpoint->z + 0.5f;
        pos.angle = 0.0f;
        auto ncp = st.get_next_cp();
        if(ncp != checkpoints.end())
            pos.angle = util::rad_to_deg(atan2(ncp->x - st.checkpoint->x, ncp->y - st.checkpoint->y));
		return pos;
	}
public:
	void change_player_state(int player, int newstate)
	{
		util::log_msg("race/state", "p: %d state: %d", player, newstate);
		
		player_state& state = players_states.at(player);
		state.state = newstate;
		//int oldstate = state.state;
		if(newstate == player_state::PREPARING)
		{
			vehicle_pos pos;
			if(race_state == PREPARING)
			{
				// using playerid as place TODO: replace
                pos = get_vehicle_start_position(player);
                state.checkpoint = checkpoints.begin();
                setup(player, pos);
                toggle_vehicle_engine(state.vehicle, false);
			}
			else // joined in progress or died
			{
                pos = get_vehicle_position(state);
                setup(player, pos);
	            REGISTER_TIMER(4000, ([this, player](){
	                //toggle_vehicle_engine(state.vehicle, true);
	                this->change_player_state(player, player_state::PLAYING);
	                throw signals::timer_stop();
	            }));
			}

		}
		else if(newstate == player_state::DEAD)
		{
			if(state.vehicle != 0)
				native::destroy_vehicle(state.vehicle);
		}
        else if(newstate == player_state::PLAYING/* && oldstate == player_state::COUNTDOWN*/)
        {
            toggle_vehicle_engine(state.vehicle, true);
            on_checkpoint(player);
        }
		// ...
		//state.state = newstate;
	}
	
	void change_race_state(int newstate)
	{
		util::log_msg("race/state", "state: %d", newstate);
		race_state = newstate;
	
		if(newstate == COUNTDOWN)
		{
			static api::counter c(6, -1, [this](api::counter *)
			{
				this->change_race_state(RACING);
			});
			
			c.set_count(6);
			REGISTER_TIMER(1000, c);
		}
        else if(newstate == RACING)
        {
            /*std::for_each(players_states.begin(), players_states.end(), [this](std::pair<const int, player_state>& it)
            {
                this->change_player_state(it.first, player_state::PLAYING);
            });*/
            for(auto it : players_states)
                this->change_player_state(it.first, player_state::PLAYING);
        }
        else if(newstate == PREPARING)
        {
        	finished_players = 0;
            REGISTER_TIMER(2500, ([this](){
                this->change_race_state(COUNTDOWN);
                throw signals::timer_stop();
            }));
            for(auto it : players_states)
                this->change_player_state(it.first, player_state::PREPARING);
        }
		// ...
		//race_state = newstate;
	}
	
	

public:

	void on_checkpoint(int player)
	{
		if(!is_connected(player))
			return;
        auto& state = players_states.at(player);
        if(state.state != player_state::PLAYING)
        {
            native::disable_player_race_checkpoint(player);
            return;
        }
        if(state.checkpoint == checkpoints.end())
        {
            // finished
            ++finished_players;
            change_player_state(player, player_state::FINISHED);
            native::disable_player_race_checkpoint(player);
            return;
        }
        auto next_cp = state.get_next_cp();
        if(next_cp != checkpoints.end())
        {
            native::set_player_race_checkpoint(player, 0, state.checkpoint->x, state.checkpoint->y, state.checkpoint->z,
                                               next_cp->x, next_cp->y, next_cp->z, size);
        }
        else
        {
            native::set_player_race_checkpoint(player, 1, state.checkpoint->x, state.checkpoint->y, state.checkpoint->z,
                                               state.checkpoint->x, state.checkpoint->y, state.checkpoint->z, size);
        }
        ++(state.checkpoint);
	}

    void load(std::istream& s)
    {
        checkpoints.list.clear();
        s >> model;
        s >> p1.x >> p1.y >> p1.z >> p1.angle;
        s >> p2.x >> p2.y >> p2.z >> p2.angle;
        s >> row_distance;
        s >> size;

        float x, y, z;
        s >> x >> y >> z;
        while(!s.fail())
        {
            checkpoints.list.push_back({x, y, z});
            s >> x >> y >> z;
        }
        change_race_state(PREPARING);
    }
	
    void join(int playerid)
    {
        join_gm(playerid);
        players_states[playerid].state = player_state::DEAD;
        players_states[playerid].checkpoint = checkpoints.begin();
    }
    void part(int playerid)
    {
        part_gm(playerid);
        players_states.erase(playerid);
    }

};


INIT
{
    race_gamemode * gm = new race_gamemode;

    REGISTER_CALLBACK(plugin_unload, ([gm](){ delete gm; }));

    REGISTER_CALLBACK(on_game_mode_init, ([](){
        native::manual_vehicle_engine_and_lights();
        INVOKE_COMMANDS(api::pipe::STDOUT, api::cmdflag::SYSTEM, "load_race races/un_autogen_d0a1.txt");
    }));

    REGISTER_CALLBACK(on_player_connect, ([gm](int player){
        gm->join(player);
    }));
    REGISTER_CALLBACK(on_player_disconnect, ([gm](int player, int){
        if(gm->is_connected(player))
            gm->part(player);
    }));
    REGISTER_CALLBACK(on_player_spawn, ([gm](int player) {
        if(gm->is_connected(player))
            gm->change_player_state(player, race_gamemode::player_state::PREPARING);
    }));
    REGISTER_CALLBACK(on_player_death, ([gm](int player, int, int) {
        if(gm->is_connected(player))
            gm->change_player_state(player, race_gamemode::player_state::DEAD);
    }));

    REGISTER_CALLBACK(on_player_enter_race_checkpoint, ([gm](int player) {
        if(gm->is_connected(player))
            gm->on_checkpoint(player);
    }));



    REGISTER_COMMAND2("load_race", api::cmdflag::ADMIN | api::cmdflag::RCON | api::cmdflag::SYSTEM,
                      ([gm](int pipe, const std::string& params)
    {
        api::parser p("*sr", params);
        std::ifstream in (p.get_string(0));
        if(in)
        {
            gm->load(in);
        	api::send_pipe_msgf(pipe, "Loaded: %s", p.get_string(0));
        }
        else
            api::send_pipe_msgf(pipe, "Cannot open: %s", p.get_string(0));
        return true;
    }));
}

