#include "config.h"
#include "signals.hpp"
#include "SDK/amx/amx.h"
#include "pawn_demarshaling.hpp"
#include <string>

#include "util/overtimer.hpp"

#define PREFIX /* empty */
#define NATIVE_DECL(fn) PREFIX static cell AMX_NATIVE_CALL fn (AMX * amx, cell params[])

#ifndef MAX_CB_EXEC_TIME
#ifdef MAX_EXEC_TIME
#define MAX_CB_EXEC_TIME MAX_EXEC_TIME
#else
#define MAX_CB_EXEC_TIME 3
#endif // MAX_EXEC_TIME
#endif //MAX_CB_EXEC_TIME

#define START() MAKE_OVERTIMER(MAX_CB_EXEC_TIME)

#define CALL(sig,...) /*return (cell)*/ MAINBOX->sig(__VA_ARGS__); return 1
#define CALL_R(sig,...) MAINBOX->sig(__VA_ARGS__)



#ifdef PRINT_INCOMING_CALLBACKS
#include <boost/preprocessor/stringize.hpp>
#include <iostream>
#define DEBUG_CALLBACK(f,p) std::cout << BOOST_PP_STRINGIZE(f) "(" << p << ");" << std::endl
#else
#define DEBUG_CALLBACK(f,...) /* empty */
#endif

#define SEPARATOR << ", " <<

namespace native // natives.cpp
{
  void natives_init(AMX *);
}

namespace pawn
{

        //OnGameModeExit();
        NATIVE_DECL(OnGameModeInit)
        {
                native::natives_init(amx);
                START();
                
                DEBUG_CALLBACK(/*f*/ on_game_mode_init, /*p*/ "");
                CALL(/*f*/ on_game_mode_init /*p*/ , );
        }

        NATIVE_DECL(OnGameModeExit)
        {
                START();
                
                DEBUG_CALLBACK(/*f*/ on_game_mode_exit, /*p*/ "");
                CALL(/*f*/ on_game_mode_exit /*p*/ , );
        }


