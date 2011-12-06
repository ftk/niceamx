bool on_game_mode_init/*p*/()
{
	return MAINBOX->on_game_mode_init/*c*/();
}

bool on_game_mode_exit/*p*/()
{
	return MAINBOX->on_game_mode_exit/*c*/();
}

bool on_filter_script_init/*p*/()
{
	return MAINBOX->on_filter_script_init/*c*/();
}

bool on_filter_script_exit/*p*/()
{
	return MAINBOX->on_filter_script_exit/*c*/();
}

bool on_player_connect(int playerid)
{
	return MAINBOX->on_player_connect/*c*/(playerid);
}

bool on_player_disconnect(int playerid, int reason)
{
	return MAINBOX->on_player_disconnect/*c*/(playerid, reason);
}

bool on_player_spawn(int playerid)
{
	return MAINBOX->on_player_spawn/*c*/(playerid);
}

bool on_player_death(int playerid, int killerid, int reason)
{
	return MAINBOX->on_player_death/*c*/(playerid, killerid, reason);
}

bool on_vehicle_spawn(int vehicleid)
{
	return MAINBOX->on_vehicle_spawn/*c*/(vehicleid);
}

bool on_vehicle_death(int vehicleid, int killerid)
{
	return MAINBOX->on_vehicle_death/*c*/(vehicleid, killerid);
}

bool on_player_text(int playerid, const std::string& text)
{
	return MAINBOX->on_player_text/*c*/(playerid, text);
}

bool on_player_command_text(int playerid, const std::string& cmdtext)
{
	return MAINBOX->on_player_command_text/*c*/(playerid, cmdtext);
}

bool on_player_request_class(int playerid, int classid)
{
	return MAINBOX->on_player_request_class/*c*/(playerid, classid);
}

bool on_player_enter_vehicle(int playerid, int vehicleid, int ispassenger)
{
	return MAINBOX->on_player_enter_vehicle/*c*/(playerid, vehicleid, ispassenger);
}

bool on_player_exit_vehicle(int playerid, int vehicleid)
{
	return MAINBOX->on_player_exit_vehicle/*c*/(playerid, vehicleid);
}

bool on_player_state_change(int playerid, int newstate, int oldstate)
{
	return MAINBOX->on_player_state_change/*c*/(playerid, newstate, oldstate);
}

bool on_player_enter_checkpoint(int playerid)
{
	return MAINBOX->on_player_enter_checkpoint/*c*/(playerid);
}

bool on_player_leave_checkpoint(int playerid)
{
	return MAINBOX->on_player_leave_checkpoint/*c*/(playerid);
}

bool on_player_enter_race_checkpoint(int playerid)
{
	return MAINBOX->on_player_enter_race_checkpoint/*c*/(playerid);
}

bool on_player_leave_race_checkpoint(int playerid)
{
	return MAINBOX->on_player_leave_race_checkpoint/*c*/(playerid);
}

bool on_rcon_command(const std::string& cmd)
{
	return MAINBOX->on_rcon_command/*c*/(cmd);
}

bool on_player_request_spawn(int playerid)
{
	return MAINBOX->on_player_request_spawn/*c*/(playerid);
}

bool on_object_moved(int objectid)
{
	return MAINBOX->on_object_moved/*c*/(objectid);
}

bool on_player_object_moved(int playerid, int objectid)
{
	return MAINBOX->on_player_object_moved/*c*/(playerid, objectid);
}

bool on_player_pick_up_pickup(int playerid, int pickupid)
{
	return MAINBOX->on_player_pick_up_pickup/*c*/(playerid, pickupid);
}

bool on_vehicle_mod(int playerid, int vehicleid, int componentid)
{
	return MAINBOX->on_vehicle_mod/*c*/(playerid, vehicleid, componentid);
}

bool on_enter_exit_mod_shop(int playerid, int enterexit, int interiorid)
{
	return MAINBOX->on_enter_exit_mod_shop/*c*/(playerid, enterexit, interiorid);
}

bool on_vehicle_paintjob(int playerid, int vehicleid, int paintjobid)
{
	return MAINBOX->on_vehicle_paintjob/*c*/(playerid, vehicleid, paintjobid);
}

bool on_vehicle_respray(int playerid, int vehicleid, int color1, int color2)
{
	return MAINBOX->on_vehicle_respray/*c*/(playerid, vehicleid, color1, color2);
}

bool on_vehicle_damage_status_update(int vehicleid, int playerid)
{
	return MAINBOX->on_vehicle_damage_status_update/*c*/(vehicleid, playerid);
}

bool on_player_selected_menu_row(int playerid, int row)
{
	return MAINBOX->on_player_selected_menu_row/*c*/(playerid, row);
}

bool on_player_exited_menu(int playerid)
{
	return MAINBOX->on_player_exited_menu/*c*/(playerid);
}

bool on_player_interior_change(int playerid, int newinteriorid, int oldinteriorid)
{
	return MAINBOX->on_player_interior_change/*c*/(playerid, newinteriorid, oldinteriorid);
}

bool on_player_key_state_change(int playerid, int newkeys, int oldkeys)
{
	return MAINBOX->on_player_key_state_change/*c*/(playerid, newkeys, oldkeys);
}

bool on_rcon_login_attempt(const std::string& ip, const std::string& password, int success)
{
	return MAINBOX->on_rcon_login_attempt/*c*/( ip, password, success );
}

bool on_player_update(int playerid)
{
	return MAINBOX->on_player_update/*c*/(playerid);
}

bool on_player_stream_in(int playerid, int forplayerid)
{
	return MAINBOX->on_player_stream_in/*c*/(playerid, forplayerid);
}

bool on_player_stream_out(int playerid, int forplayerid)
{
	return MAINBOX->on_player_stream_out/*c*/(playerid, forplayerid);
}

bool on_vehicle_stream_in(int vehicleid, int forplayerid)
{
	return MAINBOX->on_vehicle_stream_in/*c*/(vehicleid, forplayerid);
}

bool on_vehicle_stream_out(int vehicleid, int forplayerid)
{
	return MAINBOX->on_vehicle_stream_out/*c*/(vehicleid, forplayerid);
}

bool on_dialog_response(int playerid, int dialogid, int response, int listitem, const std::string& inputtext)
{
	return MAINBOX->on_dialog_response/*c*/(playerid, dialogid, response, listitem, inputtext);
}

bool on_player_click_player(int playerid, int clickedplayerid, int source)
{
	return MAINBOX->on_player_click_player/*c*/(playerid, clickedplayerid, source);
}

// REGEX
// from:
//forward \([a-_za-z]*\)\([()a-z, 0-9\[\]]*\);
// to:
//bool \1/*p*/\2\n{\n\treturn mainbox->\1/*c*/\2;\n}\n

///\*p\*/[(]\([a-z0-9\[\]]+\)[)]
//(int \1)

///\*p\*/[(]\([a-z0-9\[\]]+\), \([a-z0-9\[\]]+\)[)]
//(int \1, int \2)

///\*p\*/[(][ ]*\([a-z0-9\[\]]+\), \([a-z0-9\[\]]+\), \([a-z0-9\[\]]+\)[ ]*[)]
//(int \1, int \2, int \3)
// ...

//int \([a-z0-9]+\)\[\]
//const std::string& \1

//\[\]
//

//\([A-Z]\)\([a-z]+\)
//_\1\2

// ^Ctrl-A ^Ctrl-U

// _
//

//MAINBOX->
//MAINBOX->
