
#ifndef EVENT
#error EVENT(sampname,signal) is not defined
#endif


//EVENT(GameModeInit, on_game_mode_init)
//EVENT(GameModeExit, on_game_mode_exit)
EVENT(FilterScriptInit, on_filter_script_init)
EVENT(FilterScriptExit, on_filter_script_exit)
EVENT(PlayerConnect, on_player_connect)
EVENT(PlayerDisconnect, on_player_disconnect)
EVENT(PlayerSpawn, on_player_spawn)
EVENT(PlayerDeath, on_player_death)
EVENT(VehicleSpawn, on_vehicle_spawn)
EVENT(VehicleDeath, on_vehicle_death)
EVENT(PlayerText, on_player_text)
EVENT(PlayerCommandText, on_player_command_text)
EVENT(PlayerRequestClass, on_player_request_class)
EVENT(PlayerEnterVehicle, on_player_enter_vehicle)
EVENT(PlayerExitVehicle, on_player_exit_vehicle)
EVENT(PlayerStateChange, on_player_state_change)
EVENT(PlayerEnterCheckpoint, on_player_enter_checkpoint)
EVENT(PlayerLeaveCheckpoint, on_player_leave_checkpoint)
EVENT(PlayerEnterRaceCheckpoint, on_player_enter_race_checkpoint)
EVENT(PlayerLeaveRaceCheckpoint, on_player_leave_race_checkpoint)
EVENT(RconCommand, on_rcon_command)
EVENT(PlayerRequestSpawn, on_player_request_spawn)
EVENT(ObjectMoved, on_object_moved)
EVENT(PlayerObjectMoved, on_player_object_moved)
EVENT(PlayerPickUpPickup, on_player_pick_up_pickup)
EVENT(VehicleMod, on_vehicle_mod)
EVENT(EnterExitModShop, on_enter_exit_mod_shop)
EVENT(VehiclePaintjob, on_vehicle_paintjob)
EVENT(VehicleRespray, on_vehicle_respray)
EVENT(VehicleDamageStatusUpdate, on_vehicle_damage_status_update)
EVENT(PlayerSelectedMenuRow, on_player_selected_menu_row)
EVENT(PlayerExitedMenu, on_player_exited_menu)
EVENT(PlayerInteriorChange, on_player_interior_change)
EVENT(PlayerKeyStateChange, on_player_key_state_change)
EVENT(RconLoginAttempt, on_rcon_login_attempt)
EVENT(PlayerUpdate, on_player_update)
EVENT(PlayerStreamIn, on_player_stream_in)
EVENT(PlayerStreamOut, on_player_stream_out)
EVENT(VehicleStreamIn, on_vehicle_stream_in)
EVENT(VehicleStreamOut, on_vehicle_stream_out)
EVENT(DialogResponse, on_dialog_response)
EVENT(PlayerClickPlayer, on_player_click_player)

// 0.3e
EVENT(UnoccupiedVehicleUpdate, on_unoccupied_vehicle_update)
EVENT(PlayerTakeDamage, on_player_take_damage)
EVENT(PlayerGiveDamage, on_player_give_damage)

EVENT(PlayerClickMap, on_player_click_map)



