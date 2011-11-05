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


namespace native
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_objects.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int create_object (int model_id, float x, float y, float z, float rx, float ry, float rz, float draw_distance)
    {
        DEBUG_NATIVE(/*f*/create_object, /*p*/model_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz SEPARATOR  draw_distance);
        return(0);
    }
    void set_object_pos (int object_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_object_pos, /*p*/object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void get_object_pos (int object_id, float& x, float& y, float& z)
    {

        DEBUG_NATIVE(/*f*/get_object_pos, /*p*/object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void set_object_rot (int object_id, float rx, float ry, float rz)
    {
        DEBUG_NATIVE(/*f*/set_object_rot, /*p*/object_id SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
    }
    void get_object_rot (int object_id, float& rx, float& ry, float& rz)
    {
        DEBUG_NATIVE(/*f*/get_object_rot, /*p*/object_id SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
    }
    bool is_valid_object (int object_id)
    {
        DEBUG_NATIVE(/*f*/is_valid_object, /*p*/object_id);
        return(0);
    }
    void destroy_object (int object_id)
    {
        DEBUG_NATIVE(/*f*/destroy_object, /*p*/object_id);
    }
    void move_object (int object_id, float x, float y, float z, float speed)
    {
        DEBUG_NATIVE(/*f*/move_object, /*p*/object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  speed);
    }
    void stop_object (int object_id)
    {
        DEBUG_NATIVE(/*f*/stop_object, /*p*/object_id);
    }
    int create_player_object (int player_id, int model_id, float x, float y, float z, float rx, float ry, float rz, float draw_distance)
    {
        DEBUG_NATIVE(/*f*/create_player_object, /*p*/player_id SEPARATOR  model_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz SEPARATOR  draw_distance);
        return(0);
    }
    void set_player_object_pos (int player_id, int object_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_player_object_pos, /*p*/player_id SEPARATOR  object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void get_player_object_pos (int player_id, int object_id, float& x, float& y, float& z)
    {
        DEBUG_NATIVE(/*f*/get_player_object_pos, /*p*/player_id SEPARATOR  object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void set_player_object_rot (int player_id, int object_id, float rx, float ry, float rz)
    {
        DEBUG_NATIVE(/*f*/set_player_object_rot, /*p*/player_id SEPARATOR  object_id SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
    }
    void get_player_object_rot (int player_id, int object_id, float& rx, float& ry, float& rz)
    {
        DEBUG_NATIVE(/*f*/get_player_object_rot, /*p*/player_id SEPARATOR  object_id SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
    }
    bool is_valid_player_object (int player_id, int object_id)
    {
        DEBUG_NATIVE(/*f*/is_valid_player_object, /*p*/player_id SEPARATOR  object_id);
        return(0);
    }
    void destroy_player_object (int player_id, int object_id)
    {
        DEBUG_NATIVE(/*f*/destroy_player_object, /*p*/player_id SEPARATOR  object_id);
    }
    void move_player_object (int player_id, int object_id, float x, float y, float z, float speed)
    {
        DEBUG_NATIVE(/*f*/move_player_object, /*p*/player_id SEPARATOR  object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  speed);
    }
    void stop_player_object (int player_id, int object_id)
    {
        DEBUG_NATIVE(/*f*/stop_player_object, /*p*/player_id SEPARATOR  object_id);
    }
    void attach_object_to_player (int object_id, int player_id, float offset_x, float offset_y, float offset_z, float offset_rx, float offset_ry, float offset_rz)
    {
        DEBUG_NATIVE(/*f*/attach_object_to_player, /*p*/object_id SEPARATOR  player_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  offset_rx SEPARATOR  offset_ry SEPARATOR  offset_rz);
    }
    void attach_player_object_to_player (int object_player_id, int object_id, int attach_player_id, float offset_x, float offset_y, float offset_z, float offset_rx, float offset_ry, float offset_rz)
    {
        DEBUG_NATIVE(/*f*/attach_player_object_to_player, /*p*/object_player_id SEPARATOR  object_id SEPARATOR  attach_player_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  offset_rx SEPARATOR  offset_ry SEPARATOR  offset_rz);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_players.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Player
    void set_spawn_info (int player_id, int team_id, int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3)
    {
        DEBUG_NATIVE(/*f*/set_spawn_info, /*p*/player_id SEPARATOR  team_id SEPARATOR  skin_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  weapon_id1 SEPARATOR  weapon_ammo1 SEPARATOR  weapon_id2 SEPARATOR  weapon_ammo2 SEPARATOR  weapon_id3 SEPARATOR  weapon_ammo3);
    }
    void spawn_player (int player_id)
    {
        DEBUG_NATIVE(/*f*/spawn_player, /*p*/player_id);
    }

    // Player info
    void set_player_pos (int player_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_player_pos, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void set_player_pos_findz (int player_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_player_pos_findz, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void get_player_pos (int player_id, float& x, float& y, float& z)
    {
        DEBUG_NATIVE(/*f*/get_player_pos, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void set_player_facing_angle (int player_id, float rz)
    {
        DEBUG_NATIVE(/*f*/set_player_facing_angle, /*p*/player_id SEPARATOR  rz);
    }
    float get_player_facing_angle (int player_id)
    {
        float rz;
        DEBUG_NATIVE(/*f*/get_player_facing_angle, /*p*/player_id SEPARATOR  rz);
        return rz;
    }
    bool is_player_in_range_of_point (int player_id, float range, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/is_player_in_range_of_point, /*p*/player_id SEPARATOR  range SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        return(0);
    }
    bool is_player_streamed_in (int player_id, int for_player_id)
    {
        DEBUG_NATIVE(/*f*/is_player_streamed_in, /*p*/player_id SEPARATOR  for_player_id);
        return(0);
    }
    void set_player_interior (int player_id, int interior_id)
    {
        DEBUG_NATIVE(/*f*/set_player_interior, /*p*/player_id SEPARATOR  interior_id);
    }
    int get_player_interior (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_interior, /*p*/player_id);
        return(0);
    }
    void set_player_health (int player_id, float health)
    {
        DEBUG_NATIVE(/*f*/set_player_health, /*p*/player_id SEPARATOR  health);
    }
    float get_player_health (int player_id)
    {
        float rezult;
        DEBUG_NATIVE(/*f*/get_player_health, /*p*/player_id SEPARATOR  rezult);
        return rezult;
    }
    void set_player_armour (int player_id, float armour)
    {
        DEBUG_NATIVE(/*f*/set_player_armour, /*p*/player_id SEPARATOR  armour);
    }
    float get_player_armour (int player_id)
    {
        float rezult;
        DEBUG_NATIVE(/*f*/get_player_armour, /*p*/player_id SEPARATOR  rezult);
        return rezult;
    }
    void set_player_ammo (int player_id, int weapon_slot, int ammo)
    {
        DEBUG_NATIVE(/*f*/set_player_ammo, /*p*/player_id SEPARATOR  weapon_slot SEPARATOR  ammo);
    }
    int get_player_ammo (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_ammo, /*p*/player_id);
        return(0);
    }
    weapon_state get_player_weapon_state (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_weapon_state, /*p*/player_id);
        return weapon_state(0);
    }
    void set_player_team (int player_id, int team_id)
    {
        DEBUG_NATIVE(/*f*/set_player_team, /*p*/player_id SEPARATOR  team_id);
    }
    int get_player_team (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_team, /*p*/player_id);
        return(0);
    }
    void set_player_score (int player_id, int score)
    {
        DEBUG_NATIVE(/*f*/set_player_score, /*p*/player_id SEPARATOR  score);
    }
    int get_player_score (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_score, /*p*/player_id);
        return(0);
    }
    int get_player_drunk_level (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_drunk_level, /*p*/player_id);
        return(0);
    }
    void set_player_drunk_level (int player_id, int level)
    {
        DEBUG_NATIVE(/*f*/set_player_drunk_level, /*p*/player_id SEPARATOR  level);
    }
    void set_player_color (int player_id, unsigned color)
    {
        DEBUG_NATIVE(/*f*/set_player_color, /*p*/player_id SEPARATOR  color);
    }
    unsigned get_player_color (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_color, /*p*/player_id);
        return(0);
    }
    void set_player_skin (int player_id, int skin_id)
    {
        DEBUG_NATIVE(/*f*/set_player_skin, /*p*/player_id SEPARATOR  skin_id);
    }
    int get_player_skin (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_skin, /*p*/player_id);
        return(0);
    }
    void give_player_weapon (int player_id, int weapon_id, int weapon_ammo)
    {
        DEBUG_NATIVE(/*f*/give_player_weapon, /*p*/player_id SEPARATOR  weapon_id SEPARATOR  weapon_ammo);
    }
    void reset_player_weapons (int player_id)
    {
        DEBUG_NATIVE(/*f*/reset_player_weapons, /*p*/player_id);
    }
    void set_player_armed_weapon (int player_id, int weapon_id)
    {
        DEBUG_NATIVE(/*f*/set_player_armed_weapon, /*p*/player_id SEPARATOR  weapon_id);
    }
    void get_player_weapon_data (int player_id, int slot, int& weapon_id, int& weapon_ammo)
    {
        DEBUG_NATIVE(/*f*/get_player_weapon_data, /*p*/player_id SEPARATOR  slot SEPARATOR  weapon_id SEPARATOR  weapon_ammo);
    }
    void give_player_money (int player_id, int money)
    {
        DEBUG_NATIVE(/*f*/give_player_money, /*p*/player_id SEPARATOR  money);
    }
    void reset_player_money (int player_id)
    {
        DEBUG_NATIVE(/*f*/reset_player_money, /*p*/player_id);
    }
    int set_player_name (int player_id, std::string const& name)
    {
        DEBUG_NATIVE(/*f*/set_player_name, /*p*/player_id SEPARATOR  name);
        return(0);
    }
    int get_player_money (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_money, /*p*/player_id);
        return(0);
    }
    player_state get_player_state (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_state, /*p*/player_id);
        return player_state(0);
    }
    std::string get_player_ip (int player_id)
    {
        std::string rezult = "";
        DEBUG_NATIVE(/*f*/get_player_ip, /*p*/player_id SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        return rezult;
    }
    int get_player_ping (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_ping, /*p*/player_id);
        return(0);
    }
    int get_player_weapon (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_weapon, /*p*/player_id);
        return(0);
    }
    void get_player_keys (int player_id, int& keys, int& updown, int& leftright)
    {
        DEBUG_NATIVE(/*f*/get_player_keys, /*p*/player_id SEPARATOR  keys SEPARATOR  updown SEPARATOR  leftright);
    }
    std::string get_player_name (int player_id)
    {
        std::string rezult;
        DEBUG_NATIVE(/*f*/get_player_name, /*p*/player_id SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        return rezult;
    }
    void set_player_time (int player_id, int hour, int minute)
    {
        DEBUG_NATIVE(/*f*/set_player_time, /*p*/player_id SEPARATOR  hour SEPARATOR  minute);
    }
    void get_player_time (int player_id, int& hour, int& minute)
    {
        DEBUG_NATIVE(/*f*/get_player_time, /*p*/player_id SEPARATOR  hour SEPARATOR  minute);
    }
    void toggle_player_clock (int player_id, int toggle)
    {
        DEBUG_NATIVE(/*f*/toggle_player_clock, /*p*/player_id SEPARATOR  toggle);
    }
    void set_player_weather (int player_id, int weather)
    {
        DEBUG_NATIVE(/*f*/set_player_weather, /*p*/player_id SEPARATOR  weather);
    }
    void force_class_selection (int player_id)
    {
        DEBUG_NATIVE(/*f*/force_class_selection, /*p*/player_id);
    }
    void set_player_wanted_level (int player_id, int level)
    {
        DEBUG_NATIVE(/*f*/set_player_wanted_level, /*p*/player_id SEPARATOR  level);
    }
    int get_player_wanted_level (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_wanted_level, /*p*/player_id);
        return(0);
    }
    void set_player_fighting_style (int player_id, fight_style style)
    {
        DEBUG_NATIVE(/*f*/set_player_fighting_style, /*p*/player_id SEPARATOR  style);
    }
    fight_style get_player_fighting_style (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_fighting_style, /*p*/player_id);
        return fight_style(0);
    }
    void set_player_velocity (int player_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_player_velocity, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void get_player_velocity (int player_id, float& x, float& y, float& z)
    {
        DEBUG_NATIVE(/*f*/get_player_velocity, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void play_crime_report_for_player (int player_id, int suspect_id, int crime_id)
    {
        DEBUG_NATIVE(/*f*/play_crime_report_for_player, /*p*/player_id SEPARATOR  suspect_id SEPARATOR  crime_id);
    }
    void set_player_shop_name (int player_id, std::string const& shop_name)
    {
        DEBUG_NATIVE(/*f*/set_player_shop_name, /*p*/player_id SEPARATOR  shop_name);
    }
    void set_player_skill_level (int player_id, weapon_skill skill, int level)
    {
        DEBUG_NATIVE(/*f*/set_player_skill_level, /*p*/player_id SEPARATOR  skill SEPARATOR  level);
    }
    int get_player_surfing_vehicle_id (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_surfing_vehicle_id, /*p*/player_id);
        return(0);
    }
#ifdef _03B
    void set_player_holding_object (int player_id, int model_id, bones bone_id, float offset_x, float offset_y, float offset_z, float rx, float ry, float rz)
    {
        DEBUG_NATIVE(/*f*/set_player_holding_object, /*p*/player_id SEPARATOR  model_id SEPARATOR  bone_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
    }
    void stop_player_holding_object (int player_id)
    {
        DEBUG_NATIVE(/*f*/stop_player_holding_object, /*p*/player_id);
    }
    bool is_player_holding_object (int player_id)
    {
        DEBUG_NATIVE(/*f*/is_player_holding_object, /*p*/player_id);
        return(0);
    }
#endif
#ifdef _03C
    void set_player_attached_object (int player_id, int index, int model_id, bones bone_id, float offset_x, float offset_y, float offset_z, float rx, float ry, float rz, float sx, float sy, float sz)
    {
        DEBUG_NATIVE(/*f*/set_player_attached_object,
		     /*p*/player_id SEPARATOR index SEPARATOR model_id SEPARATOR  bone_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz SEPARATOR sx SEPARATOR  sy SEPARATOR  sz);
    }
    void remove_player_attached_object (int player_id, int index)
    {
        DEBUG_NATIVE(/*f*/remove_player_attached_object, /*p*/player_id SEPARATOR index);
    }
    bool is_player_attached_object_slot_used (int player_id, int index)
    {
        DEBUG_NATIVE(/*f*/is_player_attached_object_slot_used_t, /*p*/player_id SEPARATOR index);
        return(0);
    }
    void attach_object_to_vehicle (int vehicle_id, int model_id, float offset_x, float offset_y, float offset_z, float rx, float ry, float rz)
    {
        DEBUG_NATIVE(/*f*/attach_object_to_vehicle,
		     /*p*/player_id SEPARATOR index SEPARATOR model_id SEPARATOR  bone_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
    }
#endif


    void set_player_chat_bubble (int player_id, std::string const& text, unsigned int color, float draw_distance, int expire_time)
    {
        DEBUG_NATIVE(/*f*/set_player_chat_bubble, /*p*/player_id SEPARATOR  text SEPARATOR  color SEPARATOR  draw_distance SEPARATOR  expire_time);
    }

    // Player controls
    void put_player_in_vehicle (int player_id, int vehicle_id, int seat_id)
    {
        DEBUG_NATIVE(/*f*/put_player_in_vehicle, /*p*/player_id SEPARATOR  vehicle_id SEPARATOR  seat_id);
    }
    int get_player_vehicle_id (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_vehicle_id, /*p*/player_id);
        return(0);
    }
    int get_player_vehicle_seat (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_vehicle_seat, /*p*/player_id);
        return(0);
    }
    void remove_player_from_vehicle (int player_id)
    {
        DEBUG_NATIVE(/*f*/remove_player_from_vehicle, /*p*/player_id);
    }
    void toggle_player_controllable (int player_id, bool is_unfreeze)
    {
        DEBUG_NATIVE(/*f*/toggle_player_controllable, /*p*/player_id SEPARATOR  is_unfreeze);
    }
    void player_play_sound (int player_id, int sound_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/player_play_sound, /*p*/player_id SEPARATOR  sound_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void apply_animation (int player_id, std::string const& anim_lib, std::string const& anim_name, float delta, int loop, int lock_x, int lock_y, int freeze, int time, int forcesync)
    {
        DEBUG_NATIVE(/*f*/apply_animation, /*p*/player_id SEPARATOR  anim_lib SEPARATOR  anim_name SEPARATOR  delta SEPARATOR  loop SEPARATOR  lock_x SEPARATOR  lock_y SEPARATOR  freeze SEPARATOR  time SEPARATOR  forcesync);
    }
    void clear_animations (int player_id, int forcesync)
    {
        DEBUG_NATIVE(/*f*/clear_animations, /*p*/player_id SEPARATOR  forcesync);
    }
    int get_player_animation_index (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_animation_index, /*p*/player_id);
        return(0);
    }
    void get_animation_name (int index, std::string& anim_lib, std::string& anim_name)
    {
        DEBUG_NATIVE(/*f*/get_animation_name, /*p*/index SEPARATOR  anim_lib SEPARATOR  pawn::string_len::val SEPARATOR  anim_name SEPARATOR  pawn::string_len::val);
    }
    special_action get_player_special_action (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_special_action, /*p*/player_id);
        return special_action(0);
    }
    void set_player_special_action (int player_id, special_action action_id)
    {
        DEBUG_NATIVE(/*f*/set_player_special_action, /*p*/player_id SEPARATOR  action_id);
    }

    // Player world/map related
    void set_player_checkpoint (int player_id, float x, float y, float z, float size)
    {
        DEBUG_NATIVE(/*f*/set_player_checkpoint, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  size);
    }
    void disable_player_checkpoint (int player_id)
    {
        DEBUG_NATIVE(/*f*/disable_player_checkpoint, /*p*/player_id);
    }
    void set_player_race_checkpoint (int player_id, int type_id, float x, float y, float z, float next_x, float next_y, float next_z, float size)
    {
        DEBUG_NATIVE(/*f*/set_player_race_checkpoint, /*p*/player_id SEPARATOR  type_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  next_x SEPARATOR  next_y SEPARATOR  next_z SEPARATOR  size);
    }
    void disable_player_race_checkpoint (int player_id)
    {
        DEBUG_NATIVE(/*f*/disable_player_race_checkpoint, /*p*/player_id);
    }
    void set_player_world_bounds (int player_id, float x_max, float x_min, float y_max, float y_min)
    {
        DEBUG_NATIVE(/*f*/set_player_world_bounds, /*p*/player_id SEPARATOR  x_max SEPARATOR  x_min SEPARATOR  y_max SEPARATOR  y_min);
    }
    void set_player_marker_for_player (int player_id, int show_player_id, unsigned color)
    {
        DEBUG_NATIVE(/*f*/set_player_marker_for_player, /*p*/player_id SEPARATOR  show_player_id SEPARATOR  color);
    }
    void show_player_name_tag_for_player (int player_id, int show_player_id, bool show)
    {
        DEBUG_NATIVE(/*f*/show_player_name_tag_for_player, /*p*/player_id SEPARATOR  show_player_id SEPARATOR  show);
    }
    void set_player_mapicon (int player_id, int icon_id, float x, float y, float z, int markertype, unsigned color)
    {
        DEBUG_NATIVE(/*f*/set_player_mapicon, /*p*/player_id SEPARATOR  icon_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  markertype SEPARATOR  color);
    }
    void remove_player_mapicon (int player_id, int icon_id)
    {
        DEBUG_NATIVE(/*f*/remove_player_mapicon, /*p*/player_id SEPARATOR  icon_id);
    }
    void allow_player_teleport (int player_id, bool allow)
    {
        DEBUG_NATIVE(/*f*/allow_player_teleport, /*p*/player_id SEPARATOR  allow);
    }

    // Player camera
    void set_player_camera_pos (int player_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_player_camera_pos, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void set_player_camera_look_at (int player_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_player_camera_look_at, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void set_camera_behind_player (int player_id)
    {
        DEBUG_NATIVE(/*f*/set_camera_behind_player, /*p*/player_id);
    }
    void get_player_camera_pos (int player_id, float& x, float& y, float& z)
    {
        DEBUG_NATIVE(/*f*/get_player_camera_pos, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }

    void get_player_camera_front_vector (int player_id, float& x, float& y, float& z)
    {
        DEBUG_NATIVE(/*f*/get_player_camera_front_vector, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }

    // Player conditionals
    bool is_player_connected (int player_id)
    {
        DEBUG_NATIVE(/*f*/is_player_connected, /*p*/player_id);
        return(0);
    }
    bool is_player_in_vehicle (int player_id, int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/is_player_in_vehicle, /*p*/player_id SEPARATOR  vehicle_id);
        return(0);
    }
    bool is_player_in_any_vehicle (int player_id)
    {
        DEBUG_NATIVE(/*f*/is_player_in_any_vehicle, /*p*/player_id);
        return(0);
    }
    bool is_player_in_checkpoint (int player_id)
    {
        DEBUG_NATIVE(/*f*/is_player_in_checkpoint, /*p*/player_id);
        return(0);
    }
    bool is_player_in_race_checkpoint (int player_id)
    {
        DEBUG_NATIVE(/*f*/is_player_in_race_checkpoint, /*p*/player_id);
        return(0);
    }

    // Virtual Worlds
    void set_player_virtual_world (int player_id, int world_id)
    {
        DEBUG_NATIVE(/*f*/set_player_virtual_world, /*p*/player_id SEPARATOR  world_id);
    }
    int get_player_virtual_world (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_virtual_world, /*p*/player_id);
        return(0);
    }

    // Insane Stunts
    void enable_stunt_bonus_for_player (int player_id, bool enable)
    {
        DEBUG_NATIVE(/*f*/enable_stunt_bonus_for_player, /*p*/player_id SEPARATOR  enable);
    }
    void enable_stunt_bonus_for_all (bool enable)
    {
        DEBUG_NATIVE(/*f*/enable_stunt_bonus_for_all, /*p*/enable);
    }

    // Spectating
    void toggle_player_spectating (int player_id, bool toggle)
    {
        DEBUG_NATIVE(/*f*/toggle_player_spectating, /*p*/player_id SEPARATOR  toggle);
    }
    void player_spectate_player (int player_id, int target_player_id, spectate_mode mode)
    {
        DEBUG_NATIVE(/*f*/player_spectate_player, /*p*/player_id SEPARATOR  target_player_id SEPARATOR  mode);
    }
    void player_spectate_vehicle (int player_id, int target_vehicle_id, spectate_mode mode)
    {
        DEBUG_NATIVE(/*f*/player_spectate_vehicle, /*p*/player_id SEPARATOR  target_vehicle_id SEPARATOR  mode);
    }

    // Recording for NPC playback
    void start_recording_player_data (int player_id, player_recording_type record_type, std::string const& record_name)
    {
        DEBUG_NATIVE(/*f*/start_recording_player_data, /*p*/player_id SEPARATOR  record_type SEPARATOR  record_name);
    }
    void stop_recording_player_data (int player_id)
    {
        DEBUG_NATIVE(/*f*/stop_recording_player_data, /*p*/player_id);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_samp.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Util
    void send_client_message (int player_id, unsigned color, std::string const& message)
    {
        DEBUG_NATIVE(/*f*/send_client_message, /*p*/player_id SEPARATOR  color SEPARATOR  message);
    }
    void send_player_message_to_player (int player_id, int sender_id, std::string const& message)
    {
        DEBUG_NATIVE(/*f*/send_player_message_to_player, /*p*/player_id SEPARATOR  sender_id SEPARATOR  message);
    }
    void send_death_message (int killer_id, int killed_id, int weapon_id)
    {
        DEBUG_NATIVE(/*f*/send_death_message, /*p*/killer_id SEPARATOR  killed_id SEPARATOR  weapon_id);
    }
    void game_text_for_player (int player_id, std::string const& string, int time, int style)
    {
        DEBUG_NATIVE(/*f*/game_text_for_player, /*p*/player_id SEPARATOR  string SEPARATOR  time SEPARATOR  style);
    }
    int get_max_players ()
    {
        DEBUG_NATIVE(/*f*/get_max_players, /*p*/"");
        return(0);
    }

    // Game
    void set_game_mode_text (std::string const& text)
    {
        DEBUG_NATIVE(/*f*/set_game_mode_text, /*p*/text);
    }
    void set_team_count (int count)
    {
        DEBUG_NATIVE(/*f*/set_team_count, /*p*/count);
    }
    int add_player_class (int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3)
    {
        DEBUG_NATIVE(/*f*/add_player_class, /*p*/skin_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  weapon_id1 SEPARATOR  weapon_ammo1 SEPARATOR  weapon_id2 SEPARATOR  weapon_ammo2 SEPARATOR  weapon_id3 SEPARATOR  weapon_ammo3);
        return(0);
    }
    int add_player_class_ex (int team_id, int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3)
    {
        DEBUG_NATIVE(/*f*/add_player_class_ex, /*p*/team_id SEPARATOR  skin_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  weapon_id1 SEPARATOR  weapon_ammo1 SEPARATOR  weapon_id2 SEPARATOR  weapon_ammo2 SEPARATOR  weapon_id3 SEPARATOR  weapon_ammo3);
        return(0);
    }
    void add_static_vehicle (int model_id, float x, float y, float z, float rz, int color_id1, int color_id2)
    {
        DEBUG_NATIVE(/*f*/add_static_vehicle, /*p*/model_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  color_id1 SEPARATOR  color_id2);
    }
    int add_static_vehicle_ex (int model_id, float x, float y, float z, float rz, int color_id1, int color_id2, int respawn_delay)
    {
        DEBUG_NATIVE(/*f*/add_static_vehicle_ex, /*p*/model_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  color_id1 SEPARATOR  color_id2 SEPARATOR  respawn_delay);
        return(0);
    }
    void add_static_pickup (int model_id, int type, float x, float y, float z, int virtual_world)
    {
        DEBUG_NATIVE(/*f*/add_static_pickup, /*p*/model_id SEPARATOR  type SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  virtual_world);
    }
    int create_pickup (int model_id, int type, float x, float y, float z, int virtual_world)
    {
        DEBUG_NATIVE(/*f*/create_pickup, /*p*/model_id SEPARATOR  type SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  virtual_world);
        return(0);
    }
    void destroy_pickup (int pickup_id)
    {
        DEBUG_NATIVE(/*f*/destroy_pickup, /*p*/pickup_id);
    }
    void show_name_tags (bool is_show)
    {
        DEBUG_NATIVE(/*f*/show_name_tags, /*p*/is_show);
    }
    void show_player_markers (player_markers_mode mode)
    {
        DEBUG_NATIVE(/*f*/show_player_markers, /*p*/mode);
    }
    void gamemode_exit ()
    {
        DEBUG_NATIVE(/*f*/gamemode_exit, /*p*/"");
    }
    void set_world_time (int hour)
    {
        DEBUG_NATIVE(/*f*/set_world_time, /*p*/hour);
    }
    std::string get_weapon_name (int weapon_id)
    {
        std::string rezult = "";
        DEBUG_NATIVE(/*f*/get_weapon_name, /*p*/weapon_id SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        return rezult;
    }
    void enable_tire_popping (bool is_enable)
    {
        DEBUG_NATIVE(/*f*/enable_tire_popping, /*p*/is_enable);
    }
    void allow_interior_weapons (bool is_allow)
    {
        DEBUG_NATIVE(/*f*/allow_interior_weapons, /*p*/is_allow);
    }
    void set_weather (int weather_id)
    {
        DEBUG_NATIVE(/*f*/set_weather, /*p*/weather_id);
    }
    void set_gravity (float gravity)
    {
        DEBUG_NATIVE(/*f*/set_gravity, /*p*/gravity);
    }
    void allow_admin_teleport (bool is_allow)
    {
        DEBUG_NATIVE(/*f*/allow_admin_teleport, /*p*/is_allow);
    }
    void set_death_drop_amount (int amount)
    {
        DEBUG_NATIVE(/*f*/set_death_drop_amount, /*p*/amount);
    }
    void create_explosion (float x, float y, float z, int type, float radius)
    {
        DEBUG_NATIVE(/*f*/create_explosion, /*p*/x SEPARATOR  y SEPARATOR  z SEPARATOR  type SEPARATOR  radius);
    }
    void enable_zone_names (bool is_enable)
    {
        DEBUG_NATIVE(/*f*/enable_zone_names, /*p*/is_enable);
    }
    void use_player_ped_anims ()
    {
        DEBUG_NATIVE(/*f*/use_player_ped_anims, /*p*/"");
    }
    void disable_interior_enter_exits ()
    {
        DEBUG_NATIVE(/*f*/disable_interior_enter_exits, /*p*/"");
    }
    void set_name_tag_draw_distance (float distance)
    {
        DEBUG_NATIVE(/*f*/set_name_tag_draw_distance, /*p*/distance);
    }
    void disable_name_tag_los ()
    {
        DEBUG_NATIVE(/*f*/disable_name_tag_los, /*p*/"");
    }
    void limit_global_chat_radius (float chat_radius)
    {
        DEBUG_NATIVE(/*f*/limit_global_chat_radius, /*p*/chat_radius);
    }
    void limit_player_marker_radius (float marker_radius)
    {
        DEBUG_NATIVE(/*f*/limit_player_marker_radius, /*p*/marker_radius);
    }

    // Npc
    void connect_npc (std::string const& name, std::string const& script)
    {
        DEBUG_NATIVE(/*f*/connect_npc, /*p*/name SEPARATOR  script);
    }
    bool is_player_npc (int player_id)
    {
        DEBUG_NATIVE(/*f*/is_player_npc, /*p*/player_id);
        return(0);
    }

    // Admin
    bool is_player_admin (int player_id)
    {
        DEBUG_NATIVE(/*f*/is_player_admin, /*p*/player_id);
        return(0);
    }
    void kick (int player_id)
    {
        DEBUG_NATIVE(/*f*/kick, /*p*/player_id);
    }
    void ban (int player_id)
    {
        DEBUG_NATIVE(/*f*/ban, /*p*/player_id);
    }
    void ban_ex (int player_id, std::string const& reason)
    {
        DEBUG_NATIVE(/*f*/ban_ex, /*p*/player_id SEPARATOR  reason);
    }
    void send_rcon_command (std::string const& command)
    {
        DEBUG_NATIVE(/*f*/send_rcon_command, /*p*/command);
    }
    std::string get_server_var_as_string (std::string const& var_name)
    {
        std::string rezult;
        DEBUG_NATIVE(/*f*/get_server_var_as_string, /*p*/var_name SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        return rezult;
    }
    int get_server_var_as_int (std::string const& var_name)
    {
        DEBUG_NATIVE(/*f*/get_server_var_as_int, /*p*/var_name);
        return(0);
    }
    bool get_server_var_as_bool (std::string const& var_name)
    {
        DEBUG_NATIVE(/*f*/get_server_var_as_bool, /*p*/var_name);
        return(0);
    }

    // Menu
    int create_menu (std::string const& title, int columns, float x, float y, float col1width, float col2width)
    {
        DEBUG_NATIVE(/*f*/create_menu, /*p*/title SEPARATOR  columns SEPARATOR  x SEPARATOR  y SEPARATOR  col1width SEPARATOR  col2width);
        return(0);
    }
    void destroy_menu (int menu_id)
    {
        DEBUG_NATIVE(/*f*/destroy_menu, /*p*/menu_id);
    }
    void add_menu_item (int menu_id, int column, std::string const& text)
    {
        DEBUG_NATIVE(/*f*/add_menu_item, /*p*/menu_id SEPARATOR  column SEPARATOR  text);
    }
    void set_menu_column_header (int menu_id, int column, std::string const& header)
    {
        DEBUG_NATIVE(/*f*/set_menu_column_header, /*p*/menu_id SEPARATOR  column SEPARATOR  header);
    }
    void show_menu_for_player (int menu_id, int player_id)
    {
        DEBUG_NATIVE(/*f*/show_menu_for_player, /*p*/menu_id SEPARATOR  player_id);
    }
    void hide_menu_for_player (int menu_id, int player_id)
    {
        DEBUG_NATIVE(/*f*/hide_menu_for_player, /*p*/menu_id SEPARATOR  player_id);
    }
    bool is_valid_menu (int menu_id)
    {
        DEBUG_NATIVE(/*f*/is_valid_menu, /*p*/menu_id);
        return(0);
    }
    void disable_menu (int menu_id)
    {
        DEBUG_NATIVE(/*f*/disable_menu, /*p*/menu_id);
    }
    void disable_menu_row (int menu_id, int row)
    {
        DEBUG_NATIVE(/*f*/disable_menu_row, /*p*/menu_id SEPARATOR  row);
    }
    int get_player_menu (int player_id)
    {
        DEBUG_NATIVE(/*f*/get_player_menu, /*p*/player_id);
        return(0);
    }

    // Text Draw
    int textdraw_create (float x, float y, std::string const& text)
    {
        DEBUG_NATIVE(/*f*/textdraw_create, /*p*/x SEPARATOR  y SEPARATOR  text);
        return(0);
    }
    void textdraw_destroy (int text_id)
    {
        DEBUG_NATIVE(/*f*/textdraw_destroy, /*p*/text_id);
    }
    void textdraw_letter_size (int text_id, float x, float y)
    {
        DEBUG_NATIVE(/*f*/textdraw_letter_size, /*p*/text_id SEPARATOR  x SEPARATOR  y);
    }
    void textdraw_text_size (int text_id, float x, float y)
    {
        DEBUG_NATIVE(/*f*/textdraw_text_size, /*p*/text_id SEPARATOR  x SEPARATOR  y);
    }
    void textdraw_alignment (int text_id, int alignment)
    {
        DEBUG_NATIVE(/*f*/textdraw_alignment, /*p*/text_id SEPARATOR  alignment);
    }
    void textdraw_color (int text_id, unsigned color)
    {
        DEBUG_NATIVE(/*f*/textdraw_color, /*p*/text_id SEPARATOR  color);
    }
    void textdraw_use_box (int text_id, int use)
    {
        DEBUG_NATIVE(/*f*/textdraw_use_box, /*p*/text_id SEPARATOR  use);
    }
    void textdraw_box_color (int text_id, unsigned color)
    {
        DEBUG_NATIVE(/*f*/textdraw_box_color, /*p*/text_id SEPARATOR  color);
    }
    void textdraw_set_shadow (int text_id, int size)
    {
        DEBUG_NATIVE(/*f*/textdraw_set_shadow, /*p*/text_id SEPARATOR  size);
    }
    void textdraw_set_outline (int text_id, int size)
    {
        DEBUG_NATIVE(/*f*/textdraw_set_outline, /*p*/text_id SEPARATOR  size);
    }
    void textdraw_background_color (int text_id, unsigned color)
    {
        DEBUG_NATIVE(/*f*/textdraw_background_color, /*p*/text_id SEPARATOR  color);
    }
    void textdraw_font (int text_id, int font)
    {
        DEBUG_NATIVE(/*f*/textdraw_font, /*p*/text_id SEPARATOR  font);
    }
    void textdraw_set_proportional (int text_id, bool set)
    {
        DEBUG_NATIVE(/*f*/textdraw_set_proportional, /*p*/text_id SEPARATOR  set);
    }
    void textdraw_show_for_player (int player_id, int text_id)
    {
        DEBUG_NATIVE(/*f*/textdraw_show_for_player, /*p*/player_id SEPARATOR  text_id);
    }
    void textdraw_hide_for_player (int player_id, int text_id)
    {
        DEBUG_NATIVE(/*f*/textdraw_hide_for_player, /*p*/player_id SEPARATOR  text_id);
    }
    void textdraw_set_string (int text_id, std::string const& text)
    {
        DEBUG_NATIVE(/*f*/textdraw_set_string, /*p*/text_id SEPARATOR  text);
    }

    // Gang Zones
    int gangzone_create (float minx, float miny, float maxx, float maxy)
    {
        DEBUG_NATIVE(/*f*/gangzone_create, /*p*/minx SEPARATOR  miny SEPARATOR  maxx SEPARATOR  maxy);
        return(0);
    }
    void gangzone_destroy (int zone_id)
    {
        DEBUG_NATIVE(/*f*/gangzone_destroy, /*p*/zone_id);
    }
    void gangzone_show_for_player (int player_id, int zone_id, unsigned int color)
    {
        DEBUG_NATIVE(/*f*/gangzone_show_for_player, /*p*/player_id SEPARATOR  zone_id SEPARATOR  color);
    }
    void gangzone_hide_for_player (int player_id, int zone_id)
    {
        DEBUG_NATIVE(/*f*/gangzone_hide_for_player, /*p*/player_id SEPARATOR  zone_id);
    }
    void gangzone_flash_for_player (int player_id, int zone_id, unsigned int flashcolor)
    {
        DEBUG_NATIVE(/*f*/gangzone_flash_for_player, /*p*/player_id SEPARATOR  zone_id SEPARATOR  flashcolor);
    }
    void gangzone_stop_flash_for_player (int player_id, int zone_id)
    {
        DEBUG_NATIVE(/*f*/gangzone_stop_flash_for_player, /*p*/player_id SEPARATOR  zone_id);
    }

    // Global 3D Text Labels
    int create_3dtextlabel (std::string const& text, unsigned int color, float x, float y, float z, float draw_distance, int world, bool is_test_los)
    {
        DEBUG_NATIVE(/*f*/create_3dtextlabel, /*p*/text SEPARATOR  color SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  draw_distance SEPARATOR  world SEPARATOR  is_test_los);
        return(0);
    }
    void delete_3dtextlabel (int text3d_id)
    {
        DEBUG_NATIVE(/*f*/delete_3dtextlabel, /*p*/text3d_id);
    }
    void attach_3dtextlabel_to_player (int text3d_id, int player_id, float offset_x, float offset_y, float offset_z)
    {
        DEBUG_NATIVE(/*f*/attach_3dtextlabel_to_player, /*p*/text3d_id SEPARATOR  player_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z);
    }
    void attach_3dtextlabel_to_vehicle (int text3d_id, int vehicle_id, float offset_x, float offset_y, float offset_z)
    {
        DEBUG_NATIVE(/*f*/attach_3dtextlabel_to_vehicle, /*p*/text3d_id SEPARATOR  vehicle_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z);
    }
    void update_3dtextlabel_text (int text3d_id, unsigned int color, std::string const& text)
    {
        DEBUG_NATIVE(/*f*/update_3dtextlabel_text, /*p*/text3d_id SEPARATOR  color SEPARATOR  text);
    }

    // Per-player 3D Text Labels
    int create_player3dtextlabel (int player_id, std::string const& text, unsigned int color, float x, float y, float z, float draw_distance, int attached_player_id, int attached_vehicle_id, bool is_test_los)
    {
        DEBUG_NATIVE(/*f*/create_player3dtextlabel, /*p*/player_id SEPARATOR  text SEPARATOR  color SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  draw_distance SEPARATOR  attached_player_id SEPARATOR  attached_vehicle_id SEPARATOR  is_test_los);
        return(0);
    }
    void delete_player3dtextlabel (int player_id, int playertext3d_id)
    {
        DEBUG_NATIVE(/*f*/delete_player3dtextlabel, /*p*/player_id SEPARATOR  playertext3d_id);
    }
    void update_player3dtextlabel_text (int player_id, int playertext3d_id, unsigned int color, std::string const& text)
    {
        DEBUG_NATIVE(/*f*/update_player3dtextlabel_text, /*p*/player_id SEPARATOR  playertext3d_id SEPARATOR  color SEPARATOR  text);
    }

    // Player GUI Dialog
    void show_player_dialog (int player_id, int dialog_id, dialog_style style, std::string const& caption, std::string const& info, std::string const& button_ok, std::string const& button_cancel)
    {
        DEBUG_NATIVE(/*f*/show_player_dialog, /*p*/player_id SEPARATOR  dialog_id SEPARATOR  style SEPARATOR  caption SEPARATOR  info SEPARATOR  button_ok SEPARATOR  button_cancel);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_vehicles.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Vehicle
    int create_vehicle (int vehicle_model, float x, float y, float z, float rz, int color_id1, int color_id2, int respawn_delay)
    {
        DEBUG_NATIVE(/*f*/create_vehicle, /*p*/vehicle_model SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  color_id1 SEPARATOR  color_id2 SEPARATOR  respawn_delay);
        return(0);
    }
    void destroy_vehicle (int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/destroy_vehicle, /*p*/vehicle_id);
    }
    bool is_vehicle_streamed_in (int vehicle_id, int for_player_id)
    {
        DEBUG_NATIVE(/*f*/is_vehicle_streamed_in, /*p*/vehicle_id SEPARATOR  for_player_id);
        return(0);
    }
    void get_vehicle_pos (int vehicle_id, float& x, float& y, float& z)
    {
        DEBUG_NATIVE(/*f*/get_vehicle_pos, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void set_vehicle_pos (int vehicle_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_vehicle_pos, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    float get_vehicle_zangle (int vehicle_id)
    {
        float rz;
        DEBUG_NATIVE(/*f*/get_vehicle_zangle, /*p*/vehicle_id SEPARATOR  rz);
        return rz;
    }
    void get_vehicle_rotation_quat (int vehicle_id, float& w, float& x, float& y, float& z)
    {
        DEBUG_NATIVE(/*f*/get_vehicle_rotation_quat, /*p*/vehicle_id SEPARATOR  w SEPARATOR  x SEPARATOR  y SEPARATOR  x);
    }
    void set_vehicle_zangle (int vehicle_id, float rz)
    {
        DEBUG_NATIVE(/*f*/set_vehicle_zangle, /*p*/vehicle_id SEPARATOR  rz);
    }
    void set_vehicle_params_for_player (int vehicle_id, int player_id, bool objective, bool doorslocked)
    {
        DEBUG_NATIVE(/*f*/set_vehicle_params_for_player, /*p*/vehicle_id SEPARATOR  player_id SEPARATOR  objective SEPARATOR  doorslocked);
    }
    void set_vehicle_to_respawn (int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/set_vehicle_to_respawn, /*p*/vehicle_id);
    }
    void link_vehicle_to_interior (int vehicle_id, int interior_id)
    {
        DEBUG_NATIVE(/*f*/link_vehicle_to_interior, /*p*/vehicle_id SEPARATOR  interior_id);
    }
    void add_vehicle_component (int vehicle_id, int component_id)
    {
        DEBUG_NATIVE(/*f*/add_vehicle_component, /*p*/vehicle_id SEPARATOR  component_id);
    }
    void remove_vehicle_component (int vehicle_id, int component_id)
    {
        DEBUG_NATIVE(/*f*/remove_vehicle_component, /*p*/vehicle_id SEPARATOR  component_id);
    }
    void change_vehicle_color (int vehicle_id, int color_id1, int color_id2)
    {
        DEBUG_NATIVE(/*f*/change_vehicle_color, /*p*/vehicle_id SEPARATOR  color_id1 SEPARATOR  color_id2);
    }
    void change_vehicle_paintjob (int vehicle_id, int paintjob_id)
    {
        DEBUG_NATIVE(/*f*/change_vehicle_paintjob, /*p*/vehicle_id SEPARATOR  paintjob_id);
    }
    void set_vehicle_health (int vehicle_id, float health)
    {
        DEBUG_NATIVE(/*f*/set_vehicle_health, /*p*/vehicle_id SEPARATOR  health);
    }
    float get_vehicle_health (int vehicle_id)
    {
        float health;
        DEBUG_NATIVE(/*f*/get_vehicle_health, /*p*/vehicle_id SEPARATOR  health);
        return health;
    }
    void attach_trailer_to_vehicle (int trailer_id, int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/attach_trailer_to_vehicle, /*p*/trailer_id SEPARATOR  vehicle_id);
    }
    void detach_trailer_from_vehicle (int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/detach_trailer_from_vehicle, /*p*/vehicle_id);
    }
    bool is_trailer_attached_to_vehicle (int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/is_trailer_attached_to_vehicle, /*p*/vehicle_id);
        return(0);
    }
    int get_vehicle_trailer (int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/get_vehicle_trailer, /*p*/vehicle_id);
        return(0);
    }
    void set_vehicle_number_plate (int vehicle_id, std::string const& numberplate)
    {
        DEBUG_NATIVE(/*f*/set_vehicle_number_plate, /*p*/vehicle_id SEPARATOR  numberplate);
    }
    int get_vehicle_model (int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/get_vehicle_model, /*p*/vehicle_id);
        return(0);
    }
    int get_vehicle_component_in_slot (int vehicle_id, carmod_type slot)
    {
        DEBUG_NATIVE(/*f*/get_vehicle_component_in_slot, /*p*/vehicle_id SEPARATOR  slot);
        return(0);
    }
    carmod_type get_vehicle_component_type (int component_id)
    {
        DEBUG_NATIVE(/*f*/get_vehicle_component_type, /*p*/component_id);
        return carmod_type(0);
    }
    void repair_vehicle (int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/repair_vehicle, /*p*/vehicle_id);
    }
    void get_vehicle_velocity (int vehicle_id, float& x, float& y, float& z)
    {
        DEBUG_NATIVE(/*f*/get_vehicle_velocity, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void set_vehicle_velocity (int vehicle_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_vehicle_velocity, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void set_vehicle_angular_velocity (int vehicle_id, float x, float y, float z)
    {
        DEBUG_NATIVE(/*f*/set_vehicle_angular_velocity, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
    }
    void get_vehicle_damage_status (int vehicle_id, int& panels, int& doors, int& lights, int& tires)
    {
        DEBUG_NATIVE(/*f*/get_vehicle_damage_status, /*p*/vehicle_id SEPARATOR  panels SEPARATOR  doors SEPARATOR  lights SEPARATOR  tires);
    }
    void update_vehicle_damage_status (int vehicle_id, int panels, int doors, int lights, int tires)
    {
        DEBUG_NATIVE(/*f*/update_vehicle_damage_status, /*p*/vehicle_id SEPARATOR  panels SEPARATOR  doors SEPARATOR  lights SEPARATOR  tires);
    }

    // Virtual Worlds
    void set_vehicle_virtual_world (int vehicle_id, int world_id)
    {
        DEBUG_NATIVE(/*f*/set_vehicle_virtual_world, /*p*/vehicle_id SEPARATOR  world_id);
    }
    int get_vehicle_virtual_world (int vehicle_id)
    {
        DEBUG_NATIVE(/*f*/get_vehicle_virtual_world, /*p*/vehicle_id);
        return(0);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Недокументированные возможности
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string get_serial (int player_id)
    {
        std::string rezult = "";
        DEBUG_NATIVE(/*f*/get_serial, /*p*/player_id SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        return rezult;
    }

}

