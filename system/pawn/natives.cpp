#include "config.h"
#include "pawn_marshaling.hpp"
#include "natives.h"

#include "util/overtimer.hpp"

#include <string>

#ifndef MAX_NATIVE_EXEC_TIME
#ifdef MAX_EXEC_TIME
#define MAX_NATIVE_EXEC_TIME MAX_EXEC_TIME
#else
#define MAX_NATIVE_EXEC_TIME 3
#endif // MAX_EXEC_TIME
#endif //MAX_NATIVE_EXEC_TIME

#define START() MAKE_OVERTIMER(MAX_NATIVE_EXEC_TIME) // only in debug

#ifdef PRINT_OUTCOMING_NATIVES
#include <boost/preprocessor/stringize.hpp>
#include <iostream>
#define DEBUG_NATIVE(f,p) std::cout << BOOST_PP_STRINGIZE(f) "(" << p << ");" << std::endl
#else
#define DEBUG_NATIVE(f,...) (static_cast<void> (0)) /* empty */
#endif

#define SEPARATOR << ", " <<

// https://gta-paradise-sa.googlecode.com/svn/trunk/src/cplusplus/freezone-samp/src/core/samp/samp_api.cpp

namespace native 
{

    namespace 
    {
        //Данные для маршалинга аргументов в павн
        pawn::marh_collection_t marhs; // Должен быть до объявлений marh_t

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // a_objects.inc
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        pawn::marh_t<int, float, float, float, float, float, float, float> create_object_t("CreateObject", marhs);
        pawn::marh_t<int, float, float, float> set_object_pos_t("SetObjectPos", marhs);
        pawn::marh_t<int, float&, float&, float&> get_object_pos_t("GetObjectPos", marhs);
        pawn::marh_t<int, float, float, float> set_object_rot_t("SetObjectRot", marhs);
        pawn::marh_t<int, float&, float&, float&> get_object_rot_t("GetObjectRot", marhs);
        pawn::marh_t<int> is_valid_object_t("IsValidObject", marhs);
        pawn::marh_t<int> destroy_object_t("DestroyObject", marhs);
        pawn::marh_t<int, float, float, float, float> move_object_t("MoveObject", marhs);
        pawn::marh_t<int> stop_object_t("StopObject", marhs);
        pawn::marh_t<int, int, float, float, float, float, float, float, float> create_player_object_t("CreatePlayerObject", marhs);
        pawn::marh_t<int, int, float, float, float> set_player_object_pos_t("SetPlayerObjectPos", marhs);
        pawn::marh_t<int, int, float&, float&, float&> get_player_object_pos_t("GetPlayerObjectPos", marhs);
        pawn::marh_t<int, int, float, float, float> set_player_object_rot_t("SetPlayerObjectRot", marhs);
        pawn::marh_t<int, int, float&, float&, float&> get_player_object_rot_t("GetPlayerObjectRot", marhs);
        pawn::marh_t<int, int> is_valid_player_object_t("IsValidPlayerObject", marhs);
        pawn::marh_t<int, int> destroy_player_object_t("DestroyPlayerObject", marhs);
        pawn::marh_t<int, int, float, float, float, float> move_player_object_t("MovePlayerObject", marhs);
        pawn::marh_t<int, int> stop_player_object_t("StopPlayerObject", marhs);
        pawn::marh_t<int, int, float, float, float, float, float, float> attach_object_to_player_t("AttachObjectToPlayer", marhs);
        pawn::marh_t<int, int, int, float, float, float, float, float, float> attach_player_object_to_player_t("AttachPlayerObjectToPlayer", marhs);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // a_players.inc
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Player
        pawn::marh_t<int, int, int, float, float, float, float, int, int, int, int, int, int> set_spawn_info_t("SetSpawnInfo", marhs);
        pawn::marh_t<int> spawn_player_t("SpawnPlayer", marhs);

        // Player info
        pawn::marh_t<int, float, float, float> set_player_pos_t("SetPlayerPos", marhs);
        pawn::marh_t<int, float, float, float> set_player_pos_findz_t("SetPlayerPosFindZ", marhs);
        pawn::marh_t<int, float&, float&, float&> get_player_pos_t("GetPlayerPos", marhs);
        pawn::marh_t<int, float> set_player_facing_angle_t("SetPlayerFacingAngle", marhs);
        pawn::marh_t<int, float&> get_player_facing_angle_t("GetPlayerFacingAngle", marhs);
        pawn::marh_t<int, float, float, float, float> is_player_in_range_of_point_t("IsPlayerInRangeOfPoint", marhs);
        pawn::marh_t<int, int> is_player_streamed_in_t("IsPlayerStreamedIn", marhs);
        pawn::marh_t<int, int> set_player_interior_t("SetPlayerInterior", marhs);
        pawn::marh_t<int> get_player_interior_t("GetPlayerInterior", marhs);
        pawn::marh_t<int, float> set_player_health_t("SetPlayerHealth", marhs);
        pawn::marh_t<int, float&> get_player_health_t("GetPlayerHealth", marhs);
        pawn::marh_t<int, float> set_player_armour_t("SetPlayerArmour", marhs);
        pawn::marh_t<int, float&> get_player_armour_t("GetPlayerArmour", marhs);
        pawn::marh_t<int, int, int> set_player_ammo_t("SetPlayerAmmo", marhs);
        pawn::marh_t<int> get_player_ammo_t("GetPlayerAmmo", marhs);
        pawn::marh_t<int> get_player_weapon_state_t("GetPlayerWeaponState", marhs);
        pawn::marh_t<int, int> set_player_team_t("SetPlayerTeam", marhs);
        pawn::marh_t<int> get_player_team_t("GetPlayerTeam", marhs);
        pawn::marh_t<int, int> set_player_score_t("SetPlayerScore", marhs);
        pawn::marh_t<int> get_player_score_t("GetPlayerScore", marhs);
        pawn::marh_t<int> get_player_drunk_level_t("GetPlayerDrunkLevel", marhs);
        pawn::marh_t<int, int> set_player_drunk_level_t("SetPlayerDrunkLevel", marhs);
        pawn::marh_t<int, unsigned> set_player_color_t("SetPlayerColor", marhs);
        pawn::marh_t<int> get_player_color_t("GetPlayerColor", marhs);
        pawn::marh_t<int, int> set_player_skin_t("SetPlayerSkin", marhs);
        pawn::marh_t<int> get_player_skin_t("GetPlayerSkin", marhs);
        pawn::marh_t<int, int, int> give_player_weapon_t("GivePlayerWeapon", marhs);
        pawn::marh_t<int> reset_player_weapons_t("ResetPlayerWeapons", marhs);
        pawn::marh_t<int, int> set_player_armed_weapon_t("SetPlayerArmedWeapon", marhs);
        pawn::marh_t<int, int, int&, int&> get_player_weapon_data_t("GetPlayerWeaponData", marhs);
        pawn::marh_t<int, int> give_player_money_t("GivePlayerMoney", marhs);
        pawn::marh_t<int> reset_player_money_t("ResetPlayerMoney", marhs);
        pawn::marh_t<int, std::string const&> set_player_name_t("SetPlayerName", marhs);
        pawn::marh_t<int> get_player_money_t("GetPlayerMoney", marhs);
        pawn::marh_t<int> get_player_state_t("GetPlayerState", marhs);
        pawn::marh_t<int, std::string&, pawn::string_len> get_player_ip_t("GetPlayerIp", marhs);
        pawn::marh_t<int> get_player_ping_t("GetPlayerPing", marhs);
        pawn::marh_t<int> get_player_weapon_t("GetPlayerWeapon", marhs);
        pawn::marh_t<int, int&, int&, int&> get_player_keys_t("GetPlayerKeys", marhs);
        pawn::marh_t<int, std::string&, pawn::string_len> get_player_name_t("GetPlayerName", marhs);
        pawn::marh_t<int, int, int> set_player_time_t("SetPlayerTime", marhs);
        pawn::marh_t<int, int&, int&> get_player_time_t("GetPlayerTime", marhs);
        pawn::marh_t<int, int> toggle_player_clock_t("TogglePlayerClock", marhs);
        pawn::marh_t<int, int> set_player_weather_t("SetPlayerWeather", marhs);
        pawn::marh_t<int> force_class_selection_t("ForceClassSelection", marhs);
        pawn::marh_t<int, int> set_player_wanted_level_t("SetPlayerWantedLevel", marhs);
        pawn::marh_t<int> get_player_wanted_level_t("GetPlayerWantedLevel", marhs);
        pawn::marh_t<int, int> set_player_fighting_style_t("SetPlayerFightingStyle", marhs);
        pawn::marh_t<int> get_player_fighting_style_t("GetPlayerFightingStyle", marhs);
        pawn::marh_t<int, float, float, float> set_player_velocity_t("SetPlayerVelocity", marhs);
        pawn::marh_t<int, float&, float&, float&> get_player_velocity_t("GetPlayerVelocity", marhs);
        pawn::marh_t<int, int, int> play_crime_report_for_player_t("PlayCrimeReportForPlayer", marhs);
        pawn::marh_t<int, std::string const&> set_player_shop_name_t("SetPlayerShopName", marhs);
        pawn::marh_t<int, int, int> set_player_skill_level_t("SetPlayerSkillLevel", marhs);
        pawn::marh_t<int> get_player_surfing_vehicle_id_t("GetPlayerSurfingVehicleID", marhs);
#ifdef _03B
        pawn::marh_t<int, int, int, float, float, float, float, float, float> set_player_holding_object_t("SetPlayerHoldingObject", marhs);
        pawn::marh_t<int> stop_player_holding_object_t("StopPlayerHoldingObject", marhs);
        pawn::marh_t<int> is_player_holding_object_t("IsPlayerHoldingObject", marhs);
#endif
#ifdef _03C
	pawn::marh_t<int, int, int, int, float, float, float, float, float, float, float, float, float> set_player_attached_object_t("SetPlayerAttachedObject", marhs);
	pawn::marh_t<int, int> remove_player_attached_object_t("RemovePlayerAttachedObject", marhs);
	pawn::marh_t<int, int> is_player_attached_object_slot_used_t("IsPlayerAttachedObjectSlotUsed", marhs);
	
	pawn::marh_t<int, int, float, float, float, float, float, float> attach_object_to_vehicle_t("AttachObjectToVehicle", marhs);

#endif
        pawn::marh_t<int, std::string const&, unsigned int, float, int> set_player_chat_bubble_t("SetPlayerChatBubble", marhs);

