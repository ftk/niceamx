
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// a_objects.inc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CreateObject 		native::create_object
#define SetObjectPos 		native::set_object_pos
#define GetObjectPos 		native::get_object_pos
#define SetObjectRot 		native::set_object_rot
#define GetObjectRot 		native::get_object_rot
#define IsValidObject 		native::is_valid_object
#define DestroyObject 		native::destroy_object
#define MoveObject 		native::move_object
#define StopObject 		native::stop_object
#define CreatePlayerObject 		native::create_player_object
#define SetPlayerObjectPos 		native::set_player_object_pos
#define GetPlayerObjectPos 		native::get_player_object_pos
#define SetPlayerObjectRot 		native::set_player_object_rot
#define GetPlayerObjectRot 		native::get_player_object_rot
#define IsValidPlayerObject 		native::is_valid_player_object
#define DestroyPlayerObject 		native::destroy_player_object
#define MovePlayerObject 		native::move_player_object
#define StopPlayerObject 		native::stop_player_object
#define AttachObjectToPlayer 		native::attach_object_to_player
#define AttachPlayerObjectToPlayer 		native::attach_player_object_to_player

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// a_players.inc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Player
#define SetSpawnInfo 		native::set_spawn_info
#define SpawnPlayer 		native::spawn_player

// Player info
#define SetPlayerPos 		native::set_player_pos
#define SetPlayerPosFindZ 		native::set_player_pos_findz
#define GetPlayerPos 		native::get_player_pos
#define SetPlayerFacingAngle 		native::set_player_facing_angle
#define GetPlayerFacingAngle 		native::get_player_facing_angle
#define IsPlayerInRangeOfPoint 		native::is_player_in_range_of_point
#define IsPlayerStreamedIn 		native::is_player_streamed_in
#define SetPlayerInterior 		native::set_player_interior
#define GetPlayerInterior 		native::get_player_interior
#define SetPlayerHealth 		native::set_player_health
#define GetPlayerHealth 		native::get_player_health
#define SetPlayerArmour 		native::set_player_armour
#define GetPlayerArmour 		native::get_player_armour
#define SetPlayerAmmo 		native::set_player_ammo
#define GetPlayerAmmo 		native::get_player_ammo
#define GetPlayerWeaponState 		native::get_player_weapon_state
#define SetPlayerTeam 		native::set_player_team
#define GetPlayerTeam 		native::get_player_team
#define SetPlayerScore 		native::set_player_score
#define GetPlayerScore 		native::get_player_score
#define GetPlayerDrunkLevel 		native::get_player_drunk_level
#define SetPlayerDrunkLevel 		native::set_player_drunk_level
#define SetPlayerColor 		native::set_player_color
#define GetPlayerColor 		native::get_player_color
#define SetPlayerSkin 		native::set_player_skin
#define GetPlayerSkin 		native::get_player_skin
#define GivePlayerWeapon 		native::give_player_weapon
#define ResetPlayerWeapons 		native::reset_player_weapons
#define SetPlayerArmedWeapon 		native::set_player_armed_weapon
#define GetPlayerWeaponData 		native::get_player_weapon_data
#define GivePlayerMoney 		native::give_player_money
#define ResetPlayerMoney 		native::reset_player_money
#define SetPlayerName 		native::set_player_name
#define GetPlayerMoney 		native::get_player_money
#define GetPlayerState 		native::get_player_state
#define GetPlayerIp 		native::get_player_ip
#define GetPlayerPing 		native::get_player_ping
#define GetPlayerWeapon 		native::get_player_weapon
#define GetPlayerKeys 		native::get_player_keys
#define GetPlayerName 		native::get_player_name
#define SetPlayerTime 		native::set_player_time
#define GetPlayerTime 		native::get_player_time
#define TogglePlayerClock 		native::toggle_player_clock
#define SetPlayerWeather 		native::set_player_weather
#define ForceClassSelection 		native::force_class_selection
#define SetPlayerWantedLevel 		native::set_player_wanted_level
#define GetPlayerWantedLevel 		native::get_player_wanted_level
#define SetPlayerFightingStyle 		native::set_player_fighting_style
#define GetPlayerFightingStyle 		native::get_player_fighting_style
#define SetPlayerVelocity 		native::set_player_velocity
#define GetPlayerVelocity 		native::get_player_velocity
#define PlayCrimeReportForPlayer 		native::play_crime_report_for_player
#define SetPlayerShopName 		native::set_player_shop_name
#define SetPlayerSkillLevel 		native::set_player_skill_level
#define GetPlayerSurfingVehicleID 		native::get_player_surfing_vehicle_id
#define SetPlayerHoldingObject 		native::set_player_holding_object
#define StopPlayerHoldingObject 		native::stop_player_holding_object
#define IsPlayerHoldingObject 		native::is_player_holding_object

