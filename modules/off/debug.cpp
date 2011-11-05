#include "box.hpp"
//#include "wrapper/callbacks.h"
#include <iostream>

using std::cout;
using std::endl;

static bool on_game_mode_init() { cout << "on_game_mode_init" << endl; return true; }
static bool on_game_mode_exit() { cout << "on_game_mode_exit" << endl; return true; }
static bool on_filter_script_init() { cout << "on_filter_script_init" << endl; return true; }
static bool on_filter_script_exit() { cout << "on_filter_script_exit" << endl; return true; }
static bool on_player_connect(int) { cout << "on_player_connect" << endl; return true; }
static bool on_player_disconnect(int, int) { cout << "on_player_disconnect" << endl; return true; }
static bool on_player_spawn(int) { cout << "on_player_spawn" << endl; return true; }
static bool on_player_death(int, int, int) { cout << "on_player_death" << endl; return true; }
static bool on_vehicle_spawn(int) { cout << "on_vehicle_spawn" << endl; return true; }
static bool on_vehicle_death(int, int) { cout << "on_vehicle_death" << endl; return true; }
static bool on_player_text(int, const std::string&) { cout << "on_player_text" << endl; return true; }
static bool on_player_command_text(int, const std::string&) { cout << "on_player_command_text" << endl; return true; }
static bool on_player_request_class(int, int) { cout << "on_player_request_class" << endl; return true; }
static bool on_player_enter_vehicle(int, int, int) { cout << "on_player_enter_vehicle" << endl; return true; }
static bool on_player_exit_vehicle(int, int) { cout << "on_player_exit_vehicle" << endl; return true; }
static bool on_player_state_change(int, int, int) { cout << "on_player_state_change" << endl; return true; }
static bool on_player_enter_checkpoint(int) { cout << "on_player_enter_checkpoint" << endl; return true; }
static bool on_player_leave_checkpoint(int) { cout << "on_player_leave_checkpoint" << endl; return true; }
static bool on_player_enter_race_checkpoint(int) { cout << "on_player_enter_race_checkpoint" << endl; return true; }
static bool on_player_leave_race_checkpoint(int) { cout << "on_player_leave_race_checkpoint" << endl; return true; }
static bool on_rcon_command(const std::string&) { cout << "on_rcon_command" << endl; return true; }
static bool on_player_request_spawn(int) { cout << "on_player_request_spawn" << endl; return true; }
static bool on_object_moved(int) { cout << "on_object_moved" << endl; return true; }
static bool on_player_object_moved(int, int) { cout << "on_player_object_moved" << endl; return true; }
static bool on_player_pick_up_pickup(int, int) { cout << "on_player_pick_up_pickup" << endl; return true; }
static bool on_vehicle_mod(int, int, int) { cout << "on_vehicle_mod" << endl; return true; }
static bool on_enter_exit_mod_shop(int, int, int) { cout << "on_enter_exit_mod_shop" << endl; return true; }
static bool on_vehicle_paintjob(int, int, int) { cout << "on_vehicle_paintjob" << endl; return true; }
static bool on_vehicle_respray(int, int, int, int) { cout << "on_vehicle_respray" << endl; return true; }
static bool on_vehicle_damage_status_update(int, int) { cout << "on_vehicle_damage_status_update" << endl; return true; }
static bool on_player_selected_menu_row(int, int) { cout << "on_player_selected_menu_row" << endl; return true; }
static bool on_player_exited_menu(int) { cout << "on_player_exited_menu" << endl; return true; }
static bool on_player_interior_change(int, int, int) { cout << "on_player_interior_change" << endl; return true; }
static bool on_player_key_state_change(int, int, int) { cout << "on_player_key_state_change" << endl; return true; }
static bool on_rcon_login_attempt( const std::string&, const std::string&, int) { cout << "on_rcon_login_attempt" << endl; return true; }
static bool on_player_update(int) { cout << "on_player_update" << endl; return true; }
static bool on_player_stream_in(int, int) { cout << "on_player_stream_in" << endl; return true; }
static bool on_player_stream_out(int, int) { cout << "on_player_stream_out" << endl; return true; }
static bool on_vehicle_stream_in(int, int) { cout << "on_vehicle_stream_in" << endl; return true; }
static bool on_vehicle_stream_out(int, int) { cout << "on_vehicle_stream_out" << endl; return true; }
static bool on_dialog_response(int, int, int, int, const std::string&) { cout << "on_dialog_response" << endl; return true; }
static bool on_player_click_player(int, int, int) { cout << "on_player_click_player" << endl; return true; }

//^SIG<([^ ]+) \(([^)]*)\)[^>]*> ([^;]+);$
//\1 \3(\2) { cout << "\3" << endl; return true; }

INIT
{
  REGISTER_CB(on_game_mode_init);
  REGISTER_CB(on_game_mode_exit);
  REGISTER_CB(on_filter_script_init);
  REGISTER_CB(on_filter_script_exit);
  REGISTER_CB(on_player_connect);
  REGISTER_CB(on_player_disconnect);
  REGISTER_CB(on_player_spawn);
  REGISTER_CB(on_player_death);
  REGISTER_CB(on_vehicle_spawn);
  REGISTER_CB(on_vehicle_death);
  REGISTER_CB(on_player_text);
  REGISTER_CB(on_player_command_text);
  REGISTER_CB(on_player_request_class);
  REGISTER_CB(on_player_enter_vehicle);
  REGISTER_CB(on_player_exit_vehicle);
  REGISTER_CB(on_player_state_change);
  REGISTER_CB(on_player_enter_checkpoint);
  REGISTER_CB(on_player_leave_checkpoint);
  REGISTER_CB(on_player_enter_race_checkpoint);
  REGISTER_CB(on_player_leave_race_checkpoint);
  REGISTER_CB(on_rcon_command);
  REGISTER_CB(on_player_request_spawn);
  REGISTER_CB(on_object_moved);
  REGISTER_CB(on_player_object_moved);
  REGISTER_CB(on_player_pick_up_pickup);
  REGISTER_CB(on_vehicle_mod);
  REGISTER_CB(on_enter_exit_mod_shop);
  REGISTER_CB(on_vehicle_paintjob);
  REGISTER_CB(on_vehicle_respray);
  REGISTER_CB(on_vehicle_damage_status_update);
  REGISTER_CB(on_player_selected_menu_row);
  REGISTER_CB(on_player_exited_menu);
  REGISTER_CB(on_player_interior_change);
  REGISTER_CB(on_player_key_state_change);
  REGISTER_CB(on_rcon_login_attempt);
  REGISTER_CB(on_player_update);
  REGISTER_CB(on_player_stream_in);
  REGISTER_CB(on_player_stream_out);
  REGISTER_CB(on_vehicle_stream_in);
  REGISTER_CB(on_vehicle_stream_out);
  REGISTER_CB(on_dialog_response);
  REGISTER_CB(on_player_click_player);
  
  //^SIG<[^>]*> ([^;]+);$
  //REGISTER_CB(\1);
}