        // Player controls
        pawn::marh_t<int, int, int> put_player_in_vehicle_t("PutPlayerInVehicle", marhs);
        pawn::marh_t<int> get_player_vehicle_id_t("GetPlayerVehicleID", marhs);
        pawn::marh_t<int> get_player_vehicle_seat_t("GetPlayerVehicleSeat", marhs);
        pawn::marh_t<int> remove_player_from_vehicle_t("RemovePlayerFromVehicle", marhs);
        pawn::marh_t<int, bool> toggle_player_controllable_t("TogglePlayerControllable", marhs);
        pawn::marh_t<int, int, float, float, float> player_play_sound_t("PlayerPlaySound", marhs);
        pawn::marh_t<int, std::string const&, std::string const&, float, int, int, int, int, int, int> apply_animation_t("ApplyAnimation", marhs);
        pawn::marh_t<int, int> clear_animations_t("ClearAnimations", marhs);
        pawn::marh_t<int> get_player_animation_index_t("GetPlayerAnimationIndex", marhs);
        pawn::marh_t<int, std::string&, pawn::string_len, std::string&, pawn::string_len> get_animation_name_t("GetAnimationName", marhs);
        pawn::marh_t<int> get_player_special_action_t("GetPlayerSpecialAction", marhs);
        pawn::marh_t<int, int> set_player_special_action_t("SetPlayerSpecialAction", marhs);

        // Player world/map related
        pawn::marh_t<int, float, float, float, float> set_player_checkpoint_t("SetPlayerCheckpoint", marhs);
        pawn::marh_t<int> disable_player_checkpoint_t("DisablePlayerCheckpoint", marhs);
        pawn::marh_t<int, int, float, float, float, float, float, float, float> set_player_race_checkpoint_t("SetPlayerRaceCheckpoint", marhs);
        pawn::marh_t<int> disable_player_race_checkpoint_t("DisablePlayerRaceCheckpoint", marhs);
        pawn::marh_t<int, float, float, float, float> set_player_world_bounds_t("SetPlayerWorldBounds", marhs);
        pawn::marh_t<int, int, unsigned> set_player_marker_for_player_t("SetPlayerMarkerForPlayer", marhs);
        pawn::marh_t<int, int, bool> show_player_name_tag_for_player_t("ShowPlayerNameTagForPlayer", marhs);
        pawn::marh_t<int, int, float, float, float, int, unsigned> set_player_mapicon_t("SetPlayerMapIcon", marhs);
        pawn::marh_t<int, int> remove_player_mapicon_t("RemovePlayerMapIcon", marhs);
        pawn::marh_t<int, bool> allow_player_teleport_t("AllowPlayerTeleport", marhs);

        // Player camera
        pawn::marh_t<int, float, float, float> set_player_camera_pos_t("SetPlayerCameraPos", marhs);
        pawn::marh_t<int, float, float, float> set_player_camera_look_at_t("SetPlayerCameraLookAt", marhs);
        pawn::marh_t<int> set_camera_behind_player_t("SetCameraBehindPlayer", marhs);
        pawn::marh_t<int, float&, float&, float&> get_player_camera_pos_t("GetPlayerCameraPos", marhs);
        pawn::marh_t<int, float&, float&, float&> get_player_camera_front_vector_t("GetPlayerCameraFrontVector", marhs);

        // Player conditionals
        pawn::marh_t<int> is_player_called_t("IsPlayerConnected", marhs);
        pawn::marh_t<int, int> is_player_in_vehicle_t("IsPlayerInVehicle", marhs);
        pawn::marh_t<int> is_player_in_any_vehicle_t("IsPlayerInAnyVehicle", marhs);
        pawn::marh_t<int> is_player_in_checkpoint_t("IsPlayerInCheckpoint", marhs);
        pawn::marh_t<int> is_player_in_race_checkpoint_t("IsPlayerInRaceCheckpoint", marhs);

        // Virtual Worlds
        pawn::marh_t<int, int> set_player_virtual_world_t("SetPlayerVirtualWorld", marhs);
        pawn::marh_t<int> get_player_virtual_world_t("GetPlayerVirtualWorld", marhs);

        // Insane Stunts
        pawn::marh_t<int, bool> enable_stunt_bonus_for_player_t("EnableStuntBonusForPlayer", marhs);
        pawn::marh_t<bool> enable_stunt_bonus_for_all_t("EnableStuntBonusForAll", marhs);

        // Spectating
        pawn::marh_t<int, bool> toggle_player_spectating_t("TogglePlayerSpectating", marhs);
        pawn::marh_t<int, int, int> player_spectate_player_t("PlayerSpectatePlayer", marhs);
        pawn::marh_t<int, int, int> player_spectate_vehicle_t("PlayerSpectateVehicle", marhs);

        // Recording for NPC playback
        pawn::marh_t<int, int, std::string const&> start_recording_player_data_t("StartRecordingPlayerData", marhs);
        pawn::marh_t<int> stop_recording_player_data_t("StopRecordingPlayerData", marhs);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // a_samp.inc
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Util
        pawn::marh_t<int, unsigned, std::string const&> send_client_message_t("SendClientMessage", marhs);
        pawn::marh_t<int, int, std::string const&> send_player_message_to_player_t("SendPlayerMessageToPlayer", marhs);
        pawn::marh_t<int, int, int> send_death_message_t("SendDeathMessage", marhs);
        pawn::marh_t<int, std::string const&, int, int> game_text_for_player_t("GameTextForPlayer", marhs);
        pawn::marh_t<> get_max_players_t("GetMaxPlayers", marhs);

        // Game
        pawn::marh_t<std::string const&> set_game_mode_text_t("SetGameModeText", marhs);
        pawn::marh_t<int> set_team_count_t("SetTeamCount", marhs);
        pawn::marh_t<int, float, float, float, float, int, int, int, int, int, int> add_player_class_t("AddPlayerClass", marhs);
        pawn::marh_t<int, int, float, float, float, float, int, int, int, int, int, int> add_player_class_ex_t("AddPlayerClassEx", marhs);
        pawn::marh_t<int, float, float, float, float, int, int> add_static_vehicle_t("AddStaticVehicle", marhs);
        pawn::marh_t<int, float, float, float, float, int, int, int> add_static_vehicle_ex_t("AddStaticVehicleEx", marhs);
        pawn::marh_t<int, int, float, float, float, int> add_static_pickup_t("AddStaticPickup", marhs);
        pawn::marh_t<int, int, float, float, float, int> create_pickup_t("CreatePickup", marhs);
        pawn::marh_t<int> destroy_pickup_t("DestroyPickup", marhs);
        pawn::marh_t<bool> show_name_tags_t("ShowNameTags", marhs);
        pawn::marh_t<int> show_player_markers_t("ShowPlayerMarkers", marhs);
        pawn::marh_t<> gamemode_exit_t("GameModeExit", marhs);
        pawn::marh_t<int> set_world_time_t("SetWorldTime", marhs);
        pawn::marh_t<int, std::string&, pawn::string_len> get_weapon_name_t("GetWeaponName", marhs);
        pawn::marh_t<bool> enable_tire_popping_t("EnableTirePopping", marhs);
        pawn::marh_t<bool> allow_interior_weapons_t("AllowInteriorWeapons", marhs);
        pawn::marh_t<int> set_weather_t("SetWeather", marhs);
        pawn::marh_t<float> set_gravity_t("SetGravity", marhs);
        pawn::marh_t<bool> allow_admin_teleport_t("AllowAdminTeleport", marhs);
        pawn::marh_t<int> set_death_drop_amount_t("SetDeathDropAmount", marhs);
        pawn::marh_t<float, float, float, int, float> create_explosion_t("CreateExplosion", marhs);
        pawn::marh_t<bool> enable_zone_names_t("EnableZoneNames", marhs);
        pawn::marh_t<> use_player_ped_anims_t("UsePlayerPedAnims", marhs);
        pawn::marh_t<> disable_interior_enter_exits_t("DisableInteriorEnterExits", marhs);
        pawn::marh_t<float> set_name_tag_draw_distance_t("SetNameTagDrawDistance", marhs);
        pawn::marh_t<> disable_name_tag_los_t("DisableNameTagLOS", marhs);
        pawn::marh_t<float> limit_global_chat_radius_t("LimitGlobalChatRadius", marhs);
        pawn::marh_t<float> limit_player_marker_radius_t("LimitPlayerMarkerRadius", marhs);

        // Npc
        pawn::marh_t<std::string const&, std::string const&> call_npc_t("ConnectNPC", marhs);
        pawn::marh_t<int> is_player_npc_t("IsPlayerNPC", marhs);

        // Admin
        pawn::marh_t<int> is_player_admin_t("IsPlayerAdmin", marhs);
        pawn::marh_t<int> kick_t("Kick", marhs);
        pawn::marh_t<int> ban_t("Ban", marhs);
        pawn::marh_t<int, std::string const&> ban_ex_t("BanEx", marhs);
        pawn::marh_t<std::string const&> send_rcon_command_t("SendRconCommand", marhs);
        pawn::marh_t<std::string const&, std::string&, pawn::string_len> get_server_var_as_string_t("GetServerVarAsString", marhs);
        pawn::marh_t<std::string const&> get_server_var_as_int_t("GetServerVarAsInt", marhs);
        pawn::marh_t<std::string const&> get_server_var_as_bool_t("GetServerVarAsBool", marhs);

        // Menu
        pawn::marh_t<std::string const&, int, float, float, float, float> create_menu_t("CreateMenu", marhs);
        pawn::marh_t<int> destroy_menu_t("DestroyMenu", marhs);
        pawn::marh_t<int, int, std::string const&> add_menu_item_t("AddMenuItem", marhs);
        pawn::marh_t<int, int, std::string const&> set_menu_column_header_t("SetMenuColumnHeader", marhs);
        pawn::marh_t<int, int> show_menu_for_player_t("ShowMenuForPlayer", marhs);
        pawn::marh_t<int, int> hide_menu_for_player_t("HideMenuForPlayer", marhs);
        pawn::marh_t<int> is_valid_menu_t("IsValidMenu", marhs);
        pawn::marh_t<int> disable_menu_t("DisableMenu", marhs);
        pawn::marh_t<int, int> disable_menu_row_t("DisableMenuRow", marhs);
        pawn::marh_t<int> get_player_menu_t("GetPlayerMenu", marhs);