#define SetPlayerChatBubble 		native::set_player_chat_bubble

// Player controls
#define PutPlayerInVehicle 		native::put_player_in_vehicle
#define GetPlayerVehicleID 		native::get_player_vehicle_id
#define GetPlayerVehicleSeat 		native::get_player_vehicle_seat
#define RemovePlayerFromVehicle 		native::remove_player_from_vehicle
#define TogglePlayerControllable 		native::toggle_player_controllable
#define PlayerPlaySound 		native::player_play_sound
#define ApplyAnimation 		native::apply_animation
#define ClearAnimations 		native::clear_animations
#define GetPlayerAnimationIndex 		native::get_player_animation_index
#define GetAnimationName 		native::get_animation_name
#define GetPlayerSpecialAction 		native::get_player_special_action
#define SetPlayerSpecialAction 		native::set_player_special_action

// Player world/map related
#define SetPlayerCheckpoint 		native::set_player_checkpoint
#define DisablePlayerCheckpoint 		native::disable_player_checkpoint
#define SetPlayerRaceCheckpoint 		native::set_player_race_checkpoint
#define DisablePlayerRaceCheckpoint 		native::disable_player_race_checkpoint
#define SetPlayerWorldBounds 		native::set_player_world_bounds
#define SetPlayerMarkerForPlayer 		native::set_player_marker_for_player
#define ShowPlayerNameTagForPlayer 		native::show_player_name_tag_for_player
#define SetPlayerMapIcon 		native::set_player_mapicon
#define RemovePlayerMapIcon 		native::remove_player_mapicon
#define AllowPlayerTeleport 		native::allow_player_teleport

// Player camera
#define SetPlayerCameraPos 		native::set_player_camera_pos
#define SetPlayerCameraLookAt 		native::set_player_camera_look_at
#define SetCameraBehindPlayer 		native::set_camera_behind_player
#define GetPlayerCameraPos 		native::get_player_camera_pos
#define GetPlayerCameraFrontVector 		native::get_player_camera_front_vector

// Player conditionals
#define IsPlayerConnected 		native::is_player_called
#define IsPlayerInVehicle 		native::is_player_in_vehicle
#define IsPlayerInAnyVehicle 		native::is_player_in_any_vehicle
#define IsPlayerInCheckpoint 		native::is_player_in_checkpoint
#define IsPlayerInRaceCheckpoint 		native::is_player_in_race_checkpoint

// Virtual Worlds
#define SetPlayerVirtualWorld 		native::set_player_virtual_world
#define GetPlayerVirtualWorld 		native::get_player_virtual_world

// Insane Stunts
#define EnableStuntBonusForPlayer 		native::enable_stunt_bonus_for_player
#define EnableStuntBonusForAll 		native::enable_stunt_bonus_for_all

// Spectating
#define TogglePlayerSpectating 		native::toggle_player_spectating
#define PlayerSpectatePlayer 		native::player_spectate_player
#define PlayerSpectateVehicle 		native::player_spectate_vehicle

