#include "pawn/natives.h"
#include "pawn/pawnlog.hpp"

#include <boost/preprocessor/stringize.hpp>
#include <iostream>
#define DEBUG_NATIVE(f,p) std::cout << BOOST_PP_STRINGIZE(f) "(" << p << ");" << std::endl
#define SEPARATOR << ", " <<

namespace pawn
{
  class string_len
  {
  public:
    enum {val = 256};
  };
}

typedef int cell;

#define START() /***/
#define CALL_NATIVE(m,...) std::cout << BOOST_PP_STRINGIZE(f) << std::endl
#define CALL_NATIVE_R(m,...) ((std::cout << BOOST_PP_STRINGIZE(f) << std::endl),1)

#define NATIVE /* */

namespace native
{

    //Методы сампа

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_objects.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	NATIVE int create_object (int model_id, float x, float y, float z, float rx, float ry, float rz, float draw_distance) 
    {
        START();
        
        cell _R; return (int) CALL_NATIVE_R(create_object, model_id, x, y, z, rx, ry, rz, draw_distance);
    }
	NATIVE void set_object_pos (int object_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_object_pos, object_id, x, y, z);
    }
	NATIVE void get_object_pos (int object_id, float& x, float& y, float& z) 
    {
        START();
        
        CALL_NATIVE(get_object_pos, object_id, x, y, z);
    }
	NATIVE void set_object_rot (int object_id, float rx, float ry, float rz) 
    {
        START();
        
        CALL_NATIVE(set_object_rot, object_id, rx, ry, rz);
    }
	NATIVE void get_object_rot (int object_id, float& rx, float& ry, float& rz) 
    {
        START();
        
        CALL_NATIVE(get_object_rot, object_id, rx, ry, rz);
    }
	NATIVE bool is_valid_object (int object_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_valid_object, object_id);
    }
	NATIVE void destroy_object (int object_id) 
    {
        START();
        
        CALL_NATIVE(destroy_object, object_id);
    }
	NATIVE void move_object (int object_id, float x, float y, float z, float speed) 
    {
        START();
        
        CALL_NATIVE(move_object, object_id, x, y, z, speed);
    }
	NATIVE void stop_object (int object_id) 
    {
        START();
        
        CALL_NATIVE(stop_object, object_id);
    }
	NATIVE int create_player_object (int player_id, int model_id, float x, float y, float z, float rx, float ry, float rz, float draw_distance) 
    {
        START();
        
        cell _R; return (int) CALL_NATIVE_R(create_player_object, player_id, model_id, x, y, z, rx, ry, rz, draw_distance);
    }
	NATIVE void set_player_object_pos (int player_id, int object_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_player_object_pos, player_id, object_id, x, y, z);
    }
	NATIVE void get_player_object_pos (int player_id, int object_id, float& x, float& y, float& z) 
    {
        START();
        
        CALL_NATIVE(get_player_object_pos, player_id, object_id, x, y, z);
    }
	NATIVE void set_player_object_rot (int player_id, int object_id, float rx, float ry, float rz) 
    {
        START();
        
        CALL_NATIVE(set_player_object_rot, player_id, object_id, rx, ry, rz);
    }
	NATIVE void get_player_object_rot (int player_id, int object_id, float& rx, float& ry, float& rz) 
    {
        START();
        
        CALL_NATIVE(get_player_object_rot, player_id, object_id, rx, ry, rz);
    }
	NATIVE bool is_valid_player_object (int player_id, int object_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_valid_player_object, player_id, object_id);
    }
	NATIVE void destroy_player_object (int player_id, int object_id) 
    {
        START();
        
        CALL_NATIVE(destroy_player_object, player_id, object_id);
    }
	NATIVE void move_player_object (int player_id, int object_id, float x, float y, float z, float speed) 
    {
        START();
        
        CALL_NATIVE(move_player_object, player_id, object_id, x, y, z, speed);
    }
	NATIVE void stop_player_object (int player_id, int object_id) 
    {
        START();
        
        CALL_NATIVE(stop_player_object, player_id, object_id);
    }
	NATIVE void attach_object_to_player (int object_id, int player_id, float offset_x, float offset_y, float offset_z, float offset_rx, float offset_ry, float offset_rz) 
    {
        START();
        
        CALL_NATIVE(attach_object_to_player, object_id, player_id, offset_x, offset_y, offset_z, offset_rx, offset_ry, offset_rz);
    }
	NATIVE void attach_player_object_to_player (int object_player_id, int object_id, int attach_player_id, float offset_x, float offset_y, float offset_z, float offset_rx, float offset_ry, float offset_rz) 
    {
        START();
        
        CALL_NATIVE(attach_player_object_to_player, object_player_id, object_id, attach_player_id, offset_x, offset_y, offset_z, offset_rx, offset_ry, offset_rz);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_players.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Player
	NATIVE void set_spawn_info (int player_id, int team_id, int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3) 
    {
        START();
        
        CALL_NATIVE(set_spawn_info, player_id, team_id, skin_id, x, y, z, rz, weapon_id1, weapon_ammo1, weapon_id2, weapon_ammo2, weapon_id3, weapon_ammo3);
    }
	NATIVE void spawn_player (int player_id) 
    {
        START();
        
        CALL_NATIVE(spawn_player, player_id);
    }

    // Player info
	NATIVE void set_player_pos (int player_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_player_pos, player_id, x, y, z);
    }
	NATIVE void set_player_pos_findz (int player_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_player_pos_findz, player_id, x, y, z);
    }
	NATIVE void get_player_pos (int player_id, float& x, float& y, float& z) 
    {
        START();
        
        CALL_NATIVE(get_player_pos, player_id, x, y, z);
    }
	NATIVE void set_player_facing_angle (int player_id, float rz) 
    {
        START();
        
        CALL_NATIVE(set_player_facing_angle, player_id, rz);
    }
	NATIVE float get_player_facing_angle (int player_id) 
    {
        START();
        float rz;
        
        CALL_NATIVE(get_player_facing_angle, player_id, rz);
        return rz;
    }
	NATIVE bool is_player_in_range_of_point (int player_id, float range, float x, float y, float z) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_in_range_of_point, player_id, range, x, y, z);
    }
	NATIVE bool is_player_streamed_in (int player_id, int for_player_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_streamed_in, player_id, for_player_id);
    }
	NATIVE void set_player_interior (int player_id, int interior_id) 
    {
        START();
        
        CALL_NATIVE(set_player_interior, player_id, interior_id);
    }
	NATIVE int get_player_interior (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_interior, player_id);
    }
	NATIVE void set_player_health (int player_id, float health) 
    {
        START();
        
        CALL_NATIVE(set_player_health, player_id, health);
    }
	NATIVE float get_player_health (int player_id) 
    {
        START();
        float rezult;
        
        CALL_NATIVE(get_player_health, player_id, rezult);
        return rezult;
    }
	NATIVE void set_player_armour (int player_id, float armour) 
    {
        START();
        
        CALL_NATIVE(set_player_armour, player_id, armour);
    }
	NATIVE float get_player_armour (int player_id) 
    {
        START();
        float rezult;
        
        CALL_NATIVE(get_player_armour, player_id, rezult);
        return rezult;
    }
	NATIVE void set_player_ammo (int player_id, int weapon_slot, int ammo) 
    {
        START();
        
        CALL_NATIVE(set_player_ammo, player_id, weapon_slot, ammo);
    }
	NATIVE int get_player_ammo (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_ammo, player_id);
    }
	NATIVE weapon_state get_player_weapon_state (int player_id) 
    {
        START();
        
        cell _R; return static_cast<weapon_state>(CALL_NATIVE_R(get_player_weapon_state, player_id));
    }
	NATIVE void set_player_team (int player_id, int team_id) 
    {
        START();
        
        CALL_NATIVE(set_player_team, player_id, team_id);
    }
	NATIVE int get_player_team (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_team, player_id);
    }
	NATIVE void set_player_score (int player_id, int score) 
    {
        START();
        
        CALL_NATIVE(set_player_score, player_id, score);
    }
	NATIVE int get_player_score (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_score, player_id);
    }
	NATIVE int get_player_drunk_level (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_drunk_level, player_id);
    }
	NATIVE void set_player_drunk_level (int player_id, int level) 
    {
        START();
        
        CALL_NATIVE(set_player_drunk_level, player_id, level);
    }
	NATIVE void set_player_color (int player_id, unsigned color) 
    {
        START();
        
        CALL_NATIVE(set_player_color, player_id, color);
    }
	NATIVE unsigned get_player_color (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_color, player_id);
    }
	NATIVE void set_player_skin (int player_id, int skin_id) 
    {
        START();
        
        CALL_NATIVE(set_player_skin, player_id, skin_id);
    }
	NATIVE int get_player_skin (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_skin, player_id);
    }
	NATIVE void give_player_weapon (int player_id, int weapon_id, int weapon_ammo) 
    {
        START();
        
        CALL_NATIVE(give_player_weapon, player_id, weapon_id, weapon_ammo);
    }
	NATIVE void reset_player_weapons (int player_id) 
    {
        START();
        
        CALL_NATIVE(reset_player_weapons, player_id);
    }
	NATIVE void set_player_armed_weapon (int player_id, int weapon_id) 
    {
        START();
        
        CALL_NATIVE(set_player_armed_weapon, player_id, weapon_id);
    }
	NATIVE void get_player_weapon_data (int player_id, int slot, int& weapon_id, int& weapon_ammo) 
    {
        START();
        
        CALL_NATIVE(get_player_weapon_data, player_id, slot, weapon_id, weapon_ammo);
    }
	NATIVE void give_player_money (int player_id, int money) 
    {
        START();
        
        CALL_NATIVE(give_player_money, player_id, money);
    }
	NATIVE void reset_player_money (int player_id) 
    {
        START();
        
        CALL_NATIVE(reset_player_money, player_id);
    }
	NATIVE int set_player_name (int player_id, std::string const& name) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(set_player_name, player_id, name);
    }
	NATIVE int get_player_money (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_money, player_id);
    }
	NATIVE player_state get_player_state (int player_id) 
    {
        START();
        
        cell _R; return static_cast<player_state>(CALL_NATIVE_R(get_player_state, player_id));
    }
	NATIVE std::string get_player_ip (int player_id) 
    {
        START();
        std::string rezult;
        
        CALL_NATIVE(get_player_ip, player_id, rezult, pawn::string_len::val);
        return rezult;
    }
	NATIVE int get_player_ping (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_ping, player_id);
    }
	NATIVE int get_player_weapon (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_weapon, player_id);
    }
	NATIVE void get_player_keys (int player_id, int& keys, int& updown, int& leftright) 
    {
        START();
        
        CALL_NATIVE(get_player_keys, player_id, keys, updown, leftright);
    }
	NATIVE std::string get_player_name (int player_id) 
    {
        START();
        std::string rezult;
        
        CALL_NATIVE(get_player_name, player_id, rezult, pawn::string_len::val);
        return rezult;
    }
	NATIVE void set_player_time (int player_id, int hour, int minute) 
    {
        START();
        
        CALL_NATIVE(set_player_time, player_id, hour, minute);
    }
	NATIVE void get_player_time (int player_id, int& hour, int& minute) 
    {
        START();
        
        CALL_NATIVE(get_player_time, player_id, hour, minute);
    }
	NATIVE void toggle_player_clock (int player_id, int toggle) 
    {
        START();
        
        CALL_NATIVE(toggle_player_clock, player_id, toggle);
    }
	NATIVE void set_player_weather (int player_id, int weather) 
    {
        START();
        
        CALL_NATIVE(set_player_weather, player_id, weather);
    }
	NATIVE void force_class_selection (int player_id) 
    {
        START();
        
        CALL_NATIVE(force_class_selection, player_id);
    }
	NATIVE void set_player_wanted_level (int player_id, int level) 
    {
        START();
        
        CALL_NATIVE(set_player_wanted_level, player_id, level);
    }
	NATIVE int get_player_wanted_level (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_wanted_level, player_id);
    }
	NATIVE void set_player_fighting_style (int player_id, fight_style style) 
    {
        START();
        
        CALL_NATIVE(set_player_fighting_style, player_id, style);
    }
	NATIVE fight_style get_player_fighting_style (int player_id) 
    {
        START();
        
        cell _R; return static_cast<fight_style>(CALL_NATIVE_R(get_player_fighting_style, player_id));
    }
	NATIVE void set_player_velocity (int player_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_player_velocity, player_id, x, y, z);
    }
	NATIVE void get_player_velocity (int player_id, float& x, float& y, float& z) 
    {
        START();
        
        CALL_NATIVE(get_player_velocity, player_id, x, y, z);
    }
	NATIVE void play_crime_report_for_player (int player_id, int suspect_id, int crime_id) 
    {
        START();
        
        CALL_NATIVE(play_crime_report_for_player, player_id, suspect_id, crime_id);
    }
	NATIVE void set_player_shop_name (int player_id, std::string const& shop_name) 
    {
        START();
        
        CALL_NATIVE(set_player_shop_name, player_id, shop_name);
    }
	NATIVE void set_player_skill_level (int player_id, weapon_skill skill, int level) 
    {
        START();
        
        CALL_NATIVE(set_player_skill_level, player_id, skill, level);
    }
	NATIVE int get_player_surfing_vehicle_id (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_surfing_vehicle_id, player_id);
    }




    // 0.3c -------------------------------

	NATIVE void set_player_attached_object (int player_id, int index, int model_id, bones bone_id, float offset_x, float offset_y, float offset_z, float rx, float ry, float rz, float sx, float sy, float sz, int materialcolor1, int materialcolor2)
    {
        START();
        
        CALL_NATIVE(set_player_attached_object, player_id, index, model_id, bone_id, offset_x, offset_y, offset_z, rx, ry, rz, sx, sy, sz, materialcolor1, materialcolor2);
    }

	NATIVE void remove_player_attached_object (int player_id, int index) 
    {
        START();
        
        CALL_NATIVE(remove_player_attached_object, player_id, index);
    }
	NATIVE bool is_player_attached_object_slot_used (int player_id, int index) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_attached_object_slot_used, player_id, index);
    }
	NATIVE void attach_object_to_vehicle (int object_id, int vehicle_id, float offset_x, float offset_y, float offset_z, float rx, float ry, float rz)
    {
        START();
        
        CALL_NATIVE(attach_object_to_vehicle, object_id, vehicle_id, offset_x, offset_y, offset_z, rx, ry, rz);
    }
    // /0.3c


	NATIVE void set_player_chat_bubble (int player_id, std::string const& text, unsigned int color, float draw_distance, int expire_time) 
    {
        START();
        
        CALL_NATIVE(set_player_chat_bubble, player_id, text, color, draw_distance, expire_time);
    }

    // Player controls
	NATIVE void put_player_in_vehicle (int player_id, int vehicle_id, int seat_id) 
    {
        START();
        
        CALL_NATIVE(put_player_in_vehicle, player_id, vehicle_id, seat_id);
    }
	NATIVE int get_player_vehicle_id (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_vehicle_id, player_id);
    }
	NATIVE int get_player_vehicle_seat (int player_id) 
    {
        START();
        
        cell _R; CALL_NATIVE_R(get_player_vehicle_seat, player_id);
        return _R >= 8 ? -1 : _R;
    }
	NATIVE void remove_player_from_vehicle (int player_id) 
    {
        START();
        
        CALL_NATIVE(remove_player_from_vehicle, player_id);
    }
	NATIVE void toggle_player_controllable (int player_id, bool is_unfreeze) 
    {
        START();
        
        CALL_NATIVE(toggle_player_controllable, player_id, is_unfreeze);
    }
	NATIVE void player_play_sound (int player_id, int sound_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(player_play_sound, player_id, sound_id, x, y, z);
    }
	NATIVE void apply_animation (int player_id, std::string const& anim_lib, std::string const& anim_name, float delta, int loop, int lock_x, int lock_y, int freeze, int time, int forcesync) 
    {
        START();
        
        CALL_NATIVE(apply_animation, player_id, anim_lib, anim_name, delta, loop, lock_x, lock_y, freeze, time, forcesync);
    }
	NATIVE void clear_animations (int player_id, int forcesync) 
    {
        START();
        
        CALL_NATIVE(clear_animations, player_id, forcesync);
    }
	NATIVE int get_player_animation_index (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_animation_index, player_id);
    }
	NATIVE void get_animation_name (int index, std::string& anim_lib, std::string& anim_name) 
    {
        START();
        
        CALL_NATIVE(get_animation_name, index, anim_lib, pawn::string_len::val, anim_name, pawn::string_len::val);
    }
	NATIVE special_action get_player_special_action (int player_id) 
    {
        START();
        
        cell _R; return static_cast<special_action>(CALL_NATIVE_R(get_player_special_action, player_id));
    }
	NATIVE void set_player_special_action (int player_id, special_action action_id) 
    {
        START();
        
        CALL_NATIVE(set_player_special_action, player_id, action_id);
    }

    // Player world/map related
	NATIVE void set_player_checkpoint (int player_id, float x, float y, float z, float size) 
    {
        START();
        
        CALL_NATIVE(set_player_checkpoint, player_id, x, y, z, size);
    }
	NATIVE void disable_player_checkpoint (int player_id) 
    {
        START();
        
        CALL_NATIVE(disable_player_checkpoint, player_id);
    }
	NATIVE void set_player_race_checkpoint (int player_id, int type_id, float x, float y, float z, float next_x, float next_y, float next_z, float size) 
    {
        START();
        
        CALL_NATIVE(set_player_race_checkpoint, player_id, type_id, x, y, z, next_x, next_y, next_z, size);
    }
	NATIVE void disable_player_race_checkpoint (int player_id) 
    {
        START();
        
        CALL_NATIVE(disable_player_race_checkpoint, player_id);
    }
	NATIVE void set_player_world_bounds (int player_id, float x_max, float x_min, float y_max, float y_min) 
    {
        START();
        
        CALL_NATIVE(set_player_world_bounds, player_id, x_max, x_min, y_max, y_min);
    }
	NATIVE void set_player_marker_for_player (int player_id, int show_player_id, unsigned color) 
    {
        START();
        
        CALL_NATIVE(set_player_marker_for_player, player_id, show_player_id, color);
    }
	NATIVE void show_player_name_tag_for_player (int player_id, int show_player_id, bool show) 
    {
        START();
        
        CALL_NATIVE(show_player_name_tag_for_player, player_id, show_player_id, show);
    }
	NATIVE void set_player_mapicon (int player_id, int icon_id, float x, float y, float z, int markertype, unsigned color) 
    {
        START();
        
        CALL_NATIVE(set_player_mapicon, player_id, icon_id, x, y, z, markertype, color);
    }
	NATIVE void remove_player_mapicon (int player_id, int icon_id) 
    {
        START();
        
        CALL_NATIVE(remove_player_mapicon, player_id, icon_id);
    }
	NATIVE void allow_player_teleport (int player_id, bool allow) 
    {
        START();
        
        CALL_NATIVE(allow_player_teleport, player_id, allow);
    }
    
    // Player camera
	NATIVE void set_player_camera_pos (int player_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_player_camera_pos, player_id, x, y, z);
    }
    /*
	NATIVE void set_player_camera_look_at (int player_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_player_camera_look_at, player_id, x, y, z);
    }
    */
	NATIVE void set_camera_behind_player (int player_id) 
    {
        START();
        
        CALL_NATIVE(set_camera_behind_player, player_id);
    }
	NATIVE void get_player_camera_pos (int player_id, float& x, float& y, float& z) 
    {
        START();
        
        CALL_NATIVE(get_player_camera_pos, player_id, x, y, z);
    }

	NATIVE void get_player_camera_front_vector (int player_id, float& x, float& y, float& z) 
    {
        START();
        
        CALL_NATIVE(get_player_camera_front_vector, player_id, x, y, z);
    }

    // Player conditionals
	NATIVE bool is_player_connected (int player_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_connected, player_id);
    }
	NATIVE bool is_player_in_vehicle (int player_id, int vehicle_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_in_vehicle, player_id, vehicle_id);
    }
	NATIVE bool is_player_in_any_vehicle (int player_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_in_any_vehicle, player_id);
    }
	NATIVE bool is_player_in_checkpoint (int player_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_in_checkpoint, player_id);
    }
	NATIVE bool is_player_in_race_checkpoint (int player_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_in_race_checkpoint, player_id);
    }

    // Virtual Worlds
	NATIVE void set_player_virtual_world (int player_id, int world_id) 
    {
        START();
        
        CALL_NATIVE(set_player_virtual_world, player_id, world_id);
    }
	NATIVE int get_player_virtual_world (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_virtual_world, player_id);
    }

    // Insane Stunts
	NATIVE void enable_stunt_bonus_for_player (int player_id, bool enable) 
    {
        START();
        
        CALL_NATIVE(enable_stunt_bonus_for_player, player_id, enable);
    }
	NATIVE void enable_stunt_bonus_for_all (bool enable) 
    {
        START();
        
        CALL_NATIVE(enable_stunt_bonus_for_all, enable);
    }

    // Spectating
	NATIVE void toggle_player_spectating (int player_id, bool toggle) 
    {
        START();
        
        CALL_NATIVE(toggle_player_spectating, player_id, toggle);
    }
	NATIVE void player_spectate_player (int player_id, int target_player_id, spectate_mode mode) 
    {
        START();
        
        CALL_NATIVE(player_spectate_player, player_id, target_player_id, mode);
    }
	NATIVE void player_spectate_vehicle (int player_id, int target_vehicle_id, spectate_mode mode) 
    {
        START();
        
        CALL_NATIVE(player_spectate_vehicle, player_id, target_vehicle_id, mode);
    }
    
    // Recording for NPC playback
	NATIVE void start_recording_player_data (int player_id, player_recording_type record_type, std::string const& record_name) 
    {
        START();
        
        CALL_NATIVE(start_recording_player_data, player_id, record_type, record_name);
    }
	NATIVE void stop_recording_player_data (int player_id) 
    {
        START();
        
        CALL_NATIVE(stop_recording_player_data, player_id);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_samp.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Util
	NATIVE void send_client_message (int player_id, unsigned color, std::string const& message) 
    {
        START();
        
        CALL_NATIVE(send_client_message, player_id, color, message);
    }
	NATIVE void send_player_message_to_player (int player_id, int sender_id, std::string const& message) 
    {
        START();
        
        CALL_NATIVE(send_player_message_to_player, player_id, sender_id, message);
    }
	NATIVE void send_death_message (int killer_id, int killed_id, int weapon_id) 
    {
        START();
        
        CALL_NATIVE(send_death_message, killer_id, killed_id, weapon_id);
    }
	NATIVE void game_text_for_player (int player_id, std::string const& string, int time, int style) 
    {
        START();
        
        CALL_NATIVE(game_text_for_player, player_id, string, time, style);
    }
	NATIVE int get_max_players () 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_max_players, );
    }

    // Game
	NATIVE void set_game_mode_text (std::string const& text) 
    {
        START();
        
        CALL_NATIVE(set_game_mode_text, text);
    }
	NATIVE void set_team_count (int count) 
    {
        START();
        
        CALL_NATIVE(set_team_count, count);
    }
	NATIVE int add_player_class (int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(add_player_class, skin_id, x, y, z, rz, weapon_id1, weapon_ammo1, weapon_id2, weapon_ammo2, weapon_id3, weapon_ammo3);
    }
	NATIVE int add_player_class_ex (int team_id, int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(add_player_class_ex, team_id, skin_id, x, y, z, rz, weapon_id1, weapon_ammo1, weapon_id2, weapon_ammo2, weapon_id3, weapon_ammo3);
    }
	NATIVE void add_static_vehicle (int model_id, float x, float y, float z, float rz, int color_id1, int color_id2) 
    {
        START();
        
        CALL_NATIVE(add_static_vehicle, model_id, x, y, z, rz, color_id1, color_id2);
    }
	NATIVE int add_static_vehicle_ex (int model_id, float x, float y, float z, float rz, int color_id1, int color_id2, int respawn_delay) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(add_static_vehicle_ex, model_id, x, y, z, rz, color_id1, color_id2, respawn_delay);
    }
	NATIVE void add_static_pickup (int model_id, int type, float x, float y, float z, int virtual_world) 
    {
        START();
        
        CALL_NATIVE(add_static_pickup, model_id, type, x, y, z, virtual_world);
    }
	NATIVE int create_pickup (int model_id, int type, float x, float y, float z, int virtual_world) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(create_pickup, model_id, type, x, y, z, virtual_world);
    }
	NATIVE void destroy_pickup (int pickup_id) 
    {
        START();
        
        CALL_NATIVE(destroy_pickup, pickup_id);
    }
	NATIVE void show_name_tags (bool is_show) 
    {
        START();
        
        CALL_NATIVE(show_name_tags, is_show);
    }
	NATIVE void show_player_markers (player_markers_mode mode) 
    {
        START();
        
        CALL_NATIVE(show_player_markers, mode);
    }
	NATIVE void gamemode_exit () 
    {
        START();
        
        CALL_NATIVE(gamemode_exit, );
    }
	NATIVE void set_world_time (int hour) 
    {
        START();
        
        CALL_NATIVE(set_world_time, hour);
    }
	NATIVE std::string get_weapon_name (int weapon_id) 
    {
        START();
        std::string rezult;
        
        CALL_NATIVE(get_weapon_name, weapon_id, rezult, pawn::string_len::val);
        return rezult;
    }
	NATIVE void enable_tire_popping (bool is_enable) 
    {
        START();
        
        CALL_NATIVE(enable_tire_popping, is_enable);
    }
	NATIVE void allow_interior_weapons (bool is_allow) 
    {
        START();
        
        CALL_NATIVE(allow_interior_weapons, is_allow);
    }
	NATIVE void set_weather (int weather_id) 
    {
        START();
        
        CALL_NATIVE(set_weather, weather_id);
    }
	NATIVE void set_gravity (float gravity) 
    {
        START();
        
        CALL_NATIVE(set_gravity, gravity);
    }
	NATIVE void allow_admin_teleport (bool is_allow) 
    {
        START();
        
        CALL_NATIVE(allow_admin_teleport, is_allow);
    }
	NATIVE void set_death_drop_amount (int amount) 
    {
        START();
        
        CALL_NATIVE(set_death_drop_amount, amount);
    }
	NATIVE void create_explosion (float x, float y, float z, int type, float radius) 
    {
        START();
        
        CALL_NATIVE(create_explosion, x, y, z, type, radius);
    }
	NATIVE void enable_zone_names (bool is_enable) 
    {
        START();
        
        CALL_NATIVE(enable_zone_names, is_enable);
    }
	NATIVE void use_player_ped_anims () 
    {
        START();
        
        CALL_NATIVE(use_player_ped_anims, );
    }
	NATIVE void disable_interior_enter_exits () 
    {
        START();
        
        CALL_NATIVE(disable_interior_enter_exits, );
    }
	NATIVE void set_name_tag_draw_distance (float distance) 
    {
        START();
        
        CALL_NATIVE(set_name_tag_draw_distance, distance);
    }
	NATIVE void disable_name_tag_los () 
    {
        START();
        
        CALL_NATIVE(disable_name_tag_los, );
    }
	NATIVE void limit_global_chat_radius (float chat_radius) 
    {
        START();
        
        CALL_NATIVE(limit_global_chat_radius, chat_radius);
    }
	NATIVE void limit_player_marker_radius (float marker_radius) 
    {
        START();
        
        CALL_NATIVE(limit_player_marker_radius, marker_radius);
    }

    // Npc
	NATIVE void connect_npc (std::string const& name, std::string const& script) 
    {
        START();
        
        CALL_NATIVE(connect_npc, name, script);
    }
	NATIVE bool is_player_npc (int player_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_npc, player_id);
    }

    // Admin
	NATIVE bool is_player_admin (int player_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_player_admin, player_id);
    }
	NATIVE void kick (int player_id) 
    {
        START();
        
        CALL_NATIVE(kick, player_id);
    }
	NATIVE void ban (int player_id) 
    {
        START();
        
        CALL_NATIVE(ban, player_id);
    }
	NATIVE void ban_ex (int player_id, std::string const& reason) 
    {
        START();
        
        CALL_NATIVE(ban_ex, player_id, reason);
    }
	NATIVE void send_rcon_command (std::string const& command) 
    {
        START();
        
        CALL_NATIVE(send_rcon_command, command);
    }
	NATIVE std::string get_server_var_as_string (std::string const& var_name) 
    {
        START();
        std::string rezult;
        
        CALL_NATIVE(get_server_var_as_string, var_name, rezult, pawn::string_len::val);
        return rezult;
    }
	NATIVE int get_server_var_as_int (std::string const& var_name) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_server_var_as_int, var_name);
    }
	NATIVE bool get_server_var_as_bool (std::string const& var_name) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(get_server_var_as_bool, var_name);
    }

    // Menu
	NATIVE int create_menu (std::string const& title, int columns, float x, float y, float col1width, float col2width) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(create_menu, title, columns, x, y, col1width, col2width);
    }
	NATIVE void destroy_menu (int menu_id) 
    {
        START();
        
        CALL_NATIVE(destroy_menu, menu_id);
    }
	NATIVE void add_menu_item (int menu_id, int column, std::string const& text) 
    {
        START();
        
        CALL_NATIVE(add_menu_item, menu_id, column, text);
    }
	NATIVE void set_menu_column_header (int menu_id, int column, std::string const& header) 
    {
        START();
        
        CALL_NATIVE(set_menu_column_header, menu_id, column, header);
    }
	NATIVE void show_menu_for_player (int menu_id, int player_id) 
    {
        START();
        
        CALL_NATIVE(show_menu_for_player, menu_id, player_id);
    }
	NATIVE void hide_menu_for_player (int menu_id, int player_id) 
    {
        START();
        
        CALL_NATIVE(hide_menu_for_player, menu_id, player_id);
    }
	NATIVE bool is_valid_menu (int menu_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_valid_menu, menu_id);
    }
	NATIVE void disable_menu (int menu_id) 
    {
        START();
        
        CALL_NATIVE(disable_menu, menu_id);
    }
	NATIVE void disable_menu_row (int menu_id, int row) 
    {
        START();
        
        CALL_NATIVE(disable_menu_row, menu_id, row);
    }
	NATIVE int get_player_menu (int player_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_menu, player_id);
    }

    // Text Draw
	NATIVE int textdraw_create (float x, float y, std::string const& text) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(textdraw_create, x, y, text);
    }
	NATIVE void textdraw_destroy (int text_id) 
    {
        START();
        
        CALL_NATIVE(textdraw_destroy, text_id);
    }
	NATIVE void textdraw_letter_size (int text_id, float x, float y) 
    {
        START();
        
        CALL_NATIVE(textdraw_letter_size, text_id, x, y);
    }
	NATIVE void textdraw_text_size (int text_id, float x, float y) 
    {
        START();
        
        CALL_NATIVE(textdraw_text_size, text_id, x, y);
    }
	NATIVE void textdraw_alignment (int text_id, int alignment) 
    {
        START();
        
        CALL_NATIVE(textdraw_alignment, text_id, alignment);
    }
	NATIVE void textdraw_color (int text_id, unsigned color) 
    {
        START();
        
        CALL_NATIVE(textdraw_color, text_id, color);
    }
	NATIVE void textdraw_use_box (int text_id, int use) 
    {
        START();
        
        CALL_NATIVE(textdraw_use_box, text_id, use);
    }
	NATIVE void textdraw_box_color (int text_id, unsigned color) 
    {
        START();
        
        CALL_NATIVE(textdraw_box_color, text_id, color);
    }
	NATIVE void textdraw_set_shadow (int text_id, int size) 
    {
        START();
        
        CALL_NATIVE(textdraw_set_shadow, text_id, size);
    }
	NATIVE void textdraw_set_outline (int text_id, int size) 
    {
        START();
        
        CALL_NATIVE(textdraw_set_outline, text_id, size);
    }
	NATIVE void textdraw_background_color (int text_id, unsigned color) 
    {
        START();
        
        CALL_NATIVE(textdraw_background_color, text_id, color);
    }
	NATIVE void textdraw_font (int text_id, int font) 
    {
        START();
        
        CALL_NATIVE(textdraw_font, text_id, font);
    }
	NATIVE void textdraw_set_proportional (int text_id, bool set) 
    {
        START();
        
        CALL_NATIVE(textdraw_set_proportional, text_id, set);
    }
	NATIVE void textdraw_show_for_player (int player_id, int text_id) 
    {
        START();
        
        CALL_NATIVE(textdraw_show_for_player, player_id, text_id);
    }
	NATIVE void textdraw_hide_for_player (int player_id, int text_id) 
    {
        START();
        
        CALL_NATIVE(textdraw_hide_for_player, player_id, text_id);
    }
	NATIVE void textdraw_set_string (int text_id, std::string const& text) 
    {
        START();
        
        CALL_NATIVE(textdraw_set_string, text_id, text);
    }

    // Gang Zones
	NATIVE int gangzone_create (float minx, float miny, float maxx, float maxy) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(gangzone_create, minx, miny, maxx, maxy);
    }
	NATIVE void gangzone_destroy (int zone_id) 
    {
        START();
        
        CALL_NATIVE(gangzone_destroy, zone_id);
    }
	NATIVE void gangzone_show_for_player (int player_id, int zone_id, unsigned int color) 
    {
        START();
        
        CALL_NATIVE(gangzone_show_for_player, player_id, zone_id, color);
    }
	NATIVE void gangzone_hide_for_player (int player_id, int zone_id) 
    {
        START();
        
        CALL_NATIVE(gangzone_hide_for_player, player_id, zone_id);
    }
	NATIVE void gangzone_flash_for_player (int player_id, int zone_id, unsigned int flashcolor) 
    {
        START();
        
        CALL_NATIVE(gangzone_flash_for_player, player_id, zone_id, flashcolor);
    }
	NATIVE void gangzone_stop_flash_for_player (int player_id, int zone_id) 
    {
        START();
        
        CALL_NATIVE(gangzone_stop_flash_for_player, player_id, zone_id);
    }

    // Global 3D Text Labels
	NATIVE int create_3dtextlabel (std::string const& text, unsigned int color, float x, float y, float z, float draw_distance, int world, bool is_test_los) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(create_3dtextlabel, text, color, x, y, z, draw_distance, world, is_test_los);
    }
	NATIVE void delete_3dtextlabel (int text3d_id) 
    {
        START();
        
        CALL_NATIVE(delete_3dtextlabel, text3d_id);
    }
	NATIVE void attach_3dtextlabel_to_player (int text3d_id, int player_id, float offset_x, float offset_y, float offset_z) 
    {
        START();
        
        CALL_NATIVE(attach_3dtextlabel_to_player, text3d_id, player_id, offset_x, offset_y, offset_z);
    }
	NATIVE void attach_3dtextlabel_to_vehicle (int text3d_id, int vehicle_id, float offset_x, float offset_y, float offset_z) 
    {
        START();
        
        CALL_NATIVE(attach_3dtextlabel_to_vehicle, text3d_id, vehicle_id, offset_x, offset_y, offset_z);
    }
	NATIVE void update_3dtextlabel_text (int text3d_id, unsigned int color, std::string const& text) 
    {
        START();
        
        CALL_NATIVE(update_3dtextlabel_text, text3d_id, color, text);
    }

    // Per-player 3D Text Labels
	NATIVE int create_player3dtextlabel (int player_id, std::string const& text, unsigned int color, float x, float y, float z, float draw_distance, int attached_player_id, int attached_vehicle_id, bool is_test_los) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(create_player3dtextlabel, player_id, text, color, x, y, z, draw_distance, attached_player_id, attached_vehicle_id, is_test_los);
    }
	NATIVE void delete_player3dtextlabel (int player_id, int playertext3d_id) 
    {
        START();
        
        CALL_NATIVE(delete_player3dtextlabel, player_id, playertext3d_id);
    }
	NATIVE void update_player3dtextlabel_text (int player_id, int playertext3d_id, unsigned int color, std::string const& text) 
    {
        START();
        
        CALL_NATIVE(update_player3dtextlabel_text, player_id, playertext3d_id, color, text);
    }

    // Player GUI Dialog
	NATIVE void show_player_dialog (int player_id, int dialog_id, dialog_style style, std::string const& caption, std::string const& info, std::string const& button_ok, std::string const& button_cancel) 
    {
        START();
        
        CALL_NATIVE(show_player_dialog, player_id, dialog_id, style, caption, info, button_ok, button_cancel);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_vehicles.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Vehicle
	NATIVE int create_vehicle (int vehicle_model, float x, float y, float z, float rz, int color_id1, int color_id2, int respawn_delay) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(create_vehicle, vehicle_model, x, y, z, rz, color_id1, color_id2, respawn_delay);
    }
	NATIVE void destroy_vehicle (int vehicle_id) 
    {
        START();
        
        CALL_NATIVE(destroy_vehicle, vehicle_id);
    }
	NATIVE bool is_vehicle_streamed_in (int vehicle_id, int for_player_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_vehicle_streamed_in, vehicle_id, for_player_id);
    }
	NATIVE void get_vehicle_pos (int vehicle_id, float& x, float& y, float& z) 
    {
        START();
        
        CALL_NATIVE(get_vehicle_pos, vehicle_id, x, y, z);
    }
	NATIVE void set_vehicle_pos (int vehicle_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_vehicle_pos, vehicle_id, x, y, z);
    }
	NATIVE float get_vehicle_zangle (int vehicle_id) 
    {
        START();
        float rz;
        
        CALL_NATIVE(get_vehicle_zangle, vehicle_id, rz);
        return rz;
    }
	NATIVE void get_vehicle_rotation_quat (int vehicle_id, float& w, float& x, float& y, float& z) 
    {
        START();
        
        CALL_NATIVE(get_vehicle_rotation_quat, vehicle_id, w, x, y, z);
    }
	NATIVE void set_vehicle_zangle (int vehicle_id, float rz) 
    {
        START();
        
        CALL_NATIVE(set_vehicle_zangle, vehicle_id, rz);
    }
	NATIVE void set_vehicle_params_for_player (int vehicle_id, int player_id, bool objective, bool doorslocked) 
    {
        START();
        
        CALL_NATIVE(set_vehicle_params_for_player, vehicle_id, player_id, objective, doorslocked);
    }
	NATIVE void set_vehicle_to_respawn (int vehicle_id) 
    {
        START();
        
        CALL_NATIVE(set_vehicle_to_respawn, vehicle_id);
    }
	NATIVE void link_vehicle_to_interior (int vehicle_id, int interior_id) 
    {
        START();
        
        CALL_NATIVE(link_vehicle_to_interior, vehicle_id, interior_id);
    }
	NATIVE void add_vehicle_component (int vehicle_id, int component_id) 
    {
        START();
        
        CALL_NATIVE(add_vehicle_component, vehicle_id, component_id);
    }
	NATIVE void remove_vehicle_component (int vehicle_id, int component_id) 
    {
        START();
        
        CALL_NATIVE(remove_vehicle_component, vehicle_id, component_id);
    }
	NATIVE void change_vehicle_color (int vehicle_id, int color_id1, int color_id2) 
    {
        START();
        
        CALL_NATIVE(change_vehicle_color, vehicle_id, color_id1, color_id2);
    }
	NATIVE void change_vehicle_paintjob (int vehicle_id, int paintjob_id) 
    {
        START();
        
        CALL_NATIVE(change_vehicle_paintjob, vehicle_id, paintjob_id);
    }
	NATIVE void set_vehicle_health (int vehicle_id, float health) 
    {
        START();
        
        CALL_NATIVE(set_vehicle_health, vehicle_id, health);
    }
	NATIVE float get_vehicle_health (int vehicle_id) 
    {
        START();
        float health;
        
        CALL_NATIVE(get_vehicle_health, vehicle_id, health);
        return health;
    }
	NATIVE void attach_trailer_to_vehicle (int trailer_id, int vehicle_id) 
    {
        START();
        
        CALL_NATIVE(attach_trailer_to_vehicle, trailer_id, vehicle_id);
    }
	NATIVE void detach_trailer_from_vehicle (int vehicle_id) 
    {
        START();
        
        CALL_NATIVE(detach_trailer_from_vehicle, vehicle_id);
    }
	NATIVE bool is_trailer_attached_to_vehicle (int vehicle_id) 
    {
        START();
        
        cell _R; return 0 != CALL_NATIVE_R(is_trailer_attached_to_vehicle, vehicle_id);
    }
	NATIVE int get_vehicle_trailer (int vehicle_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_vehicle_trailer, vehicle_id);
    }
	NATIVE void set_vehicle_number_plate (int vehicle_id, std::string const& numberplate) 
    {
        START();
        
        CALL_NATIVE(set_vehicle_number_plate, vehicle_id, numberplate);
    }
	NATIVE int get_vehicle_model (int vehicle_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_vehicle_model, vehicle_id);
    }
	NATIVE int get_vehicle_component_in_slot (int vehicle_id, carmod_type slot) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_vehicle_component_in_slot, vehicle_id, slot);
    }
	NATIVE carmod_type get_vehicle_component_type (int component_id) 
    {
        START();
        
        cell _R; return static_cast<carmod_type>(CALL_NATIVE_R(get_vehicle_component_type, component_id));
    }
	NATIVE void repair_vehicle (int vehicle_id) 
    {
        START();
        
        CALL_NATIVE(repair_vehicle, vehicle_id);
    }
	NATIVE void get_vehicle_velocity (int vehicle_id, float& x, float& y, float& z) 
    {
        START();
        
        CALL_NATIVE(get_vehicle_velocity, vehicle_id, x, y, z);
    }
	NATIVE void set_vehicle_velocity (int vehicle_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_vehicle_velocity, vehicle_id, x, y, z);
    }
	NATIVE void set_vehicle_angular_velocity (int vehicle_id, float x, float y, float z) 
    {
        START();
        
        CALL_NATIVE(set_vehicle_angular_velocity, vehicle_id, x, y, z);
    }
	NATIVE void get_vehicle_damage_status (int vehicle_id, int& panels, int& doors, int& lights, int& tires) 
    {
        START();
        
        CALL_NATIVE(get_vehicle_damage_status, vehicle_id, panels, doors, lights, tires);
    }
	NATIVE void update_vehicle_damage_status (int vehicle_id, int panels, int doors, int lights, int tires) 
    {
        START();
        
        CALL_NATIVE(update_vehicle_damage_status, vehicle_id, panels, doors, lights, tires);
    }

    // Virtual Worlds
	NATIVE void set_vehicle_virtual_world (int vehicle_id, int world_id) 
    {
        START();
        
        CALL_NATIVE(set_vehicle_virtual_world, vehicle_id, world_id);
    }
	NATIVE int get_vehicle_virtual_world (int vehicle_id) 
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_vehicle_virtual_world, vehicle_id);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Недокументированные возможности
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	NATIVE std::string get_serial (int player_id) 
    {
        START();
        std::string rezult;
        
        CALL_NATIVE(gpci, player_id, rezult, pawn::string_len::val);
        return rezult;
    }
    
    /***  0.3e ***/
	NATIVE void manual_vehicle_engine_and_lights ()
	{
		START();
        
		CALL_NATIVE(manual_vehicle_engine_and_lights, );  
	}
	NATIVE void set_vehicle_params_ex (int vehicleid, int engine, int lights, int alarm, int doors, int bonnet, int boot, int objective)
	{
		START();
		
		CALL_NATIVE(set_vehicle_params_ex, vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);  
	}
	NATIVE void get_vehicle_params_ex (int vehicleid, int& engine, int& lights, int& alarm, int& doors, int& bonnet, int& boot, int& objective)
	{
		START();
		
		CALL_NATIVE(get_vehicle_params_ex, vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);  
	}
	NATIVE void get_vehicle_model_info (int vehiclemodel, int infotype, float& X, float& Y, float& Z)
	{
		START();
		
		CALL_NATIVE(get_vehicle_model_info, vehiclemodel, infotype, X, Y, Z);  
	}

	NATIVE int get_player_target_player (int playerid)
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_target_player, playerid);
    }
	NATIVE int play_audio_stream_for_player (int playerid, const std::string& url, float posX, float posY, float posZ, float distance, int usepos)
    {
        START();
        
        cell _R; return CALL_NATIVE_R(play_audio_stream_for_player, playerid, url, posX, posY, posZ, distance, usepos);
    }
	NATIVE int stop_audio_stream_for_player (int playerid)
    {
        START();
        
        cell _R; return CALL_NATIVE_R(stop_audio_stream_for_player, playerid);
    }
	NATIVE int get_player_surfing_object_id (int playerid)
    {
        START();
        
        cell _R; return CALL_NATIVE_R(get_player_surfing_object_i_d, playerid);
    }
	NATIVE int remove_building_for_player (int playerid, int modelid, float fX, float fY, float fZ, float fRadius)
    {
        START();
        
        cell _R; return CALL_NATIVE_R(remove_building_for_player, playerid, modelid, fX, fY, fZ, fRadius);
    }


	NATIVE int set_player_map_icon (int playerid, int iconid, float x, float y, float z, int markertype, int color, int style)
    {
        START();
        cell _R; return CALL_NATIVE_R(set_player_map_icon,  playerid, iconid, x, y, z, markertype, color, style);
    }
	NATIVE int set_player_camera_look_at (int playerid, float x, float y, float z, camera_cut cut)
    {
        START();
        cell _R; return CALL_NATIVE_R(set_player_camera_look_at,  playerid, x, y, z, static_cast<int>(cut));
    }
	NATIVE int get_player_camera_mode (int playerid)
    {
        START();
        cell _R; return CALL_NATIVE_R(get_player_camera_mode,  playerid);
    }
	NATIVE int attach_camera_to_object (int playerid, int objectid)
    {
        START();
        cell _R; return CALL_NATIVE_R(attach_camera_to_object,  playerid, objectid);
    }
	NATIVE int attach_camera_to_player_object (int playerid, int playerobjectid)
    {
        START();
        cell _R; return CALL_NATIVE_R(attach_camera_to_player_object,  playerid, playerobjectid);
    }
	NATIVE int interpolate_camera_pos (int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, camera_cut cut)
    {
        START();
        cell _R; return CALL_NATIVE_R(interpolate_camera_pos,  playerid, FromX, FromY, FromZ, ToX, ToY, ToZ, time, static_cast<int>(cut));
    }
	NATIVE int interpolate_camera_look_at (int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, camera_cut cut)
    {
        START();
        cell _R; return CALL_NATIVE_R(interpolate_camera_look_at,  playerid, FromX, FromY, FromZ, ToX, ToY, ToZ, time, static_cast<int>(cut));
    }

}