        // Text Draw
        pawn::marh_t<float, float, std::string const&> textdraw_create_t("TextDrawCreate", marhs);
        pawn::marh_t<int> textdraw_destroy_t("TextDrawDestroy", marhs);
        pawn::marh_t<int, float, float> textdraw_letter_size_t("TextDrawLetterSize", marhs);
        pawn::marh_t<int, float, float> textdraw_text_size_t("TextDrawTextSize", marhs);
        pawn::marh_t<int, int> textdraw_alignment_t("TextDrawAlignment", marhs);
        pawn::marh_t<int, unsigned> textdraw_color_t("TextDrawColor", marhs);
        pawn::marh_t<int, int> textdraw_use_box_t("TextDrawUseBox", marhs);
        pawn::marh_t<int, unsigned> textdraw_box_color_t("TextDrawBoxColor", marhs);
        pawn::marh_t<int, int> textdraw_set_shadow_t("TextDrawSetShadow", marhs);
        pawn::marh_t<int, int> textdraw_set_outline_t("TextDrawSetOutline", marhs);
        pawn::marh_t<int, unsigned> textdraw_background_color_t("TextDrawBackgroundColor", marhs);
        pawn::marh_t<int, int> textdraw_font_t("TextDrawFont", marhs);
        pawn::marh_t<int, bool> textdraw_set_proportional_t("TextDrawSetProportional", marhs);
        pawn::marh_t<int, int> textdraw_show_for_player_t("TextDrawShowForPlayer", marhs);
        pawn::marh_t<int, int> textdraw_hide_for_player_t("TextDrawHideForPlayer", marhs);
        pawn::marh_t<int, std::string const&> textdraw_set_string_t("TextDrawSetString", marhs);

        // Gang Zones
        pawn::marh_t<float, float, float, float> gangzone_create_t("GangZoneCreate", marhs);
        pawn::marh_t<int> gangzone_destroy_t("GangZoneDestroy", marhs);
        pawn::marh_t<int, int, unsigned> gangzone_show_for_player_t("GangZoneShowForPlayer", marhs);
        pawn::marh_t<int, int> gangzone_hide_for_player_t("GangZoneHideForPlayer", marhs);
        pawn::marh_t<int, int, int> gangzone_flash_for_player_t("GangZoneFlashForPlayer", marhs);
        pawn::marh_t<int, int> gangzone_stop_flash_for_player_t("GangZoneStopFlashForPlayer", marhs);

        // Global 3D Text Labels
        pawn::marh_t<std::string const&, unsigned int, float, float, float, float, int, bool> create_3dtextlabel_t("Create3DTextLabel", marhs);
        pawn::marh_t<int> delete_3dtextlabel_t("Delete3DTextLabel", marhs);
        pawn::marh_t<int, int, float, float, float> attach_3dtextlabel_to_player_t("Attach3DTextLabelToPlayer", marhs);
        pawn::marh_t<int, int, float, float, float> attach_3dtextlabel_to_vehicle_t("Attach3DTextLabelToVehicle", marhs);
        pawn::marh_t<int, unsigned int, std::string const&> update_3dtextlabel_text_t("Update3DTextLabelText", marhs);

        // Per-player 3D Text Labels
        pawn::marh_t<int, std::string const&, unsigned int, float, float, float, float, int, int, bool> create_player3dtextlabel_t("CreatePlayer3DTextLabel", marhs);
        pawn::marh_t<int, int> delete_player3dtextlabel_t("DeletePlayer3DTextLabel", marhs);
        pawn::marh_t<int, int, unsigned int, std::string const&> update_player3dtextlabel_text_t("UpdatePlayer3DTextLabelText", marhs);

        // Player GUI Dialog
        pawn::marh_t<int, int, int, std::string const&, std::string const&, std::string const&, std::string const&> show_player_dialog_t("ShowPlayerDialog", marhs); // ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[]);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // a_vehicles.inc
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Vehicle
        pawn::marh_t<int, float, float, float, float, int, int, int> create_vehicle_t("CreateVehicle", marhs);
        pawn::marh_t<int> destroy_vehicle_t("DestroyVehicle", marhs);
        pawn::marh_t<int, int> is_vehicle_streamed_in_t("IsVehicleStreamedIn", marhs);
        pawn::marh_t<int, float&, float&, float&> get_vehicle_pos_t("GetVehiclePos", marhs);
        pawn::marh_t<int, float, float, float> set_vehicle_pos_t("SetVehiclePos", marhs);
        pawn::marh_t<int, float&> get_vehicle_zangle_t("GetVehicleZAngle", marhs);
        pawn::marh_t<int, float&, float&, float&, float&> get_vehicle_rotation_quat_t("GetVehicleRotationQuat", marhs);
        pawn::marh_t<int, float> set_vehicle_zangle_t("SetVehicleZAngle", marhs);
        pawn::marh_t<int, int, bool, bool> set_vehicle_params_for_player_t("SetVehicleParamsForPlayer", marhs);
        pawn::marh_t<int> set_vehicle_to_respawn_t("SetVehicleToRespawn", marhs);
        pawn::marh_t<int, int> link_vehicle_to_interior_t("LinkVehicleToInterior", marhs);
        pawn::marh_t<int, int> add_vehicle_component_t("AddVehicleComponent", marhs);
        pawn::marh_t<int, int> remove_vehicle_component_t("RemoveVehicleComponent", marhs);
        pawn::marh_t<int, int, int> change_vehicle_color_t("ChangeVehicleColor", marhs);
        pawn::marh_t<int, int> change_vehicle_paintjob_t("ChangeVehiclePaintjob", marhs);
        pawn::marh_t<int, float> set_vehicle_health_t("SetVehicleHealth", marhs);
        pawn::marh_t<int, float&> get_vehicle_health_t("GetVehicleHealth", marhs);
        pawn::marh_t<int, int> attach_trailer_to_vehicle_t("AttachTrailerToVehicle", marhs);
        pawn::marh_t<int> detach_trailer_from_vehicle_t("DetachTrailerFromVehicle", marhs);
        pawn::marh_t<int> is_trailer_attached_to_vehicle_t("IsTrailerAttachedToVehicle", marhs);
        pawn::marh_t<int> get_vehicle_trailer_t("GetVehicleTrailer", marhs);
        pawn::marh_t<int, std::string const&> set_vehicle_number_plate_t("SetVehicleNumberPlate", marhs);
        pawn::marh_t<int> get_vehicle_model_t("GetVehicleModel", marhs);
        pawn::marh_t<int, int> get_vehicle_component_in_slot_t("GetVehicleComponentInSlot", marhs);
        pawn::marh_t<int> get_vehicle_component_type_t("GetVehicleComponentType", marhs);
        pawn::marh_t<int> repair_vehicle_t("RepairVehicle", marhs);
        pawn::marh_t<int, float&, float&, float&> get_vehicle_velocity_t("GetVehicleVelocity", marhs);
        pawn::marh_t<int, float, float, float> set_vehicle_velocity_t("SetVehicleVelocity", marhs);
        pawn::marh_t<int, float, float, float> set_vehicle_angular_velocity_t("SetVehicleAngularVelocity", marhs);
        pawn::marh_t<int, int&, int&, int&, int&> get_vehicle_damage_status_t("GetVehicleDamageStatus", marhs);
        pawn::marh_t<int, int, int, int, int> update_vehicle_damage_status_t("UpdateVehicleDamageStatus", marhs);

        // Virtual Worlds
        pawn::marh_t<int, int> set_vehicle_virtual_world_t("SetVehicleVirtualWorld", marhs);
        pawn::marh_t<int> get_vehicle_virtual_world_t("GetVehicleVirtualWorld", marhs);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Недокументированные возможности
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        pawn::marh_t<int, std::string&, pawn::string_len> gpci_t("gpci", marhs);
    } // namespace {


    //Инициализация мода - инициализирем методы маршалинга
    void natives_init(AMX* amx) 
    {

        typedef pawn::marh_collection_t::marhs_t::iterator iterator;
        for(iterator it = marhs.marhs.begin(), en = marhs.marhs.end(); it != en; ++it)
        {
            bool ret = (*it)->init(amx);
            if(!ret)
            {
              assert(false && "Не удалось инициализировать натив. Возможно его нужно прописать в sys_all_call() в игровом режиме");
              abort();
            }
        }
    }