// Recording for NPC playback
#define StartRecordingPlayerData 		native::start_recording_player_data
#define StopRecordingPlayerData 		native::stop_recording_player_data
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// a_samp.inc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Util
#define SendClientMessage 		native::send_client_message
#define SendPlayerMessageToPlayer 		native::send_player_message_to_player
#define SendDeathMessage 		native::send_death_message
#define GameTextForPlayer 		native::game_text_for_player
#define GetMaxPlayers 		native::get_max_players

// Game
#define SetGameModeText 		native::set_game_mode_text
#define SetTeamCount 		native::set_team_count
#define AddPlayerClass 		native::add_player_class
#define AddPlayerClassEx 		native::add_player_class_ex
#define AddStaticVehicle 		native::add_static_vehicle
#define AddStaticVehicleEx 		native::add_static_vehicle_ex
#define AddStaticPickup 		native::add_static_pickup
#define CreatePickup 		native::create_pickup
#define DestroyPickup 		native::destroy_pickup
#define ShowNameTags 		native::show_name_tags
#define ShowPlayerMarkers 		native::show_player_markers
#define GameModeExit 		native::gamemode_exit
#define SetWorldTime 		native::set_world_time
#define GetWeaponName 		native::get_weapon_name
#define EnableTirePopping 		native::enable_tire_popping
#define AllowInteriorWeapons 		native::allow_interior_weapons
#define SetWeather 		native::set_weather
#define SetGravity 		native::set_gravity
#define AllowAdminTeleport 		native::allow_admin_teleport
#define SetDeathDropAmount 		native::set_death_drop_amount
#define CreateExplosion 		native::create_explosion
#define EnableZoneNames 		native::enable_zone_names
#define UsePlayerPedAnims 		native::use_player_ped_anims
#define DisableInteriorEnterExits 		native::disable_interior_enter_exits
#define SetNameTagDrawDistance 		native::set_name_tag_draw_distance
#define DisableNameTagLOS 		native::disable_name_tag_los
#define LimitGlobalChatRadius 		native::limit_global_chat_radius
#define LimitPlayerMarkerRadius 		native::limit_player_marker_radius

// Npc
#define ConnectNPC 		native::call_npc
#define IsPlayerNPC 		native::is_player_npc

// Admin
#define IsPlayerAdmin 		native::is_player_admin
#define Kick 		native::kick
#define Ban 		native::ban
#define BanEx 		native::ban_ex
#define SendRconCommand 		native::send_rcon_command
#define GetServerVarAsString 		native::get_server_var_as_string
#define GetServerVarAsInt 		native::get_server_var_as_int
#define GetServerVarAsBool 		native::get_server_var_as_bool

// Menu
#define CreateMenu 		native::create_menu
#define DestroyMenu 		native::destroy_menu
#define AddMenuItem 		native::add_menu_item
#define SetMenuColumnHeader 		native::set_menu_column_header
#define ShowMenuForPlayer 		native::show_menu_for_player
#define HideMenuForPlayer 		native::hide_menu_for_player
#define IsValidMenu 		native::is_valid_menu
#define DisableMenu 		native::disable_menu
#define DisableMenuRow 		native::disable_menu_row
#define GetPlayerMenu 		native::get_player_menu

// Text Draw
#define TextDrawCreate 		native::textdraw_create
#define TextDrawDestroy 		native::textdraw_destroy
#define TextDrawLetterSize 		native::textdraw_letter_size
#define TextDrawTextSize 		native::textdraw_text_size
#define TextDrawAlignment 		native::textdraw_alignment
#define TextDrawColor 		native::textdraw_color
#define TextDrawUseBox 		native::textdraw_use_box
#define TextDrawBoxColor 		native::textdraw_box_color
#define TextDrawSetShadow 		native::textdraw_set_shadow
#define TextDrawSetOutline 		native::textdraw_set_outline
#define TextDrawBackgroundColor 		native::textdraw_background_color
#define TextDrawFont 		native::textdraw_font
#define TextDrawSetProportional 		native::textdraw_set_proportional
#define TextDrawShowForPlayer 		native::textdraw_show_for_player
#define TextDrawHideForPlayer 		native::textdraw_hide_for_player
#define TextDrawSetString 		native::textdraw_set_string

