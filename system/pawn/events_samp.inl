
#ifndef SIGNAL
#error SIGNAL(name,args...) is not defined
#endif
//#define SIGNAL(name,...) signals::signal<__VA_ARGS__> name;


SIGNAL(on_game_mode_init,)
SIGNAL(on_game_mode_exit,)
SIGNAL(on_filter_script_init,)
SIGNAL(on_filter_script_exit,)
SIGNAL(on_player_connect, int)
SIGNAL(on_player_disconnect, int, int)
SIGNAL(on_player_spawn, int)
SIGNAL(on_player_death, int, int, int)
SIGNAL(on_vehicle_spawn, int)
SIGNAL(on_vehicle_death, int, int)
SIGNAL(on_player_text, int, std::string&)
SIGNAL(on_player_command_text, int, const std::string&)
SIGNAL(on_player_request_class, int, int)
SIGNAL(on_player_enter_vehicle, int, int, int)
SIGNAL(on_player_exit_vehicle, int, int)
SIGNAL(on_player_state_change, int, int, int)
SIGNAL(on_player_enter_checkpoint, int)
SIGNAL(on_player_leave_checkpoint, int)
SIGNAL(on_player_enter_race_checkpoint, int)
SIGNAL(on_player_leave_race_checkpoint, int)
SIGNAL(on_rcon_command, const std::string&)
SIGNAL(on_player_request_spawn, int)
SIGNAL(on_object_moved, int)
SIGNAL(on_player_object_moved, int, int)
SIGNAL(on_player_pick_up_pickup, int, int)
SIGNAL(on_vehicle_mod, int, int, int)
SIGNAL(on_enter_exit_mod_shop, int, int, int)
SIGNAL(on_vehicle_paintjob, int, int, int)
SIGNAL(on_vehicle_respray, int, int, int, int)
SIGNAL(on_vehicle_damage_status_update, int, int)
SIGNAL(on_player_selected_menu_row, int, int)
SIGNAL(on_player_exited_menu, int)
SIGNAL(on_player_interior_change, int, int, int)
SIGNAL(on_player_key_state_change, int, int, int)
SIGNAL(on_rcon_login_attempt,  const std::string&, const std::string&, int)
SIGNAL(on_player_update, int)
SIGNAL(on_player_stream_in, int, int)
SIGNAL(on_player_stream_out, int, int)
SIGNAL(on_vehicle_stream_in, int, int)
SIGNAL(on_vehicle_stream_out, int, int)
SIGNAL(on_dialog_response, int, int, int, int, const std::string&)
SIGNAL(on_player_click_player, int, int, int)

// 0.3e
SIGNAL(on_unoccupied_vehicle_update, int, int, int)
SIGNAL(on_player_take_damage, int, int, float, int)
SIGNAL(on_player_give_damage, int, int, float, int)

SIGNAL(on_player_click_map, int, float, float, float)
// TODO:
//SIGNAL(on_player_take_damage, int, int, float, int)
//SIGNAL(on_player_take_damage, int, int, float, int)