    //Методы сампа

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_objects.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int create_object (int model_id, float x, float y, float z, float rx, float ry, float rz, float draw_distance) 
    {
        START();
        DEBUG_NATIVE(/*f*/create_object, /*p*/model_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz SEPARATOR  draw_distance);
        return (int) create_object_t.call(model_id, x, y, z, rx, ry, rz, draw_distance);
    }
    void set_object_pos (int object_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_object_pos, /*p*/object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_object_pos_t.call(object_id, x, y, z);
    }
    void get_object_pos (int object_id, float& x, float& y, float& z) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_object_pos, /*p*/object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        get_object_pos_t.call(object_id, x, y, z);
    }
    void set_object_rot (int object_id, float rx, float ry, float rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_object_rot, /*p*/object_id SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
        set_object_rot_t.call(object_id, rx, ry, rz);
    }
    void get_object_rot (int object_id, float& rx, float& ry, float& rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_object_rot, /*p*/object_id SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
        get_object_rot_t.call(object_id, rx, ry, rz);
    }
    bool is_valid_object (int object_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_valid_object, /*p*/object_id);
        return 0 != is_valid_object_t.call(object_id);
    }
    void destroy_object (int object_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/destroy_object, /*p*/object_id);
        destroy_object_t.call(object_id);
    }
    void move_object (int object_id, float x, float y, float z, float speed) 
    {
        START();
        DEBUG_NATIVE(/*f*/move_object, /*p*/object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  speed);
        move_object_t.call(object_id, x, y, z, speed);
    }
    void stop_object (int object_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/stop_object, /*p*/object_id);
        stop_object_t.call(object_id);
    }
    int create_player_object (int player_id, int model_id, float x, float y, float z, float rx, float ry, float rz, float draw_distance) 
    {
        START();
        DEBUG_NATIVE(/*f*/create_player_object, /*p*/player_id SEPARATOR  model_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz SEPARATOR  draw_distance);
        return (int) create_player_object_t.call(player_id, model_id, x, y, z, rx, ry, rz, draw_distance);
    }
    void set_player_object_pos (int player_id, int object_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_object_pos, /*p*/player_id SEPARATOR  object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_player_object_pos_t.call(player_id, object_id, x, y, z);
    }
    void get_player_object_pos (int player_id, int object_id, float& x, float& y, float& z) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_object_pos, /*p*/player_id SEPARATOR  object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        get_player_object_pos_t.call(player_id, object_id, x, y, z);
    }
    void set_player_object_rot (int player_id, int object_id, float rx, float ry, float rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_object_rot, /*p*/player_id SEPARATOR  object_id SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
        set_player_object_rot_t.call(player_id, object_id, rx, ry, rz);
    }
    void get_player_object_rot (int player_id, int object_id, float& rx, float& ry, float& rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_object_rot, /*p*/player_id SEPARATOR  object_id SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
        get_player_object_rot_t.call(player_id, object_id, rx, ry, rz);
    }
    bool is_valid_player_object (int player_id, int object_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_valid_player_object, /*p*/player_id SEPARATOR  object_id);
        return 0 != is_valid_player_object_t.call(player_id, object_id);
    }
    void destroy_player_object (int player_id, int object_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/destroy_player_object, /*p*/player_id SEPARATOR  object_id);
        destroy_player_object_t.call(player_id, object_id);
    }
    void move_player_object (int player_id, int object_id, float x, float y, float z, float speed) 
    {
        START();
        DEBUG_NATIVE(/*f*/move_player_object, /*p*/player_id SEPARATOR  object_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  speed);
        move_player_object_t.call(player_id, object_id, x, y, z, speed);
    }
    void stop_player_object (int player_id, int object_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/stop_player_object, /*p*/player_id SEPARATOR  object_id);
        stop_player_object_t.call(player_id, object_id);
    }
    void attach_object_to_player (int object_id, int player_id, float offset_x, float offset_y, float offset_z, float offset_rx, float offset_ry, float offset_rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/attach_object_to_player, /*p*/object_id SEPARATOR  player_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  offset_rx SEPARATOR  offset_ry SEPARATOR  offset_rz);
        attach_object_to_player_t.call(object_id, player_id, offset_x, offset_y, offset_z, offset_rx, offset_ry, offset_rz);
    }
    void attach_player_object_to_player (int object_player_id, int object_id, int attach_player_id, float offset_x, float offset_y, float offset_z, float offset_rx, float offset_ry, float offset_rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/attach_player_object_to_player, /*p*/object_player_id SEPARATOR  object_id SEPARATOR  attach_player_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  offset_rx SEPARATOR  offset_ry SEPARATOR  offset_rz);
        attach_player_object_to_player_t.call(object_player_id, object_id, attach_player_id, offset_x, offset_y, offset_z, offset_rx, offset_ry, offset_rz);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_players.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Player
    void set_spawn_info (int player_id, int team_id, int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_spawn_info, /*p*/player_id SEPARATOR  team_id SEPARATOR  skin_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  weapon_id1 SEPARATOR  weapon_ammo1 SEPARATOR  weapon_id2 SEPARATOR  weapon_ammo2 SEPARATOR  weapon_id3 SEPARATOR  weapon_ammo3);
        set_spawn_info_t.call(player_id, team_id, skin_id, x, y, z, rz, weapon_id1, weapon_ammo1, weapon_id2, weapon_ammo2, weapon_id3, weapon_ammo3);
    }
    void spawn_player (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/spawn_player, /*p*/player_id);
        spawn_player_t.call(player_id);
    }

    // Player info
    void set_player_pos (int player_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_pos, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_player_pos_t.call(player_id, x, y, z);
    }
    void set_player_pos_findz (int player_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_pos_findz, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_player_pos_findz_t.call(player_id, x, y, z);
    }
    void get_player_pos (int player_id, float& x, float& y, float& z) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_pos, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        get_player_pos_t.call(player_id, x, y, z);
    }
    void set_player_facing_angle (int player_id, float rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_facing_angle, /*p*/player_id SEPARATOR  rz);
        set_player_facing_angle_t.call(player_id, rz);
    }
    float get_player_facing_angle (int player_id) 
    {
        START();
        float rz;
        DEBUG_NATIVE(/*f*/get_player_facing_angle, /*p*/player_id SEPARATOR  rz);
        get_player_facing_angle_t.call(player_id, rz);
        return rz;
    }
    bool is_player_in_range_of_point (int player_id, float range, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_in_range_of_point, /*p*/player_id SEPARATOR  range SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        return 0 != is_player_in_range_of_point_t.call(player_id, range, x, y, z);
    }
    bool is_player_streamed_in (int player_id, int for_player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_streamed_in, /*p*/player_id SEPARATOR  for_player_id);
        return 0 != is_player_streamed_in_t.call(player_id, for_player_id);
    }
    void set_player_interior (int player_id, int interior_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_interior, /*p*/player_id SEPARATOR  interior_id);
        set_player_interior_t.call(player_id, interior_id);
    }
    int get_player_interior (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_interior, /*p*/player_id);
        return get_player_interior_t.call(player_id);
    }
    void set_player_health (int player_id, float health) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_health, /*p*/player_id SEPARATOR  health);
        set_player_health_t.call(player_id, health);
    }
    float get_player_health (int player_id) 
    {
        START();
        float rezult;
        DEBUG_NATIVE(/*f*/get_player_health, /*p*/player_id SEPARATOR  rezult);
        get_player_health_t.call(player_id, rezult);
        return rezult;
    }
    void set_player_armour (int player_id, float armour) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_armour, /*p*/player_id SEPARATOR  armour);
        set_player_armour_t.call(player_id, armour);
    }
    float get_player_armour (int player_id) 
    {
        START();
        float rezult;
        DEBUG_NATIVE(/*f*/get_player_armour, /*p*/player_id SEPARATOR  rezult);
        get_player_armour_t.call(player_id, rezult);
        return rezult;
    }
    void set_player_ammo (int player_id, int weapon_slot, int ammo) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_ammo, /*p*/player_id SEPARATOR  weapon_slot SEPARATOR  ammo);
        set_player_ammo_t.call(player_id, weapon_slot, ammo);
    }
    int get_player_ammo (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_ammo, /*p*/player_id);
        return get_player_ammo_t.call(player_id);
    }
    weapon_state get_player_weapon_state (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_weapon_state, /*p*/player_id);
        return static_cast<weapon_state>(get_player_weapon_state_t.call(player_id));
    }
    void set_player_team (int player_id, int team_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_team, /*p*/player_id SEPARATOR  team_id);
        set_player_team_t.call(player_id, team_id);
    }
    int get_player_team (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_team, /*p*/player_id);
        return get_player_team_t.call(player_id);
    }
    void set_player_score (int player_id, int score) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_score, /*p*/player_id SEPARATOR  score);
        set_player_score_t.call(player_id, score);
    }
    int get_player_score (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_score, /*p*/player_id);
        return get_player_score_t.call(player_id);
    }
    int get_player_drunk_level (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_drunk_level, /*p*/player_id);
        return get_player_drunk_level_t.call(player_id);
    }
    void set_player_drunk_level (int player_id, int level) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_drunk_level, /*p*/player_id SEPARATOR  level);
        set_player_drunk_level_t.call(player_id, level);
    }
    void set_player_color (int player_id, unsigned color) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_color, /*p*/player_id SEPARATOR  color);
        set_player_color_t.call(player_id, color);
    }
    unsigned get_player_color (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_color, /*p*/player_id);
        return get_player_color_t.call(player_id);
    }
    void set_player_skin (int player_id, int skin_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_skin, /*p*/player_id SEPARATOR  skin_id);
        set_player_skin_t.call(player_id, skin_id);
    }
    int get_player_skin (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_skin, /*p*/player_id);
        return get_player_skin_t.call(player_id);
    }
    void give_player_weapon (int player_id, int weapon_id, int weapon_ammo) 
    {
        START();
        DEBUG_NATIVE(/*f*/give_player_weapon, /*p*/player_id SEPARATOR  weapon_id SEPARATOR  weapon_ammo);
        give_player_weapon_t.call(player_id, weapon_id, weapon_ammo);
    }
    void reset_player_weapons (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/reset_player_weapons, /*p*/player_id);
        reset_player_weapons_t.call(player_id);
    }
    void set_player_armed_weapon (int player_id, int weapon_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_armed_weapon, /*p*/player_id SEPARATOR  weapon_id);
        set_player_armed_weapon_t.call(player_id, weapon_id);
    }
    void get_player_weapon_data (int player_id, int slot, int& weapon_id, int& weapon_ammo) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_weapon_data, /*p*/player_id SEPARATOR  slot SEPARATOR  weapon_id SEPARATOR  weapon_ammo);
        get_player_weapon_data_t.call(player_id, slot, weapon_id, weapon_ammo);
    }
    void give_player_money (int player_id, int money) 
    {
        START();
        DEBUG_NATIVE(/*f*/give_player_money, /*p*/player_id SEPARATOR  money);
        give_player_money_t.call(player_id, money);
    }
    void reset_player_money (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/reset_player_money, /*p*/player_id);
        reset_player_money_t.call(player_id);
    }
    int set_player_name (int player_id, std::string const& name) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_name, /*p*/player_id SEPARATOR  name);
        return set_player_name_t.call(player_id, name);
    }
    int get_player_money (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_money, /*p*/player_id);
        return get_player_money_t.call(player_id);
    }
    player_state get_player_state (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_state, /*p*/player_id);
        return static_cast<player_state>(get_player_state_t.call(player_id));
    }
    std::string get_player_ip (int player_id) 
    {
        START();
        std::string rezult;
        DEBUG_NATIVE(/*f*/get_player_ip, /*p*/player_id SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        get_player_ip_t.call(player_id, rezult, pawn::string_len::val);
        return rezult;
    }
    int get_player_ping (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_ping, /*p*/player_id);
        return get_player_ping_t.call(player_id);
    }
    int get_player_weapon (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_weapon, /*p*/player_id);
        return get_player_weapon_t.call(player_id);
    }
    void get_player_keys (int player_id, int& keys, int& updown, int& leftright) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_keys, /*p*/player_id SEPARATOR  keys SEPARATOR  updown SEPARATOR  leftright);
        get_player_keys_t.call(player_id, keys, updown, leftright);
    }
    std::string get_player_name (int player_id) 
    {
        START();
        std::string rezult;
        DEBUG_NATIVE(/*f*/get_player_name, /*p*/player_id SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        get_player_name_t.call(player_id, rezult, pawn::string_len::val);
        return rezult;
    }
    void set_player_time (int player_id, int hour, int minute) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_time, /*p*/player_id SEPARATOR  hour SEPARATOR  minute);
        set_player_time_t.call(player_id, hour, minute);
    }
    void get_player_time (int player_id, int& hour, int& minute) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_time, /*p*/player_id SEPARATOR  hour SEPARATOR  minute);
        get_player_time_t.call(player_id, hour, minute);
    }
    void toggle_player_clock (int player_id, int toggle) 
    {
        START();
        DEBUG_NATIVE(/*f*/toggle_player_clock, /*p*/player_id SEPARATOR  toggle);
        toggle_player_clock_t.call(player_id, toggle);
    }
    void set_player_weather (int player_id, int weather) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_weather, /*p*/player_id SEPARATOR  weather);
        set_player_weather_t.call(player_id, weather);
    }
    void force_class_selection (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/force_class_selection, /*p*/player_id);
        force_class_selection_t.call(player_id);
    }
    void set_player_wanted_level (int player_id, int level) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_wanted_level, /*p*/player_id SEPARATOR  level);
        set_player_wanted_level_t.call(player_id, level);
    }
    int get_player_wanted_level (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_wanted_level, /*p*/player_id);
        return get_player_wanted_level_t.call(player_id);
    }
    void set_player_fighting_style (int player_id, fight_style style) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_fighting_style, /*p*/player_id SEPARATOR  style);
        set_player_fighting_style_t.call(player_id, style);
    }
    fight_style get_player_fighting_style (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_fighting_style, /*p*/player_id);
        return static_cast<fight_style>(get_player_fighting_style_t.call(player_id));
    }
    void set_player_velocity (int player_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_velocity, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_player_velocity_t.call(player_id, x, y, z);
    }
    void get_player_velocity (int player_id, float& x, float& y, float& z) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_velocity, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        get_player_velocity_t.call(player_id, x, y, z);
    }
    void play_crime_report_for_player (int player_id, int suspect_id, int crime_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/play_crime_report_for_player, /*p*/player_id SEPARATOR  suspect_id SEPARATOR  crime_id);
        play_crime_report_for_player_t.call(player_id, suspect_id, crime_id);
    }
    void set_player_shop_name (int player_id, std::string const& shop_name) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_shop_name, /*p*/player_id SEPARATOR  shop_name);
        set_player_shop_name_t.call(player_id, shop_name);
    }
    void set_player_skill_level (int player_id, weapon_skill skill, int level) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_skill_level, /*p*/player_id SEPARATOR  skill SEPARATOR  level);
        set_player_skill_level_t.call(player_id, skill, level);
    }
    int get_player_surfing_vehicle_id (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_surfing_vehicle_id, /*p*/player_id);
        return get_player_surfing_vehicle_id_t.call(player_id);
    }
