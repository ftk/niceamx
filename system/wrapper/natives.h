#include "pawn/natives.h"
#include "natives2.h"

/*
#define CreateObject create_object
#define SetObjectPos set_object_pos
#define GetObjectPos get_object_pos
#define SetObjectRot set_object_rot
#define GetObjectRot get_object_rot
#define AttachObjectToVehicle attach_object_to_vehicle
#define IsValidObject is_valid_object
#define DestroyObject destroy_object
#define StopObject stop_object
#define MoveObject move_object
#define CreatePlayerObject create_player_object
#define SetPlayerObjectPos set_player_object_pos
#define GetPlayerObjectPos get_player_object_pos
#define SetPlayerObjectRot set_player_object_rot
#define GetPlayerObjectRot get_player_object_rot
#define MovePlayerObject move_player_object
#define AttachObjectToPlayer attach_object_to_player
#define AttachPlayerObjectToPlayer attach_player_object_to_player
#define IsValidPlayerObject is_valid_player_object
#define DestroyPlayerObject destroy_player_object
#define StopPlayerObject stop_player_object
#define SetSpawnInfo set_spawn_info
#define SpawnPlayer spawn_player
#define SetPlayerPos set_player_pos
#define SetPlayerPosFindZ set_player_pos_find_z
#define GetPlayerPos get_player_pos
#define SetPlayerFacingAngle set_player_facing_angle
#define GetPlayerFacingAngle get_player_facing_angle
#define IsPlayerInRangeOfPoint is_player_in_range_of_point
#define IsPlayerStreamedIn is_player_streamed_in
#define SetPlayerInterior set_player_interior
#define GetPlayerInterior get_player_interior
#define SetPlayerHealth set_player_health
#define GetPlayerHealth get_player_health
#define SetPlayerArmour set_player_armour
#define GetPlayerArmour get_player_armour
#define SetPlayerAmmo set_player_ammo
#define GetPlayerAmmo get_player_ammo
#define GetPlayerWeaponState get_player_weapon_state
#define SetPlayerTeam set_player_team
#define GetPlayerTeam get_player_team
#define SetPlayerScore set_player_score
#define GetPlayerScore get_player_score
#define GetPlayerDrunkLevel get_player_drunk_level
#define SetPlayerDrunkLevel set_player_drunk_level
#define SetPlayerColor set_player_color
#define GetPlayerColor get_player_color
#define SetPlayerSkin set_player_skin
#define GetPlayerSkin get_player_skin
#define GivePlayerWeapon give_player_weapon
#define ResetPlayerWeapons reset_player_weapons
#define SetPlayerArmedWeapon set_player_armed_weapon
#define GetPlayerWeaponData get_player_weapon_data
#define GivePlayerMoney give_player_money
#define ResetPlayerMoney reset_player_money
#define SetPlayerName set_player_name
#define GetPlayerMoney get_player_money
#define GetPlayerState get_player_state
#define GetPlayerIp get_player_ip
#define GetPlayerPing get_player_ping
#define GetPlayerWeapon get_player_weapon
#define GetPlayerKeys get_player_keys
#define GetPlayerName get_player_name
#define SetPlayerTime set_player_time
#define GetPlayerTime get_player_time
#define TogglePlayerClock toggle_player_clock
#define SetPlayerWeather set_player_weather
#define ForceClassSelection force_class_selection
#define SetPlayerWantedLevel set_player_wanted_level
#define GetPlayerWantedLevel get_player_wanted_level
#define SetPlayerFightingStyle set_player_fighting_style
#define GetPlayerFightingStyle get_player_fighting_style
#define SetPlayerVelocity set_player_velocity
#define GetPlayerVelocity get_player_velocity
#define SetPlayerHoldingObject set_player_holding_object
#define PlayCrimeReportForPlayer play_crime_report_for_player
#define SetPlayerShopName set_player_shop_name
#define SetPlayerSkillLevel set_player_skill_level
#define GetPlayerSurfingVehicleID get_player_surfing_vehicle_id
#define StopPlayerHoldingObject stop_player_holding_object
#define IsPlayerHoldingObject is_player_holding_object
#define SetPVarInt set_p_var_int
#define GetPVarInt get_p_var_int
#define SetPVarString set_p_var_string
#define GetPVarString get_p_var_string
#define SetPVarFloat set_p_var_float
#define DeletePVar delete_p_var
#define GetPVarsUpperIndex get_p_vars_upper_index
#define GetPVarNameAtIndex get_p_var_name_at_index
#define GetPVarType get_p_var_type
#define SetPlayerChatBubble set_player_chat_bubble
#define PlayerPlaySound player_play_sound
#define ApplyAnimation apply_animation
#define SetPlayerCheckpoint set_player_checkpoint
#define SetPlayerRaceCheckpoint set_player_race_checkpoint
#define SetPlayerWorldBounds set_player_world_bounds
#define SetPlayerMapIcon set_player_map_icon
#define PutPlayerInVehicle put_player_in_vehicle
#define GetPlayerVehicleID get_player_vehicle_id
#define GetPlayerVehicleSeat get_player_vehicle_seat
#define RemovePlayerFromVehicle remove_player_from_vehicle
#define TogglePlayerControllable toggle_player_controllable
#define GetPlayerAnimationIndex get_player_animation_index
#define GetAnimationName get_animation_name
#define ClearAnimations clear_animations
#define GetPlayerSpecialAction get_player_special_action
#define SetPlayerSpecialAction set_player_special_action
#define DisablePlayerCheckpoint disable_player_checkpoint
#define DisablePlayerRaceCheckpoint disable_player_race_checkpoint
#define SetPlayerMarkerForPlayer set_player_marker_for_player
#define ShowPlayerNameTagForPlayer show_player_name_tag_for_player
#define RemovePlayerMapIcon remove_player_map_icon
#define AllowPlayerTeleport allow_player_teleport
#define SetPlayerCameraPos set_player_camera_pos
#define SetPlayerCameraLookAt set_player_camera_look_at
#define GetPlayerCameraPos get_player_camera_pos
#define GetPlayerCameraFrontVector get_player_camera_front_vector
#define GetPlayerCameraUpVector get_player_camera_up_vector
#define SetCameraBehindPlayer set_camera_behind_player
#define IsPlayerConnected is_player_connected
#define IsPlayerInVehicle is_player_in_vehicle
#define IsPlayerInAnyVehicle is_player_in_any_vehicle
#define IsPlayerInCheckpoint is_player_in_checkpoint
#define IsPlayerInRaceCheckpoint is_player_in_race_checkpoint
#define SetPlayerVirtualWorld set_player_virtual_world
#define GetPlayerVirtualWorld get_player_virtual_world
#define EnableStuntBonusForPlayer enable_stunt_bonus_for_player
#define EnableStuntBonusForAll enable_stunt_bonus_for_all
#define TogglePlayerSpectating toggle_player_spectating
#define PlayerSpectatePlayer player_spectate_player
#define PlayerSpectateVehicle player_spectate_vehicle
#define StartRecordingPlayerData start_recording_player_data
#define StopRecordingPlayerData stop_recording_player_data
#define SendClientMessage send_client_message
#define SendClientMessageToAll send_client_message_to_all
#define SendPlayerMessageToPlayer send_player_message_to_player
#define SendPlayerMessageToAll send_player_message_to_all
#define SendDeathMessage send_death_message
#define GameTextForAll game_text_for_all
#define GameTextForPlayer game_text_for_player
#define SetPlayerAttachedObject set_player_attached_object
#define RemovePlayerAttachedObject remove_player_attached_object
#define IsPlayerAttachedObjectSlotUsed is_player_attached_object_slot_used
#define print _print
#define printf _printf
#define format _format
#define SetTimerEx set_timer_ex
#define CallRemoteFunction call_remote_function
#define CallLocalFunction call_local_function
#define printf _printf
#define format _format
#define SetTimerEx set_timer_ex
#define CallRemoteFunction call_remote_function
#define CallLocalFunction call_local_function
#define SetTimer set_timer
#define KillTimer kill_timer
#define GetTickCount get_tick_count
#define GetMaxPlayers get_max_players
#define Float float
#define Float float
#define Float float
#define Float float
#define SetGameModeText set_game_mode_text
#define SetTeamCount set_team_count
#define AddPlayerClass add_player_class
#define AddPlayerClassEx add_player_class_ex
#define AddStaticVehicle add_static_vehicle
#define AddStaticVehicleEx add_static_vehicle_ex
#define AddStaticPickup add_static_pickup
#define CreatePickup create_pickup
#define CreateExplosion create_explosion
#define DestroyPickup destroy_pickup
#define ShowNameTags show_name_tags
#define ShowPlayerMarkers show_player_markers
#define GameModeExit game_mode_exit
#define SetWorldTime set_world_time
#define GetWeaponName get_weapon_name
#define EnableTirePopping enable_tire_popping
#define AllowInteriorWeapons allow_interior_weapons
#define SetWeather set_weather
#define SetGravity set_gravity
#define Float float
#define AllowAdminTeleport allow_admin_teleport
#define SetDeathDropAmount set_death_drop_amount
#define EnableZoneNames enable_zone_names
#define UsePlayerPedAnims use_player_ped_anims
#define DisableInteriorEnterExits disable_interior_enter_exits
#define DisableNameTagLOS disable_name_tag_l_o_s
#define SetNameTagDrawDistance set_name_tag_draw_distance
#define LimitGlobalChatRadius limit_global_chat_radius
#define LimitPlayerMarkerRadius limit_player_marker_radius
#define ConnectNPC connect_n_p_c
#define IsPlayerNPC is_player_n_p_c
#define IsPlayerAdmin is_player_admin
#define Kick kick
#define Ban ban
#define BanEx ban_ex
#define SendRconCommand send_rcon_command
#define GetServerVarAsString get_server_var_as_string
#define GetServerVarAsInt get_server_var_as_int
#define GetServerVarAsBool get_server_var_as_bool
#define Menu menu
#define DestroyMenu destroy_menu
#define AddMenuItem add_menu_item
#define SetMenuColumnHeader set_menu_column_header
#define ShowMenuForPlayer show_menu_for_player
#define HideMenuForPlayer hide_menu_for_player
#define IsValidMenu is_valid_menu
#define DisableMenu disable_menu
#define DisableMenuRow disable_menu_row
#define TextDrawDestroy text_draw_destroy
#define TextDrawLetterSize text_draw_letter_size
#define TextDrawTextSize text_draw_text_size
#define TextDrawAlignment text_draw_alignment
#define TextDrawColor text_draw_color
#define TextDrawUseBox text_draw_use_box
#define TextDrawBoxColor text_draw_box_color
#define TextDrawSetShadow text_draw_set_shadow
#define TextDrawSetOutline text_draw_set_outline
#define TextDrawBackgroundColor text_draw_background_color
#define TextDrawFont text_draw_font
#define TextDrawSetProportional text_draw_set_proportional
#define TextDrawShowForPlayer text_draw_show_for_player
#define TextDrawHideForPlayer text_draw_hide_for_player
#define TextDrawShowForAll text_draw_show_for_all
#define TextDrawHideForAll text_draw_hide_for_all
#define TextDrawSetString text_draw_set_string
#define GangZoneCreate gang_zone_create
#define GangZoneDestroy gang_zone_destroy
#define GangZoneShowForPlayer gang_zone_show_for_player
#define GangZoneShowForAll gang_zone_show_for_all
#define GangZoneHideForPlayer gang_zone_hide_for_player
#define GangZoneHideForAll gang_zone_hide_for_all
#define GangZoneFlashForPlayer gang_zone_flash_for_player
#define GangZoneFlashForAll gang_zone_flash_for_all
#define GangZoneStopFlashForPlayer gang_zone_stop_flash_for_player
#define GangZoneStopFlashForAll gang_zone_stop_flash_for_all
#define Delete3DTextLabel delete_3dtextlabel
#define Attach3DTextLabelToPlayer attach_3dtextlabel
#define Attach3DTextLabelToVehicle attach_3dtextlabel
#define Update3DTextLabelText update_3dtextlabel
#define DeletePlayer3DTextLabel delete_player3dtextlabel
#define UpdatePlayer3DTextLabelText update_player3dtextlabel
#define ShowPlayerDialog show_player_dialog
#define CreateVehicle create_vehicle
#define GetVehiclePos get_vehicle_pos
#define SetVehiclePos set_vehicle_pos
#define GetVehicleZAngle get_vehicle_z_angle
#define SetVehicleZAngle set_vehicle_z_angle
#define DestroyVehicle destroy_vehicle
#define IsVehicleStreamedIn is_vehicle_streamed_in
#define SetVehicleParamsForPlayer set_vehicle_params_for_player
#define SetVehicleToRespawn set_vehicle_to_respawn
#define LinkVehicleToInterior link_vehicle_to_interior
#define AddVehicleComponent add_vehicle_component
#define RemoveVehicleComponent remove_vehicle_component
#define ChangeVehicleColor change_vehicle_color
#define ChangeVehiclePaintjob change_vehicle_paintjob
#define SetVehicleHealth set_vehicle_health
#define GetVehicleHealth get_vehicle_health
#define AttachTrailerToVehicle attach_trailer_to_vehicle
#define DetachTrailerFromVehicle detach_trailer_from_vehicle
#define IsTrailerAttachedToVehicle is_trailer_attached_to_vehicle
#define GetVehicleTrailer get_vehicle_trailer
#define SetVehicleNumberPlate set_vehicle_number_plate
#define GetVehicleModel get_vehicle_model
#define GetVehicleComponentInSlot get_vehicle_component_in_slot
#define GetVehicleComponentType get_vehicle_component_type
#define RepairVehicle repair_vehicle
#define GetVehicleRotationQuat get_vehicle_rotation_quat
#define SetVehicleAngularVelocity set_vehicle_angular_velocity
#define GetVehicleVelocity get_vehicle_velocity
#define SetVehicleVelocity set_vehicle_velocity
#define GetVehicleDamageStatus get_vehicle_damage_status
#define UpdateVehicleDamageStatus update_vehicle_damage_status
#define ManualVehicleEngineAndLights manual_vehicle_engine_and_lights
#define SetVehicleParamsEx set_vehicle_params_ex
#define GetVehicleParamsEx get_vehicle_params_ex
#define SetVehicleVirtualWorld set_vehicle_virtual_world
#define GetVehicleVirtualWorld get_vehicle_virtual_world

//^native ([A-Za-z_0-9]+).*$
//\1 _\1

//_(.*)([A-Z])
//_\1_\l\2

*/