        //OnPlayerConnect(playerid);
        NATIVE_DECL(OnPlayerConnect)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_connect, /*p*/ player_id.get());
                CALL(/*f*/ on_player_connect /*p*/ , player_id.get()); 
        }


        //OnPlayerDisconnect(playerid, reason);
        NATIVE_DECL(OnPlayerDisconnect)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> reason_int(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_disconnect, /*p*/ player_id.get() SEPARATOR  reason_int.get());
                CALL(/*f*/ on_player_disconnect /*p*/ , player_id.get(), reason_int.get());
        }


        //OnPlayerSpawn(playerid);
        NATIVE_DECL(OnPlayerSpawn)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_spawn, /*p*/ player_id.get());
                CALL(/*f*/ on_player_spawn /*p*/ , player_id.get()); 
        }


        //OnPlayerDeath(playerid, killerid, reason);
        NATIVE_DECL(OnPlayerDeath)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> killer_id(amx, params);
                pawn::demarh_t<2, int> reason(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_death, /*p*/ player_id.get() SEPARATOR  killer_id.get() SEPARATOR  reason.get());
                CALL(/*f*/ on_player_death /*p*/ , player_id.get(), killer_id.get(), reason.get()); 
        }


        //OnVehicleSpawn(vehicleid);
        NATIVE_DECL(OnVehicleSpawn)
        {
                START();
                
                pawn::demarh_t<0, int> vehicle_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_vehicle_spawn, /*p*/ vehicle_id.get());
                CALL(/*f*/ on_vehicle_spawn /*p*/ , vehicle_id.get()); 
        }


        //OnVehicleDeath(vehicleid, killerid);
        NATIVE_DECL(OnVehicleDeath)
        {
                START();
                
                pawn::demarh_t<0, int> vehicle_id(amx, params);
                pawn::demarh_t<1, int> killer_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_vehicle_death, /*p*/ vehicle_id.get() SEPARATOR  killer_id.get());
                CALL(/*f*/ on_vehicle_death /*p*/ , vehicle_id.get(), killer_id.get());
        }


        //OnPlayerText(playerid, text[]);
        NATIVE_DECL(OnPlayerText)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, /*const*/ std::string> text(amx, params); // allow scripts to change message, edit events_samp.inl
                DEBUG_CALLBACK(/*f*/ on_player_text, /*p*/ player_id.get() SEPARATOR  text.get());
                CALL_R(/*f*/ on_player_text /*p*/ , player_id.get(), text.get());
                return 1; // always allow player's chat
        }


        //OnPlayerCommandText(playerid, cmdtext[]);
        NATIVE_DECL(OnPlayerCommandText)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, const std::string> cmd(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_command_text, /*p*/ player_id.get() SEPARATOR  cmd.get());
                CALL(/*f*/ on_player_command_text /*p*/ , player_id.get(), cmd.get());
                return 1;
        }


        //OnPlayerRequestClass(playerid, classid);
        NATIVE_DECL(OnPlayerRequestClass)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> class_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_request_class, /*p*/ player_id.get() SEPARATOR  class_id.get());
                CALL(/*f*/ on_player_request_class /*p*/ , player_id.get(), class_id.get()); 
        }


        //OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
        NATIVE_DECL(OnPlayerEnterVehicle)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> vehicle_id(amx, params);
                pawn::demarh_t<2, bool> is_passenger(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_enter_vehicle, /*p*/ player_id.get() SEPARATOR  vehicle_id.get() SEPARATOR  is_passenger.get());
                CALL(/*f*/ on_player_enter_vehicle /*p*/ , player_id.get(), vehicle_id.get(), is_passenger.get()); 
        }


        //OnPlayerExitVehicle(playerid, vehicleid);
        NATIVE_DECL(OnPlayerExitVehicle)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> vehicle_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_exit_vehicle, /*p*/ player_id.get() SEPARATOR  vehicle_id.get());
                CALL(/*f*/ on_player_exit_vehicle /*p*/ , player_id.get(), vehicle_id.get()); 
        }


        //OnPlayerStateChange(playerid, newstate, oldstate);
        NATIVE_DECL(OnPlayerStateChange)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> newstate_int(amx, params);
                pawn::demarh_t<2, int> oldstate_int(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_state_change, /*p*/ player_id.get() SEPARATOR  newstate_int.get() SEPARATOR  oldstate_int.get());
                CALL(/*f*/ on_player_state_change /*p*/ , player_id.get(), newstate_int.get(), oldstate_int.get());
        }



        //OnPlayerEnterCheckpoint(playerid);
        NATIVE_DECL(OnPlayerEnterCheckpoint)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_enter_checkpoint, /*p*/ player_id.get());
                CALL(/*f*/ on_player_enter_checkpoint /*p*/ , player_id.get()); 
        }


        //OnPlayerLeaveCheckpoint(playerid);
        NATIVE_DECL(OnPlayerLeaveCheckpoint)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_leave_checkpoint, /*p*/ player_id.get());
                CALL(/*f*/ on_player_leave_checkpoint /*p*/ , player_id.get()); 
        }

        //OnPlayerEnterRaceCheckpoint(playerid);
        NATIVE_DECL(OnPlayerEnterRaceCheckpoint)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_enter_race_checkpoint, /*p*/ player_id.get());
                CALL(/*f*/ on_player_enter_race_checkpoint /*p*/ , player_id.get()); 
        }


        //OnPlayerLeaveRaceCheckpoint(playerid);
        NATIVE_DECL(OnPlayerLeaveRaceCheckpoint)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_leave_race_checkpoint, /*p*/ player_id.get());
                CALL(/*f*/ on_player_leave_race_checkpoint /*p*/ , player_id.get()); 
        }


        //OnRconCommand(cmd[]);
        NATIVE_DECL(OnRconCommand)
        {
                START();
                
                pawn::demarh_t<0, const std::string> cmd(amx, params);
                DEBUG_CALLBACK(/*f*/ on_rcon_command, /*p*/ cmd.get());
                CALL(/*f*/ on_rcon_command /*p*/ , cmd.get());
        }



        //OnPlayerRequestSpawn(playerid);
        NATIVE_DECL(OnPlayerRequestSpawn)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_request_spawn, /*p*/ player_id.get());
                CALL(/*f*/ on_player_request_spawn /*p*/ , player_id.get()); 
        }


        //OnObjectMoved(objectid);
        NATIVE_DECL(OnObjectMoved)
        {
                START();
                
                pawn::demarh_t<0, int> object_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_object_moved, /*p*/ object_id.get());
                CALL(/*f*/ on_object_moved /*p*/ , object_id.get()); 
        }


        //OnPlayerObjectMoved(playerid, objectid);
        NATIVE_DECL(OnPlayerObjectMoved)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> object_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_object_moved, /*p*/ player_id.get() SEPARATOR  object_id.get());
                CALL(/*f*/ on_player_object_moved /*p*/ , player_id.get(), object_id.get());
        }


        //OnPlayerPickUpPickup(playerid, pickupid);
        NATIVE_DECL(OnPlayerPickUpPickup)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> pickup_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_pick_up_pickup, /*p*/ player_id.get() SEPARATOR  pickup_id.get());
                CALL(/*f*/ on_player_pick_up_pickup /*p*/ , player_id.get(), pickup_id.get());
        }


        //OnEnterExitModShop(playerid, enterexit, interiorid);
        NATIVE_DECL(OnEnterExitModShop)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> enter_exit(amx, params);
                pawn::demarh_t<2, int> interior_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_enter_exit_mod_shop, /*p*/ player_id.get() SEPARATOR  enter_exit.get() SEPARATOR  interior_id.get());
                CALL(/*f*/ on_enter_exit_mod_shop /*p*/ , player_id.get(), enter_exit.get(), interior_id.get()); 
        }


        //OnVehicleMod(playerid, vehicleid, componentid);
        NATIVE_DECL(OnVehicleMod)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> vehicle_id(amx, params);
                pawn::demarh_t<2, int> component_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_vehicle_mod, /*p*/ player_id.get() SEPARATOR  vehicle_id.get() SEPARATOR  component_id.get());
                CALL(/*f*/ on_vehicle_mod /*p*/ , player_id.get(), vehicle_id.get(), component_id.get()); 
        }


        //OnVehiclePaintjob(playerid, vehicleid, paintjobid);
        NATIVE_DECL(OnVehiclePaintjob)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> vehicle_id(amx, params);
                pawn::demarh_t<2, int> paintjob_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_vehicle_paintjob, /*p*/ player_id.get() SEPARATOR  vehicle_id.get() SEPARATOR  paintjob_id.get());
                CALL(/*f*/ on_vehicle_paintjob /*p*/ , player_id.get(), vehicle_id.get(), paintjob_id.get()); 
        }


        //OnVehicleRespray(playerid, vehicleid, color1, color2);
        NATIVE_DECL(OnVehicleRespray)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> vehicle_id(amx, params);
                pawn::demarh_t<2, int> color1(amx, params);
                pawn::demarh_t<3, int> color2(amx, params);
                DEBUG_CALLBACK(/*f*/ on_vehicle_respray, /*p*/ player_id.get() SEPARATOR  vehicle_id.get() SEPARATOR  color1.get() SEPARATOR  color2.get());
                CALL(/*f*/ on_vehicle_respray /*p*/ , player_id.get(), vehicle_id.get(), color1.get(), color2.get()); 
        }


        //OnPlayerSelectedMenuRow(playerid, row);
        NATIVE_DECL(OnPlayerSelectedMenuRow)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> row(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_selected_menu_row, /*p*/ player_id.get() SEPARATOR  row.get());
                CALL(/*f*/ on_player_selected_menu_row /*p*/ , player_id.get(), row.get());
        }


        //OnPlayerExitedMenu(playerid);
        NATIVE_DECL(OnPlayerExitedMenu)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_exited_menu, /*p*/ player_id.get());
                CALL(/*f*/ on_player_exited_menu /*p*/ , player_id.get()); 
        }


        //OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);
        NATIVE_DECL(OnPlayerInteriorChange)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> interior_id_new(amx, params);
                pawn::demarh_t<2, int> interior_id_old(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_interior_change, /*p*/ player_id.get() SEPARATOR  interior_id_new.get() SEPARATOR  interior_id_old.get());
                CALL(/*f*/ on_player_interior_change /*p*/ , player_id.get(), interior_id_new.get(), interior_id_old.get()); 
        }


        //OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
        NATIVE_DECL(OnPlayerKeyStateChange)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> keys_new(amx, params);
                pawn::demarh_t<2, int> keys_old(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_key_state_change, /*p*/ player_id.get() SEPARATOR  keys_new.get() SEPARATOR  keys_old.get());
                CALL(/*f*/ on_player_key_state_change /*p*/ , player_id.get(), keys_new.get(), keys_old.get());
        }


        //OnPlayerUpdate(playerid);
        NATIVE_DECL(OnPlayerUpdate)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_update, /*p*/ player_id.get());
                CALL(/*f*/ on_player_update /*p*/ , player_id.get());
                return 1;
        }


        // OnRconLoginAttempt(ip[], password[], success);
        NATIVE_DECL(OnRconLoginAttempt)
        {
                START();
                
                pawn::demarh_t<0, const std::string> ip(amx, params);
                pawn::demarh_t<1, const std::string> password(amx, params);
                pawn::demarh_t<3, bool> is_success(amx, params);
                DEBUG_CALLBACK(/*f*/ on_rcon_login_attempt, /*p*/ ip.get() SEPARATOR  password.get() SEPARATOR  is_success.get());
                CALL(/*f*/ on_rcon_login_attempt /*p*/ , ip.get(), password.get(), is_success.get()); 
        }


        // OnPlayerStreamIn(playerid, forplayerid);
        NATIVE_DECL(OnPlayerStreamIn)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> for_player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_stream_in, /*p*/ player_id.get() SEPARATOR  for_player_id.get());
                CALL(/*f*/ on_player_stream_in /*p*/ , player_id.get(), for_player_id.get()); 
        }


        // OnPlayerStreamOut(playerid, forplayerid);
        NATIVE_DECL(OnPlayerStreamOut)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> for_player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_stream_out, /*p*/ player_id.get() SEPARATOR  for_player_id.get());
                CALL(/*f*/ on_player_stream_out /*p*/ , player_id.get(), for_player_id.get()); 
        }


        // OnVehicleStreamIn(vehicleid, forplayerid);
        NATIVE_DECL(OnVehicleStreamIn)
        {
                START();
                
                pawn::demarh_t<0, int> vehicle_id(amx, params);
                pawn::demarh_t<1, int> for_player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_vehicle_stream_in, /*p*/ vehicle_id.get() SEPARATOR  for_player_id.get());
                CALL(/*f*/ on_vehicle_stream_in /*p*/ , vehicle_id.get(), for_player_id.get()); 
        }


        // OnVehicleStreamOut(vehicleid, forplayerid);
        NATIVE_DECL(OnVehicleStreamOut)
        {
                START();
                
                pawn::demarh_t<0, int> vehicle_id(amx, params);
                pawn::demarh_t<1, int> for_player_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_vehicle_stream_out, /*p*/ vehicle_id.get() SEPARATOR  for_player_id.get());
                CALL(/*f*/ on_vehicle_stream_out /*p*/ , vehicle_id.get(), for_player_id.get()); 
        }


        // OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
        NATIVE_DECL(OnDialogResponse)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> dialog_id(amx, params);
                pawn::demarh_t<2, int> response(amx, params);
                pawn::demarh_t<3, int> list_item(amx, params);
                pawn::demarh_t<4, const std::string> input_text(amx, params);
                DEBUG_CALLBACK(/*f*/ on_dialog_response, /*p*/ player_id.get() SEPARATOR  dialog_id.get() SEPARATOR  response.get() SEPARATOR  list_item.get() SEPARATOR  input_text.get());
                CALL(/*f*/ on_dialog_response /*p*/ , player_id.get(), dialog_id.get(), response.get(), list_item.get(), input_text.get()); 
        }


        // OnPlayerClickPlayer(playerid, clickedplayerid, source);
        NATIVE_DECL(OnPlayerClickPlayer)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> clicked_player_id(amx, params);
                pawn::demarh_t<2, int> source_int(amx, params);
                DEBUG_CALLBACK(/*f*/ on_player_click_player, /*p*/ player_id.get() SEPARATOR  clicked_player_id.get() SEPARATOR  source_int.get());
                CALL(/*f*/ on_player_click_player /*p*/ , player_id.get(), clicked_player_id.get(), source_int.get());
        }
        
        NATIVE_DECL(OnVehicleDamageStatusUpdate)
        {
                START();
                
                pawn::demarh_t<0, int> player_id(amx, params);
                pawn::demarh_t<1, int> vehicle_id(amx, params);
                DEBUG_CALLBACK(/*f*/ on_vehicle_damage_status_update, /*p*/ player_id.get() SEPARATOR  vehicle_id.get());
                CALL(/*f*/ on_vehicle_damage_status_update /*p*/ , player_id.get(), vehicle_id.get());
        }
        

              //cell AMX_NATIVE_CALL ([A-Za-z0-9]+)\(AMX\* amx, cell\* params\) \{(([\n\t ]*pawn::.+)*)[\n\t ]*[^}]*\}[^}]*\}[\n\t ]*.*container_execute_handlers\(application::instance\(\), &.+_i::([^,]+)([^;]*);[^}]+\}
              //NATIVE_DECL(\1) \n\t{\n\t\t\2\n\t\tCALL(/*f*/ \4 /*p*/ \5; \n\t}\n
              
              //(CALL\(/\*f\*/ ([a-z_0-9]+) /\*p\*/ , ([^;]*);)
              //DEBUG_CALLBACK(/*f*/ \2, /*p*/ \3;\n\t\t\1
              
              //(DEBUG_CALLBACK\(/\*f\*/ [^,]+, /\*p\*/ [^,]+),
              //\1 SEPARATOR 


        AMX_NATIVE_INFO toexport[] =
        {
            {"_GameModeInit",              OnGameModeInit},
            {"_GameModeExit",              OnGameModeExit},
            {"_PlayerConnect",             OnPlayerConnect},
            {"_PlayerDisconnect",          OnPlayerDisconnect},
            {"_PlayerSpawn",               OnPlayerSpawn},
            {"_PlayerDeath",               OnPlayerDeath},
            {"_VehicleSpawn",              OnVehicleSpawn},
            {"_VehicleDeath",              OnVehicleDeath},
            {"_PlayerText",                OnPlayerText},
            {"_PlayerCommandText",         OnPlayerCommandText},
            {"_PlayerRequestClass",        OnPlayerRequestClass},
            {"_PlayerEnterVehicle",        OnPlayerEnterVehicle},
            {"_PlayerExitVehicle",         OnPlayerExitVehicle},
            {"_PlayerStateChange",         OnPlayerStateChange},
            {"_PlayerEnterCheckpoint",     OnPlayerEnterCheckpoint},
            {"_PlayerLeaveCheckpoint",     OnPlayerLeaveCheckpoint},
            {"_PlayerEnterRaceCheckpoint", OnPlayerEnterRaceCheckpoint},
            {"_PlayerLeaveRaceCheckpoint", OnPlayerLeaveRaceCheckpoint},
            {"_RconCommand",               OnRconCommand},
            {"_PlayerRequestSpawn",        OnPlayerRequestSpawn},
            {"_ObjectMoved",               OnObjectMoved},
            {"_PlayerObjectMoved",         OnPlayerObjectMoved},
            {"_PlayerPickUpPickup",        OnPlayerPickUpPickup},
            {"_EnterExitModShop",          OnEnterExitModShop},
            {"_VehicleMod",                OnVehicleMod},
            {"_VehiclePaintjob",           OnVehiclePaintjob},
            {"_VehicleRespray",            OnVehicleRespray},
            {"_PlayerSelectedMenuRow",     OnPlayerSelectedMenuRow},
            {"_PlayerExitedMenu",          OnPlayerExitedMenu},
            {"_PlayerInteriorChange",      OnPlayerInteriorChange},
            {"_PlayerKeyStateChange",      OnPlayerKeyStateChange},
            {"_PlayerUpdate",              OnPlayerUpdate},
            {"_RconLoginAttempt",          OnRconLoginAttempt},
            {"_PlayerStreamIn",            OnPlayerStreamIn},
            {"_PlayerStreamOut",           OnPlayerStreamOut},
            {"_VehicleStreamIn",           OnVehicleStreamIn},
            {"_VehicleStreamOut",          OnVehicleStreamOut},
            {"_DialogResponse",            OnDialogResponse},
            {"_PlayerClickPlayer",         OnPlayerClickPlayer},
            {"_VehicleDamageStatusUpdate", OnVehicleDamageStatusUpdate},
            {0, 0}

        };
        
        


} // namespace 