#ifdef _03B
    void set_player_holding_object (int player_id, int model_id, bones bone_id, float offset_x, float offset_y, float offset_z, float rx, float ry, float rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_holding_object, /*p*/player_id SEPARATOR  model_id SEPARATOR  bone_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
        set_player_holding_object_t.call(player_id, model_id, bone_id, offset_x, offset_y, offset_z, rx, ry, rz);
    }
    void stop_player_holding_object (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/stop_player_holding_object, /*p*/player_id);
        stop_player_holding_object_t.call(player_id);
    }
    bool is_player_holding_object (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_holding_object, /*p*/player_id);
        return 0 != is_player_holding_object_t.call(player_id);
    }
#endif
#ifdef _03C
    void set_player_attached_object (int player_id, int index, int model_id, bones bone_id, float offset_x, float offset_y, float offset_z, float rx, float ry, float rz, float sx, float sy, float sz) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_attached_object, 
		     /*p*/player_id SEPARATOR index SEPARATOR model_id SEPARATOR  bone_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz SEPARATOR sx SEPARATOR  sy SEPARATOR  sz);
        set_player_attached_object_t.call(player_id,index model_id, bone_id, offset_x, offset_y, offset_z, rx, ry, rz, sx, sy, sz);
    }
    void remove_player_attached_object (int player_id, int index) 
    {
        START();
        DEBUG_NATIVE(/*f*/remove_player_attached_object, /*p*/player_id SEPARATOR index);
        remove_player_attached_object_t.call(player_id);
    }
    bool is_player_attached_object_slot_used (int player_id, int index) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_attached_object_slot_used_t, /*p*/player_id SEPARATOR index);
        return 0 != is_player_attached_object_slot_used_t.call(player_id);
    }
    void attach_object_to_vehicle (int vehicle_id, int model_id, float offset_x, float offset_y, float offset_z, float rx, float ry, float rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/attach_object_to_vehicle, 
		     /*p*/player_id SEPARATOR index SEPARATOR model_id SEPARATOR  bone_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z SEPARATOR  rx SEPARATOR  ry SEPARATOR  rz);
        attach_object_to_vehicle_t.call(player_id,index model_id, bone_id, offset_x, offset_y, offset_z, rx, ry, rz, sx, sy, sz);
    }
