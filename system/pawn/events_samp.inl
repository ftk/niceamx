

SIG() on_game_mode_init;
SIG() on_game_mode_exit;
SIG() on_filter_script_init;
SIG() on_filter_script_exit;
SIG(int) on_player_connect;
SIG(int, int) on_player_disconnect;
SIG(int) on_player_spawn;
SIG(int, int, int) on_player_death;
SIG(int) on_vehicle_spawn;
SIG(int, int) on_vehicle_death;
SIG(int, std::string&) on_player_text;
SIG(int, const std::string&) on_player_command_text;
SIG(int, int) on_player_request_class;
SIG(int, int, int) on_player_enter_vehicle;
SIG(int, int) on_player_exit_vehicle;
SIG(int, int, int) on_player_state_change;
SIG(int) on_player_enter_checkpoint;
SIG(int) on_player_leave_checkpoint;
SIG(int) on_player_enter_race_checkpoint;
SIG(int) on_player_leave_race_checkpoint;
SIG(const std::string&) on_rcon_command;
SIG(int) on_player_request_spawn;
SIG(int) on_object_moved;
SIG(int, int) on_player_object_moved;
SIG(int, int) on_player_pick_up_pickup;
SIG(int, int, int) on_vehicle_mod;
SIG(int, int, int) on_enter_exit_mod_shop;
SIG(int, int, int) on_vehicle_paintjob;
SIG(int, int, int, int) on_vehicle_respray;
SIG(int, int) on_vehicle_damage_status_update;
SIG(int, int) on_player_selected_menu_row;
SIG(int) on_player_exited_menu;
SIG(int, int, int) on_player_interior_change;
SIG(int, int, int) on_player_key_state_change;
SIG( const std::string&, const std::string&, int) on_rcon_login_attempt;
SIG(int) on_player_update;
SIG(int, int) on_player_stream_in;
SIG(int, int) on_player_stream_out;
SIG(int, int) on_vehicle_stream_in;
SIG(int, int) on_vehicle_stream_out;
SIG(int, int, int, int, const std::string&) on_dialog_response;
SIG(int, int, int) on_player_click_player;


//\([A-Z]\)\([a-z]+\)
//_\1\2

// ^Ctrl-A ^Ctrl-U

//$
//;

//^sig ([a-z_0-9]+)(<[^>]+>);
//SIG\2 \1;

#define CALLBACKS_SAMP_INCLUDED