// Gang Zones
#define GangZoneCreate 		native::gangzone_create
#define GangZoneDestroy 		native::gangzone_destroy
#define GangZoneShowForPlayer 		native::gangzone_show_for_player
#define GangZoneHideForPlayer 		native::gangzone_hide_for_player
#define GangZoneFlashForPlayer 		native::gangzone_flash_for_player
#define GangZoneStopFlashForPlayer 		native::gangzone_stop_flash_for_player

// Global 3D Text Labels
#define Create3DTextLabel 		native::create_3dtextlabel
#define Delete3DTextLabel 		native::delete_3dtextlabel
#define Attach3DTextLabelToPlayer 		native::attach_3dtextlabel_to_player
#define Attach3DTextLabelToVehicle 		native::attach_3dtextlabel_to_vehicle
#define Update3DTextLabelText 		native::update_3dtextlabel_text

// Per-player 3D Text Labels
#define CreatePlayer3DTextLabel 		native::create_player3dtextlabel
#define DeletePlayer3DTextLabel 		native::delete_player3dtextlabel
#define UpdatePlayer3DTextLabelText 		native::update_player3dtextlabel_text

// Player GUI Dialog
#define ShowPlayerDialog 		native::show_player_dialog
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// a_vehicles.inc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vehicle
#define CreateVehicle 		native::create_vehicle
#define DestroyVehicle 		native::destroy_vehicle
#define IsVehicleStreamedIn 		native::is_vehicle_streamed_in
#define GetVehiclePos 		native::get_vehicle_pos
#define SetVehiclePos 		native::set_vehicle_pos
#define GetVehicleZAngle 		native::get_vehicle_zangle
#define GetVehicleRotationQuat 		native::get_vehicle_rotation_quat
#define SetVehicleZAngle 		native::set_vehicle_zangle
#define SetVehicleParamsForPlayer 		native::set_vehicle_params_for_player
#define SetVehicleToRespawn 		native::set_vehicle_to_respawn
#define LinkVehicleToInterior 		native::link_vehicle_to_interior
#define AddVehicleComponent 		native::add_vehicle_component
#define RemoveVehicleComponent 		native::remove_vehicle_component
#define ChangeVehicleColor 		native::change_vehicle_color
#define ChangeVehiclePaintjob 		native::change_vehicle_paintjob
#define SetVehicleHealth 		native::set_vehicle_health
#define GetVehicleHealth 		native::get_vehicle_health
#define AttachTrailerToVehicle 		native::attach_trailer_to_vehicle
#define DetachTrailerFromVehicle 		native::detach_trailer_from_vehicle
#define IsTrailerAttachedToVehicle 		native::is_trailer_attached_to_vehicle
#define GetVehicleTrailer 		native::get_vehicle_trailer
#define SetVehicleNumberPlate 		native::set_vehicle_number_plate
#define GetVehicleModel 		native::get_vehicle_model
#define GetVehicleComponentInSlot 		native::get_vehicle_component_in_slot
#define GetVehicleComponentType 		native::get_vehicle_component_type
#define RepairVehicle 		native::repair_vehicle
#define GetVehicleVelocity 		native::get_vehicle_velocity
#define SetVehicleVelocity 		native::set_vehicle_velocity
#define SetVehicleAngularVelocity 		native::set_vehicle_angular_velocity
#define GetVehicleDamageStatus 		native::get_vehicle_damage_status
#define UpdateVehicleDamageStatus 		native::update_vehicle_damage_status

// Virtual Worlds
#define SetVehicleVirtualWorld 		native::set_vehicle_virtual_world
#define GetVehicleVirtualWorld 		native::get_vehicle_virtual_world

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Недокументированные возможности
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define gpci 		native::gpci

// ^ *pawn::marh_t[^>]*> ([a-z_0-9]+)_t\("([^"]+)",.*$
// #define \2 \t\tnative::\1