#endif


    void set_player_chat_bubble (int player_id, std::string const& text, unsigned int color, float draw_distance, int expire_time) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_chat_bubble, /*p*/player_id SEPARATOR  text SEPARATOR  color SEPARATOR  draw_distance SEPARATOR  expire_time);
        set_player_chat_bubble_t.call(player_id, text, color, draw_distance, expire_time);
    }

    // Player controls
    void put_player_in_vehicle (int player_id, int vehicle_id, int seat_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/put_player_in_vehicle, /*p*/player_id SEPARATOR  vehicle_id SEPARATOR  seat_id);
        put_player_in_vehicle_t.call(player_id, vehicle_id, seat_id);
    }
    int get_player_vehicle_id (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_vehicle_id, /*p*/player_id);
        return get_player_vehicle_id_t.call(player_id);
    }
    int get_player_vehicle_seat (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_vehicle_seat, /*p*/player_id);
        return get_player_vehicle_seat_t.call(player_id);
    }
    void remove_player_from_vehicle (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/remove_player_from_vehicle, /*p*/player_id);
        remove_player_from_vehicle_t.call(player_id);
    }
    void toggle_player_controllable (int player_id, bool is_unfreeze) 
    {
        START();
        DEBUG_NATIVE(/*f*/toggle_player_controllable, /*p*/player_id SEPARATOR  is_unfreeze);
        toggle_player_controllable_t.call(player_id, is_unfreeze);
    }
    void player_play_sound (int player_id, int sound_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/player_play_sound, /*p*/player_id SEPARATOR  sound_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        player_play_sound_t.call(player_id, sound_id, x, y, z);
    }
    void apply_animation (int player_id, std::string const& anim_lib, std::string const& anim_name, float delta, int loop, int lock_x, int lock_y, int freeze, int time, int forcesync) 
    {
        START();
        DEBUG_NATIVE(/*f*/apply_animation, /*p*/player_id SEPARATOR  anim_lib SEPARATOR  anim_name SEPARATOR  delta SEPARATOR  loop SEPARATOR  lock_x SEPARATOR  lock_y SEPARATOR  freeze SEPARATOR  time SEPARATOR  forcesync);
        apply_animation_t.call(player_id, anim_lib, anim_name, delta, loop, lock_x, lock_y, freeze, time, forcesync);
    }
    void clear_animations (int player_id, int forcesync) 
    {
        START();
        DEBUG_NATIVE(/*f*/clear_animations, /*p*/player_id SEPARATOR  forcesync);
        clear_animations_t.call(player_id, forcesync);
    }
    int get_player_animation_index (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_animation_index, /*p*/player_id);
        return get_player_animation_index_t.call(player_id);
    }
    void get_animation_name (int index, std::string& anim_lib, std::string& anim_name) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_animation_name, /*p*/index SEPARATOR  anim_lib SEPARATOR  pawn::string_len::val SEPARATOR  anim_name SEPARATOR  pawn::string_len::val);
        get_animation_name_t.call(index, anim_lib, pawn::string_len::val, anim_name, pawn::string_len::val);
    }
    special_action get_player_special_action (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_special_action, /*p*/player_id);
        return static_cast<special_action>(get_player_special_action_t.call(player_id));
    }
    void set_player_special_action (int player_id, special_action action_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_special_action, /*p*/player_id SEPARATOR  action_id);
        set_player_special_action_t.call(player_id, action_id);
    }

    // Player world/map related
    void set_player_checkpoint (int player_id, float x, float y, float z, float size) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_checkpoint, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  size);
        set_player_checkpoint_t.call(player_id, x, y, z, size);
    }
    void disable_player_checkpoint (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/disable_player_checkpoint, /*p*/player_id);
        disable_player_checkpoint_t.call(player_id);
    }
    void set_player_race_checkpoint (int player_id, int type_id, float x, float y, float z, float next_x, float next_y, float next_z, float size) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_race_checkpoint, /*p*/player_id SEPARATOR  type_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  next_x SEPARATOR  next_y SEPARATOR  next_z SEPARATOR  size);
        set_player_race_checkpoint_t.call(player_id, type_id, x, y, z, next_x, next_y, next_z, size);
    }
    void disable_player_race_checkpoint (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/disable_player_race_checkpoint, /*p*/player_id);
        disable_player_race_checkpoint_t.call(player_id);
    }
    void set_player_world_bounds (int player_id, float x_max, float x_min, float y_max, float y_min) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_world_bounds, /*p*/player_id SEPARATOR  x_max SEPARATOR  x_min SEPARATOR  y_max SEPARATOR  y_min);
        set_player_world_bounds_t.call(player_id, x_max, x_min, y_max, y_min);
    }
    void set_player_marker_for_player (int player_id, int show_player_id, unsigned color) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_marker_for_player, /*p*/player_id SEPARATOR  show_player_id SEPARATOR  color);
        set_player_marker_for_player_t.call(player_id, show_player_id, color);
    }
    void show_player_name_tag_for_player (int player_id, int show_player_id, bool show) 
    {
        START();
        DEBUG_NATIVE(/*f*/show_player_name_tag_for_player, /*p*/player_id SEPARATOR  show_player_id SEPARATOR  show);
        show_player_name_tag_for_player_t.call(player_id, show_player_id, show);
    }
    void set_player_mapicon (int player_id, int icon_id, float x, float y, float z, int markertype, unsigned color) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_mapicon, /*p*/player_id SEPARATOR  icon_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  markertype SEPARATOR  color);
        set_player_mapicon_t.call(player_id, icon_id, x, y, z, markertype, color);
    }
    void remove_player_mapicon (int player_id, int icon_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/remove_player_mapicon, /*p*/player_id SEPARATOR  icon_id);
        remove_player_mapicon_t.call(player_id, icon_id);
    }
    void allow_player_teleport (int player_id, bool allow) 
    {
        START();
        DEBUG_NATIVE(/*f*/allow_player_teleport, /*p*/player_id SEPARATOR  allow);
        allow_player_teleport_t.call(player_id, allow);
    }
    
    // Player camera
    void set_player_camera_pos (int player_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_camera_pos, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_player_camera_pos_t.call(player_id, x, y, z);
    }
    void set_player_camera_look_at (int player_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_camera_look_at, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_player_camera_look_at_t.call(player_id, x, y, z);
    }
    void set_camera_behind_player (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_camera_behind_player, /*p*/player_id);
        set_camera_behind_player_t.call(player_id);
    }
    void get_player_camera_pos (int player_id, float& x, float& y, float& z) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_camera_pos, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        get_player_camera_pos_t.call(player_id, x, y, z);
    }

    void get_player_camera_front_vector (int player_id, float& x, float& y, float& z) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_camera_front_vector, /*p*/player_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        get_player_camera_front_vector_t.call(player_id, x, y, z);
    }

    // Player conditionals
    bool is_player_connected (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_connected, /*p*/player_id);
        return 0 != is_player_called_t.call(player_id);
    }
    bool is_player_in_vehicle (int player_id, int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_in_vehicle, /*p*/player_id SEPARATOR  vehicle_id);
        return 0 != is_player_in_vehicle_t.call(player_id, vehicle_id);
    }
    bool is_player_in_any_vehicle (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_in_any_vehicle, /*p*/player_id);
        return 0 != is_player_in_any_vehicle_t.call(player_id);
    }
    bool is_player_in_checkpoint (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_in_checkpoint, /*p*/player_id);
        return 0 != is_player_in_checkpoint_t.call(player_id);
    }
    bool is_player_in_race_checkpoint (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_in_race_checkpoint, /*p*/player_id);
        return 0 != is_player_in_race_checkpoint_t.call(player_id);
    }

    // Virtual Worlds
    void set_player_virtual_world (int player_id, int world_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_player_virtual_world, /*p*/player_id SEPARATOR  world_id);
        set_player_virtual_world_t.call(player_id, world_id);
    }
    int get_player_virtual_world (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_virtual_world, /*p*/player_id);
        return get_player_virtual_world_t.call(player_id);
    }

    // Insane Stunts
    void enable_stunt_bonus_for_player (int player_id, bool enable) 
    {
        START();
        DEBUG_NATIVE(/*f*/enable_stunt_bonus_for_player, /*p*/player_id SEPARATOR  enable);
        enable_stunt_bonus_for_player_t.call(player_id, enable);
    }
    void enable_stunt_bonus_for_all (bool enable) 
    {
        START();
        DEBUG_NATIVE(/*f*/enable_stunt_bonus_for_all, /*p*/enable);
        enable_stunt_bonus_for_all_t.call(enable);
    }

    // Spectating
    void toggle_player_spectating (int player_id, bool toggle) 
    {
        START();
        DEBUG_NATIVE(/*f*/toggle_player_spectating, /*p*/player_id SEPARATOR  toggle);
        toggle_player_spectating_t.call(player_id, toggle);
    }
    void player_spectate_player (int player_id, int target_player_id, spectate_mode mode) 
    {
        START();
        DEBUG_NATIVE(/*f*/player_spectate_player, /*p*/player_id SEPARATOR  target_player_id SEPARATOR  mode);
        player_spectate_player_t.call(player_id, target_player_id, mode);
    }
    void player_spectate_vehicle (int player_id, int target_vehicle_id, spectate_mode mode) 
    {
        START();
        DEBUG_NATIVE(/*f*/player_spectate_vehicle, /*p*/player_id SEPARATOR  target_vehicle_id SEPARATOR  mode);
        player_spectate_vehicle_t.call(player_id, target_vehicle_id, mode);
    }
    
    // Recording for NPC playback
    void start_recording_player_data (int player_id, player_recording_type record_type, std::string const& record_name) 
    {
        START();
        DEBUG_NATIVE(/*f*/start_recording_player_data, /*p*/player_id SEPARATOR  record_type SEPARATOR  record_name);
        start_recording_player_data_t.call(player_id, record_type, record_name);
    }
    void stop_recording_player_data (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/stop_recording_player_data, /*p*/player_id);
        stop_recording_player_data_t.call(player_id);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_samp.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Util
    void send_client_message (int player_id, unsigned color, std::string const& message) 
    {
        START();
        DEBUG_NATIVE(/*f*/send_client_message, /*p*/player_id SEPARATOR  color SEPARATOR  message);
        send_client_message_t.call(player_id, color, message);
    }
    void send_player_message_to_player (int player_id, int sender_id, std::string const& message) 
    {
        START();
        DEBUG_NATIVE(/*f*/send_player_message_to_player, /*p*/player_id SEPARATOR  sender_id SEPARATOR  message);
        send_player_message_to_player_t.call(player_id, sender_id, message);
    }
    void send_death_message (int killer_id, int killed_id, int weapon_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/send_death_message, /*p*/killer_id SEPARATOR  killed_id SEPARATOR  weapon_id);
        send_death_message_t.call(killer_id, killed_id, weapon_id);
    }
    void game_text_for_player (int player_id, std::string const& string, int time, int style) 
    {
        START();
        DEBUG_NATIVE(/*f*/game_text_for_player, /*p*/player_id SEPARATOR  string SEPARATOR  time SEPARATOR  style);
        game_text_for_player_t.call(player_id, string, time, style);
    }
    int get_max_players () 
    {
        START();
        DEBUG_NATIVE(/*f*/get_max_players, /*p*/"");
        return get_max_players_t.call();
    }

    // Game
    void set_game_mode_text (std::string const& text) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_game_mode_text, /*p*/text);
        set_game_mode_text_t.call(text);
    }
    void set_team_count (int count) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_team_count, /*p*/count);
        set_team_count_t.call(count);
    }
    int add_player_class (int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3) 
    {
        START();
        DEBUG_NATIVE(/*f*/add_player_class, /*p*/skin_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  weapon_id1 SEPARATOR  weapon_ammo1 SEPARATOR  weapon_id2 SEPARATOR  weapon_ammo2 SEPARATOR  weapon_id3 SEPARATOR  weapon_ammo3);
        return add_player_class_t.call(skin_id, x, y, z, rz, weapon_id1, weapon_ammo1, weapon_id2, weapon_ammo2, weapon_id3, weapon_ammo3);
    }
    int add_player_class_ex (int team_id, int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3) 
    {
        START();
        DEBUG_NATIVE(/*f*/add_player_class_ex, /*p*/team_id SEPARATOR  skin_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  weapon_id1 SEPARATOR  weapon_ammo1 SEPARATOR  weapon_id2 SEPARATOR  weapon_ammo2 SEPARATOR  weapon_id3 SEPARATOR  weapon_ammo3);
        return add_player_class_ex_t.call(team_id, skin_id, x, y, z, rz, weapon_id1, weapon_ammo1, weapon_id2, weapon_ammo2, weapon_id3, weapon_ammo3);
    }
    void add_static_vehicle (int model_id, float x, float y, float z, float rz, int color_id1, int color_id2) 
    {
        START();
        DEBUG_NATIVE(/*f*/add_static_vehicle, /*p*/model_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  color_id1 SEPARATOR  color_id2);
        add_static_vehicle_t.call(model_id, x, y, z, rz, color_id1, color_id2);
    }
    int add_static_vehicle_ex (int model_id, float x, float y, float z, float rz, int color_id1, int color_id2, int respawn_delay) 
    {
        START();
        DEBUG_NATIVE(/*f*/add_static_vehicle_ex, /*p*/model_id SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  color_id1 SEPARATOR  color_id2 SEPARATOR  respawn_delay);
        return add_static_vehicle_ex_t.call(model_id, x, y, z, rz, color_id1, color_id2, respawn_delay);
    }
    void add_static_pickup (int model_id, int type, float x, float y, float z, int virtual_world) 
    {
        START();
        DEBUG_NATIVE(/*f*/add_static_pickup, /*p*/model_id SEPARATOR  type SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  virtual_world);
        add_static_pickup_t.call(model_id, type, x, y, z, virtual_world);
    }
    int create_pickup (int model_id, int type, float x, float y, float z, int virtual_world) 
    {
        START();
        DEBUG_NATIVE(/*f*/create_pickup, /*p*/model_id SEPARATOR  type SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  virtual_world);
        return create_pickup_t.call(model_id, type, x, y, z, virtual_world);
    }
    void destroy_pickup (int pickup_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/destroy_pickup, /*p*/pickup_id);
        destroy_pickup_t.call(pickup_id);
    }
    void show_name_tags (bool is_show) 
    {
        START();
        DEBUG_NATIVE(/*f*/show_name_tags, /*p*/is_show);
        show_name_tags_t.call(is_show);
    }
    void show_player_markers (player_markers_mode mode) 
    {
        START();
        DEBUG_NATIVE(/*f*/show_player_markers, /*p*/mode);
        show_player_markers_t.call(mode);
    }
    void gamemode_exit () 
    {
        START();
        DEBUG_NATIVE(/*f*/gamemode_exit, /*p*/"");
        gamemode_exit_t.call();
    }
    void set_world_time (int hour) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_world_time, /*p*/hour);
        set_world_time_t.call(hour);
    }
    std::string get_weapon_name (int weapon_id) 
    {
        START();
        std::string rezult;
        DEBUG_NATIVE(/*f*/get_weapon_name, /*p*/weapon_id SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        get_weapon_name_t.call(weapon_id, rezult, pawn::string_len::val);
        return rezult;
    }
    void enable_tire_popping (bool is_enable) 
    {
        START();
        DEBUG_NATIVE(/*f*/enable_tire_popping, /*p*/is_enable);
        enable_tire_popping_t.call(is_enable);
    }
    void allow_interior_weapons (bool is_allow) 
    {
        START();
        DEBUG_NATIVE(/*f*/allow_interior_weapons, /*p*/is_allow);
        allow_interior_weapons_t.call(is_allow);
    }
    void set_weather (int weather_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_weather, /*p*/weather_id);
        set_weather_t.call(weather_id);
    }
    void set_gravity (float gravity) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_gravity, /*p*/gravity);
        set_gravity_t.call(gravity);
    }
    void allow_admin_teleport (bool is_allow) 
    {
        START();
        DEBUG_NATIVE(/*f*/allow_admin_teleport, /*p*/is_allow);
        allow_admin_teleport_t.call(is_allow);
    }
    void set_death_drop_amount (int amount) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_death_drop_amount, /*p*/amount);
        set_death_drop_amount_t.call(amount);
    }
    void create_explosion (float x, float y, float z, int type, float radius) 
    {
        START();
        DEBUG_NATIVE(/*f*/create_explosion, /*p*/x SEPARATOR  y SEPARATOR  z SEPARATOR  type SEPARATOR  radius);
        create_explosion_t.call(x, y, z, type, radius);
    }
    void enable_zone_names (bool is_enable) 
    {
        START();
        DEBUG_NATIVE(/*f*/enable_zone_names, /*p*/is_enable);
        enable_zone_names_t.call(is_enable);
    }
    void use_player_ped_anims () 
    {
        START();
        DEBUG_NATIVE(/*f*/use_player_ped_anims, /*p*/"");
        use_player_ped_anims_t.call();
    }
    void disable_interior_enter_exits () 
    {
        START();
        DEBUG_NATIVE(/*f*/disable_interior_enter_exits, /*p*/"");
        disable_interior_enter_exits_t.call();
    }
    void set_name_tag_draw_distance (float distance) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_name_tag_draw_distance, /*p*/distance);
        set_name_tag_draw_distance_t.call(distance);
    }
    void disable_name_tag_los () 
    {
        START();
        DEBUG_NATIVE(/*f*/disable_name_tag_los, /*p*/"");
        disable_name_tag_los_t.call();
    }
    void limit_global_chat_radius (float chat_radius) 
    {
        START();
        DEBUG_NATIVE(/*f*/limit_global_chat_radius, /*p*/chat_radius);
        limit_global_chat_radius_t.call(chat_radius);
    }
    void limit_player_marker_radius (float marker_radius) 
    {
        START();
        DEBUG_NATIVE(/*f*/limit_player_marker_radius, /*p*/marker_radius);
        limit_player_marker_radius_t.call(marker_radius);
    }

    // Npc
    void connect_npc (std::string const& name, std::string const& script) 
    {
        START();
        DEBUG_NATIVE(/*f*/connect_npc, /*p*/name SEPARATOR  script);
        call_npc_t.call(name, script);
    }
    bool is_player_npc (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_npc, /*p*/player_id);
        return 0 != is_player_npc_t.call(player_id);
    }

    // Admin
    bool is_player_admin (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_player_admin, /*p*/player_id);
        return 0 != is_player_admin_t.call(player_id);
    }
    void kick (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/kick, /*p*/player_id);
        kick_t.call(player_id);
    }
    void ban (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/ban, /*p*/player_id);
        ban_t.call(player_id);
    }
    void ban_ex (int player_id, std::string const& reason) 
    {
        START();
        DEBUG_NATIVE(/*f*/ban_ex, /*p*/player_id SEPARATOR  reason);
        ban_ex_t.call(player_id, reason);
    }
    void send_rcon_command (std::string const& command) 
    {
        START();
        DEBUG_NATIVE(/*f*/send_rcon_command, /*p*/command);
        send_rcon_command_t.call(command);
    }
    std::string get_server_var_as_string (std::string const& var_name) 
    {
        START();
        std::string rezult;
        DEBUG_NATIVE(/*f*/get_server_var_as_string, /*p*/var_name SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        get_server_var_as_string_t.call(var_name, rezult, pawn::string_len::val);
        return rezult;
    }
    int get_server_var_as_int (std::string const& var_name) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_server_var_as_int, /*p*/var_name);
        return get_server_var_as_int_t.call(var_name);
    }
    bool get_server_var_as_bool (std::string const& var_name) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_server_var_as_bool, /*p*/var_name);
        return 0 != get_server_var_as_bool_t.call(var_name);
    }

    // Menu
    int create_menu (std::string const& title, int columns, float x, float y, float col1width, float col2width) 
    {
        START();
        DEBUG_NATIVE(/*f*/create_menu, /*p*/title SEPARATOR  columns SEPARATOR  x SEPARATOR  y SEPARATOR  col1width SEPARATOR  col2width);
        return create_menu_t.call(title, columns, x, y, col1width, col2width);
    }
    void destroy_menu (int menu_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/destroy_menu, /*p*/menu_id);
        destroy_menu_t.call(menu_id);
    }
    void add_menu_item (int menu_id, int column, std::string const& text) 
    {
        START();
        DEBUG_NATIVE(/*f*/add_menu_item, /*p*/menu_id SEPARATOR  column SEPARATOR  text);
        add_menu_item_t.call(menu_id, column, text);
    }
    void set_menu_column_header (int menu_id, int column, std::string const& header) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_menu_column_header, /*p*/menu_id SEPARATOR  column SEPARATOR  header);
        set_menu_column_header_t.call(menu_id, column, header);
    }
    void show_menu_for_player (int menu_id, int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/show_menu_for_player, /*p*/menu_id SEPARATOR  player_id);
        show_menu_for_player_t.call(menu_id, player_id);
    }
    void hide_menu_for_player (int menu_id, int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/hide_menu_for_player, /*p*/menu_id SEPARATOR  player_id);
        hide_menu_for_player_t.call(menu_id, player_id);
    }
    bool is_valid_menu (int menu_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_valid_menu, /*p*/menu_id);
        return 0 != is_valid_menu_t.call(menu_id);
    }
    void disable_menu (int menu_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/disable_menu, /*p*/menu_id);
        disable_menu_t.call(menu_id);
    }
    void disable_menu_row (int menu_id, int row) 
    {
        START();
        DEBUG_NATIVE(/*f*/disable_menu_row, /*p*/menu_id SEPARATOR  row);
        disable_menu_row_t.call(menu_id, row);
    }
    int get_player_menu (int player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_player_menu, /*p*/player_id);
        return get_player_menu_t.call(player_id);
    }

    // Text Draw
    int textdraw_create (float x, float y, std::string const& text) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_create, /*p*/x SEPARATOR  y SEPARATOR  text);
        return textdraw_create_t.call(x, y, text);
    }
    void textdraw_destroy (int text_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_destroy, /*p*/text_id);
        textdraw_destroy_t.call(text_id);
    }
    void textdraw_letter_size (int text_id, float x, float y) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_letter_size, /*p*/text_id SEPARATOR  x SEPARATOR  y);
        textdraw_letter_size_t.call(text_id, x, y);
    }
    void textdraw_text_size (int text_id, float x, float y) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_text_size, /*p*/text_id SEPARATOR  x SEPARATOR  y);
        textdraw_text_size_t.call(text_id, x, y);
    }
    void textdraw_alignment (int text_id, int alignment) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_alignment, /*p*/text_id SEPARATOR  alignment);
        textdraw_alignment_t.call(text_id, alignment);
    }
    void textdraw_color (int text_id, unsigned color) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_color, /*p*/text_id SEPARATOR  color);
        textdraw_color_t.call(text_id, color);
    }
    void textdraw_use_box (int text_id, int use) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_use_box, /*p*/text_id SEPARATOR  use);
        textdraw_use_box_t.call(text_id, use);
    }
    void textdraw_box_color (int text_id, unsigned color) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_box_color, /*p*/text_id SEPARATOR  color);
        textdraw_box_color_t.call(text_id, color);
    }
    void textdraw_set_shadow (int text_id, int size) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_set_shadow, /*p*/text_id SEPARATOR  size);
        textdraw_set_shadow_t.call(text_id, size);
    }
    void textdraw_set_outline (int text_id, int size) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_set_outline, /*p*/text_id SEPARATOR  size);
        textdraw_set_outline_t.call(text_id, size);
    }
    void textdraw_background_color (int text_id, unsigned color) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_background_color, /*p*/text_id SEPARATOR  color);
        textdraw_background_color_t.call(text_id, color);
    }
    void textdraw_font (int text_id, int font) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_font, /*p*/text_id SEPARATOR  font);
        textdraw_font_t.call(text_id, font);
    }
    void textdraw_set_proportional (int text_id, bool set) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_set_proportional, /*p*/text_id SEPARATOR  set);
        textdraw_set_proportional_t.call(text_id, set);
    }
    void textdraw_show_for_player (int player_id, int text_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_show_for_player, /*p*/player_id SEPARATOR  text_id);
        textdraw_show_for_player_t.call(player_id, text_id);
    }
    void textdraw_hide_for_player (int player_id, int text_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_hide_for_player, /*p*/player_id SEPARATOR  text_id);
        textdraw_hide_for_player_t.call(player_id, text_id);
    }
    void textdraw_set_string (int text_id, std::string const& text) 
    {
        START();
        DEBUG_NATIVE(/*f*/textdraw_set_string, /*p*/text_id SEPARATOR  text);
        textdraw_set_string_t.call(text_id, text);
    }

    // Gang Zones
    int gangzone_create (float minx, float miny, float maxx, float maxy) 
    {
        START();
        DEBUG_NATIVE(/*f*/gangzone_create, /*p*/minx SEPARATOR  miny SEPARATOR  maxx SEPARATOR  maxy);
        return gangzone_create_t.call(minx, miny, maxx, maxy);
    }
    void gangzone_destroy (int zone_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/gangzone_destroy, /*p*/zone_id);
        gangzone_destroy_t.call(zone_id);
    }
    void gangzone_show_for_player (int player_id, int zone_id, unsigned int color) 
    {
        START();
        DEBUG_NATIVE(/*f*/gangzone_show_for_player, /*p*/player_id SEPARATOR  zone_id SEPARATOR  color);
        gangzone_show_for_player_t.call(player_id, zone_id, color);
    }
    void gangzone_hide_for_player (int player_id, int zone_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/gangzone_hide_for_player, /*p*/player_id SEPARATOR  zone_id);
        gangzone_hide_for_player_t.call(player_id, zone_id);
    }
    void gangzone_flash_for_player (int player_id, int zone_id, unsigned int flashcolor) 
    {
        START();
        DEBUG_NATIVE(/*f*/gangzone_flash_for_player, /*p*/player_id SEPARATOR  zone_id SEPARATOR  flashcolor);
        gangzone_flash_for_player_t.call(player_id, zone_id, flashcolor);
    }
    void gangzone_stop_flash_for_player (int player_id, int zone_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/gangzone_stop_flash_for_player, /*p*/player_id SEPARATOR  zone_id);
        gangzone_stop_flash_for_player_t.call(player_id, zone_id);
    }

    // Global 3D Text Labels
    int create_3dtextlabel (std::string const& text, unsigned int color, float x, float y, float z, float draw_distance, int world, bool is_test_los) 
    {
        START();
        DEBUG_NATIVE(/*f*/create_3dtextlabel, /*p*/text SEPARATOR  color SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  draw_distance SEPARATOR  world SEPARATOR  is_test_los);
        return create_3dtextlabel_t.call(text, color, x, y, z, draw_distance, world, is_test_los);
    }
    void delete_3dtextlabel (int text3d_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/delete_3dtextlabel, /*p*/text3d_id);
        delete_3dtextlabel_t.call(text3d_id);
    }
    void attach_3dtextlabel_to_player (int text3d_id, int player_id, float offset_x, float offset_y, float offset_z) 
    {
        START();
        DEBUG_NATIVE(/*f*/attach_3dtextlabel_to_player, /*p*/text3d_id SEPARATOR  player_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z);
        attach_3dtextlabel_to_player_t.call(text3d_id, player_id, offset_x, offset_y, offset_z);
    }
    void attach_3dtextlabel_to_vehicle (int text3d_id, int vehicle_id, float offset_x, float offset_y, float offset_z) 
    {
        START();
        DEBUG_NATIVE(/*f*/attach_3dtextlabel_to_vehicle, /*p*/text3d_id SEPARATOR  vehicle_id SEPARATOR  offset_x SEPARATOR  offset_y SEPARATOR  offset_z);
        attach_3dtextlabel_to_vehicle_t.call(text3d_id, vehicle_id, offset_x, offset_y, offset_z);
    }
    void update_3dtextlabel_text (int text3d_id, unsigned int color, std::string const& text) 
    {
        START();
        DEBUG_NATIVE(/*f*/update_3dtextlabel_text, /*p*/text3d_id SEPARATOR  color SEPARATOR  text);
        update_3dtextlabel_text_t.call(text3d_id, color, text);
    }

    // Per-player 3D Text Labels
    int create_player3dtextlabel (int player_id, std::string const& text, unsigned int color, float x, float y, float z, float draw_distance, int attached_player_id, int attached_vehicle_id, bool is_test_los) 
    {
        START();
        DEBUG_NATIVE(/*f*/create_player3dtextlabel, /*p*/player_id SEPARATOR  text SEPARATOR  color SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  draw_distance SEPARATOR  attached_player_id SEPARATOR  attached_vehicle_id SEPARATOR  is_test_los);
        return create_player3dtextlabel_t.call(player_id, text, color, x, y, z, draw_distance, attached_player_id, attached_vehicle_id, is_test_los);
    }
    void delete_player3dtextlabel (int player_id, int playertext3d_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/delete_player3dtextlabel, /*p*/player_id SEPARATOR  playertext3d_id);
        delete_player3dtextlabel_t.call(player_id, playertext3d_id);
    }
    void update_player3dtextlabel_text (int player_id, int playertext3d_id, unsigned int color, std::string const& text) 
    {
        START();
        DEBUG_NATIVE(/*f*/update_player3dtextlabel_text, /*p*/player_id SEPARATOR  playertext3d_id SEPARATOR  color SEPARATOR  text);
        update_player3dtextlabel_text_t.call(player_id, playertext3d_id, color, text);
    }

    // Player GUI Dialog
    void show_player_dialog (int player_id, int dialog_id, dialog_style style, std::string const& caption, std::string const& info, std::string const& button_ok, std::string const& button_cancel) 
    {
        START();
        DEBUG_NATIVE(/*f*/show_player_dialog, /*p*/player_id SEPARATOR  dialog_id SEPARATOR  style SEPARATOR  caption SEPARATOR  info SEPARATOR  button_ok SEPARATOR  button_cancel);
        show_player_dialog_t.call(player_id, dialog_id, style, caption, info, button_ok, button_cancel);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // a_vehicles.inc
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Vehicle
    int create_vehicle (int vehicle_model, float x, float y, float z, float rz, int color_id1, int color_id2, int respawn_delay) 
    {
        START();
        DEBUG_NATIVE(/*f*/create_vehicle, /*p*/vehicle_model SEPARATOR  x SEPARATOR  y SEPARATOR  z SEPARATOR  rz SEPARATOR  color_id1 SEPARATOR  color_id2 SEPARATOR  respawn_delay);
        return create_vehicle_t.call(vehicle_model, x, y, z, rz, color_id1, color_id2, respawn_delay);
    }
    void destroy_vehicle (int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/destroy_vehicle, /*p*/vehicle_id);
        destroy_vehicle_t.call(vehicle_id);
    }
    bool is_vehicle_streamed_in (int vehicle_id, int for_player_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_vehicle_streamed_in, /*p*/vehicle_id SEPARATOR  for_player_id);
        return 0 != is_vehicle_streamed_in_t.call(vehicle_id, for_player_id);
    }
    void get_vehicle_pos (int vehicle_id, float& x, float& y, float& z) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_vehicle_pos, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        get_vehicle_pos_t.call(vehicle_id, x, y, z);
    }
    void set_vehicle_pos (int vehicle_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_vehicle_pos, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_vehicle_pos_t.call(vehicle_id, x, y, z);
    }
    float get_vehicle_zangle (int vehicle_id) 
    {
        START();
        float rz;
        DEBUG_NATIVE(/*f*/get_vehicle_zangle, /*p*/vehicle_id SEPARATOR  rz);
        get_vehicle_zangle_t.call(vehicle_id, rz);
        return rz;
    }
    void get_vehicle_rotation_quat (int vehicle_id, float& w, float& x, float& y, float& z) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_vehicle_rotation_quat, /*p*/vehicle_id SEPARATOR  w SEPARATOR  x SEPARATOR  y SEPARATOR  x);
        get_vehicle_rotation_quat_t.call(vehicle_id, w, x, y, x);
    }
    void set_vehicle_zangle (int vehicle_id, float rz) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_vehicle_zangle, /*p*/vehicle_id SEPARATOR  rz);
        set_vehicle_zangle_t.call(vehicle_id, rz);
    }
    void set_vehicle_params_for_player (int vehicle_id, int player_id, bool objective, bool doorslocked) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_vehicle_params_for_player, /*p*/vehicle_id SEPARATOR  player_id SEPARATOR  objective SEPARATOR  doorslocked);
        set_vehicle_params_for_player_t.call(vehicle_id, player_id, objective, doorslocked);
    }
    void set_vehicle_to_respawn (int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_vehicle_to_respawn, /*p*/vehicle_id);
        set_vehicle_to_respawn_t.call(vehicle_id);
    }
    void link_vehicle_to_interior (int vehicle_id, int interior_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/link_vehicle_to_interior, /*p*/vehicle_id SEPARATOR  interior_id);
        link_vehicle_to_interior_t.call(vehicle_id, interior_id);
    }
    void add_vehicle_component (int vehicle_id, int component_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/add_vehicle_component, /*p*/vehicle_id SEPARATOR  component_id);
        add_vehicle_component_t.call(vehicle_id, component_id);
    }
    void remove_vehicle_component (int vehicle_id, int component_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/remove_vehicle_component, /*p*/vehicle_id SEPARATOR  component_id);
        remove_vehicle_component_t.call(vehicle_id, component_id);
    }
    void change_vehicle_color (int vehicle_id, int color_id1, int color_id2) 
    {
        START();
        DEBUG_NATIVE(/*f*/change_vehicle_color, /*p*/vehicle_id SEPARATOR  color_id1 SEPARATOR  color_id2);
        change_vehicle_color_t.call(vehicle_id, color_id1, color_id2);
    }
    void change_vehicle_paintjob (int vehicle_id, int paintjob_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/change_vehicle_paintjob, /*p*/vehicle_id SEPARATOR  paintjob_id);
        change_vehicle_paintjob_t.call(vehicle_id, paintjob_id);
    }
    void set_vehicle_health (int vehicle_id, float health) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_vehicle_health, /*p*/vehicle_id SEPARATOR  health);
        set_vehicle_health_t.call(vehicle_id, health);
    }
    float get_vehicle_health (int vehicle_id) 
    {
        START();
        float health;
        DEBUG_NATIVE(/*f*/get_vehicle_health, /*p*/vehicle_id SEPARATOR  health);
        get_vehicle_health_t.call(vehicle_id, health);
        return health;
    }
    void attach_trailer_to_vehicle (int trailer_id, int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/attach_trailer_to_vehicle, /*p*/trailer_id SEPARATOR  vehicle_id);
        attach_trailer_to_vehicle_t.call(trailer_id, vehicle_id);
    }
    void detach_trailer_from_vehicle (int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/detach_trailer_from_vehicle, /*p*/vehicle_id);
        detach_trailer_from_vehicle_t.call(vehicle_id);
    }
    bool is_trailer_attached_to_vehicle (int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/is_trailer_attached_to_vehicle, /*p*/vehicle_id);
        return 0 != is_trailer_attached_to_vehicle_t.call(vehicle_id);
    }
    int get_vehicle_trailer (int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_vehicle_trailer, /*p*/vehicle_id);
        return get_vehicle_trailer_t.call(vehicle_id);
    }
    void set_vehicle_number_plate (int vehicle_id, std::string const& numberplate) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_vehicle_number_plate, /*p*/vehicle_id SEPARATOR  numberplate);
        set_vehicle_number_plate_t.call(vehicle_id, numberplate);
    }
    int get_vehicle_model (int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_vehicle_model, /*p*/vehicle_id);
        return get_vehicle_model_t.call(vehicle_id);
    }
    int get_vehicle_component_in_slot (int vehicle_id, carmod_type slot) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_vehicle_component_in_slot, /*p*/vehicle_id SEPARATOR  slot);
        return get_vehicle_component_in_slot_t.call(vehicle_id, slot);
    }
    carmod_type get_vehicle_component_type (int component_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_vehicle_component_type, /*p*/component_id);
        return static_cast<carmod_type>(get_vehicle_component_type_t.call(component_id));
    }
    void repair_vehicle (int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/repair_vehicle, /*p*/vehicle_id);
        repair_vehicle_t.call(vehicle_id);
    }
    void get_vehicle_velocity (int vehicle_id, float& x, float& y, float& z) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_vehicle_velocity, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        get_vehicle_velocity_t.call(vehicle_id, x, y, z);
    }
    void set_vehicle_velocity (int vehicle_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_vehicle_velocity, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_vehicle_velocity_t.call(vehicle_id, x, y, z);
    }
    void set_vehicle_angular_velocity (int vehicle_id, float x, float y, float z) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_vehicle_angular_velocity, /*p*/vehicle_id SEPARATOR  x SEPARATOR  y SEPARATOR  z);
        set_vehicle_angular_velocity_t.call(vehicle_id, x, y, z);
    }
    void get_vehicle_damage_status (int vehicle_id, int& panels, int& doors, int& lights, int& tires) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_vehicle_damage_status, /*p*/vehicle_id SEPARATOR  panels SEPARATOR  doors SEPARATOR  lights SEPARATOR  tires);
        get_vehicle_damage_status_t.call(vehicle_id, panels, doors, lights, tires);
    }
    void update_vehicle_damage_status (int vehicle_id, int panels, int doors, int lights, int tires) 
    {
        START();
        DEBUG_NATIVE(/*f*/update_vehicle_damage_status, /*p*/vehicle_id SEPARATOR  panels SEPARATOR  doors SEPARATOR  lights SEPARATOR  tires);
        update_vehicle_damage_status_t.call(vehicle_id, panels, doors, lights, tires);
    }

    // Virtual Worlds
    void set_vehicle_virtual_world (int vehicle_id, int world_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/set_vehicle_virtual_world, /*p*/vehicle_id SEPARATOR  world_id);
        set_vehicle_virtual_world_t.call(vehicle_id, world_id);
    }
    int get_vehicle_virtual_world (int vehicle_id) 
    {
        START();
        DEBUG_NATIVE(/*f*/get_vehicle_virtual_world, /*p*/vehicle_id);
        return get_vehicle_virtual_world_t.call(vehicle_id);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Недокументированные возможности
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string get_serial (int player_id) 
    {
        START();
        std::string rezult;
        DEBUG_NATIVE(/*f*/get_serial, /*p*/player_id SEPARATOR  rezult SEPARATOR  pawn::string_len::val);
        gpci_t.call(player_id, rezult, pawn::string_len::val);
        return rezult;
    }


} // namespace samp {

// ([a-z_0-9]+)(\([^)]*\))((.*|\n){,9};\n *)(.+_t\.call\(([^)]*)\).*)
// \1 \2 \3DEBUG_NATIVE(/*f*/\1, /*p*/\6);\n        \5

//(DEBUG_NATIVE\([^,]+, /\*p\*/[^,]+),
//\1 SEPARATOR 


