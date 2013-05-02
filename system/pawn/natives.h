#ifndef PAWN_NATIVES_H
#define PAWN_NATIVES_H
#include "config.h"
#include <string>

namespace native
{

        //Константы сампа
        enum player_state {
            PLAYER_STATE_NONE               = 0
            ,PLAYER_STATE_ONFOOT            = 1
            ,PLAYER_STATE_DRIVER            = 2
            ,PLAYER_STATE_PASSENGER         = 3
            ,PLAYER_STATE_WASTED            = 7
            ,PLAYER_STATE_SPAWNED           = 8
            ,PLAYER_STATE_SPECTATING        = 9
        };


        // Limits and internal constants
        enum {MAX_PLAYER_NAME          = 24};
        enum {MAX_PLAYERS              = 500};
        enum {MAX_VEHICLES             = 2000};
        enum {INVALID_PLAYER_ID        = 0xFFFF};
        enum {INVALID_VEHICLE_ID       = 0xFFFF};
        enum {NO_TEAM                  = 255};
        enum {MAX_OBJECTS              = 1000};
        enum {INVALID_OBJECT_ID        = 0xFFFF};
        enum {MAX_GANG_ZONES           = 1024};
        enum {MAX_TEXT_DRAWS           = 2048};
        enum {MAX_MENUS                = 128};
        enum {MAX_3DTEXT_GLOBAL        = 1024};
        enum {MAX_3DTEXT_PLAYER        = 1024};
        enum {MAX_PICKUPS              = 2048};
        enum {INVALID_MENU             = 0xFF};
        enum {INVALID_TEXT_DRAW        = 0xFFFF};
        enum {INVALID_GANG_ZONE        = -1};
        enum {INVALID_3DTEXT_ID        = 0xFFFF};
        enum {MAX_CHATBUBBLE_LENGTH    = 144};


        enum player_markers_mode {
            PLAYER_MARKERS_MODE_OFF         = 0
            ,PLAYER_MARKERS_MODE_GLOBAL     = 1
            ,PLAYER_MARKERS_MODE_STREAMED   = 2
        };

        // Weapons
        enum {WEAPON_UNARMED            = 0};
        enum {WEAPON_BRASSKNUCKLE       = 1};
        enum {WEAPON_GOLFCLUB           = 2};
        enum {WEAPON_NITESTICK          = 3};
        enum {WEAPON_KNIFE              = 4};
        enum {WEAPON_BAT                = 5};
        enum {WEAPON_SHOVEL             = 6};
        enum {WEAPON_POOLSTICK          = 7};
        enum {WEAPON_KATANA             = 8};
        enum {WEAPON_CHAINSAW           = 9};
        enum {WEAPON_DILDO              = 10};
        enum {WEAPON_DILDO2             = 11};
        enum {WEAPON_VIBRATOR           = 12};
        enum {WEAPON_VIBRATOR2          = 13};
        enum {WEAPON_FLOWER             = 14};
        enum {WEAPON_CANE               = 15};
        enum {WEAPON_GRENADE            = 16};
        enum {WEAPON_TEARGAS            = 17};
        enum {WEAPON_MOLTOV             = 18};
        enum {WEAPON_COLT45             = 22};
        enum {WEAPON_SILENCED           = 23};
        enum {WEAPON_DEAGLE             = 24};
        enum {WEAPON_SHOTGUN            = 25};
        enum {WEAPON_SAWEDOFF           = 26};
        enum {WEAPON_SHOTGSPA           = 27};
        enum {WEAPON_UZI                = 28};
        enum {WEAPON_MP5                = 29};
        enum {WEAPON_AK47               = 30};
        enum {WEAPON_M4                 = 31};
        enum {WEAPON_TEC9               = 32};
        enum {WEAPON_RIFLE              = 33};
        enum {WEAPON_SNIPER             = 34};
        enum {WEAPON_ROCKETLAUNCHER     = 35};
        enum {WEAPON_HEATSEEKER         = 36};
        enum {WEAPON_FLAMETHROWER       = 37};
        enum {WEAPON_MINIGUN            = 38};
        enum {WEAPON_SATCHEL            = 39};
        enum {WEAPON_BOMB               = 40};
        enum {WEAPON_SPRAYCAN           = 41};
        enum {WEAPON_FIREEXTINGUISHER   = 42};
        enum {WEAPON_CAMERA             = 43};
        enum {WEAPON_PARACHUTE          = 46};
        enum {WEAPON_VEHICLE            = 49};
        enum {WEAPON_DROWN              = 53};
        enum {WEAPON_COLLISION          = 54};

        // Keys
        enum {KEY_ACTION                = 1};
        enum {KEY_CROUCH                = 2};
        enum {KEY_FIRE                  = 4};
        enum {KEY_SPRINT                = 8};
        enum {KEY_SECONDARY_ATTACK      = 16};
        enum {KEY_JUMP                  = 32};
        enum {KEY_LOOK_RIGHT            = 64};
        enum {KEY_HANDBRAKE             = 128};
        enum {KEY_LOOK_LEFT             = 256};
        enum {KEY_SUBMISSION            = 512};
        enum {KEY_LOOK_BEHIND           = 512};
        enum {KEY_WALK                  = 1024};
        enum {KEY_ANALOG_UP             = 2048};
        enum {KEY_ANALOG_DOWN           = 4096};
        enum {KEY_ANALOG_RIGHT          = 16384};
        enum {KEY_ANALOG_LEFT           = 8192};

        enum {KEY_UP                    = 65408}; // -128 - проверить с 0,3
        enum {KEY_DOWN                  = 128};
        enum {KEY_LEFT                  = 65408}; // -128 - проверить с 0,3
        enum {KEY_RIGHT                 = 128};

        // Spectating
        enum spectate_mode {
             SPECTATE_MODE_NORMAL       = 1
            ,SPECTATE_MODE_FIXED        = 2
            ,SPECTATE_MODE_SIDE         = 3
        };

        // SpecialActions
        enum special_action {
             SPECIAL_ACTION_NONE            = 0
            ,SPECIAL_ACTION_DUCK            = 1 // Только чтение
            ,SPECIAL_ACTION_USEJETPACK      = 2
            ,SPECIAL_ACTION_ENTER_VEHICLE   = 3 // Только чтение
            ,SPECIAL_ACTION_EXIT_VEHICLE    = 4 // Только чтение
            ,SPECIAL_ACTION_DANCE1          = 5
            ,SPECIAL_ACTION_DANCE2          = 6
            ,SPECIAL_ACTION_DANCE3          = 7
            ,SPECIAL_ACTION_DANCE4          = 8
            ,SPECIAL_ACTION_HANDSUP         = 10
            ,SPECIAL_ACTION_USECELLPHONE    = 11
            ,SPECIAL_ACTION_SITTING         = 12
            ,SPECIAL_ACTION_STOPUSECELLPHONE= 13
            ,SPECIAL_ACTION_DRINK_BEER      = 20 // Will increase the player's drunk level when used
            ,SPECIAL_ACTION_SMOKE_CIGGY     = 21
            ,SPECIAL_ACTION_DRINK_WINE      = 22
            ,SPECIAL_ACTION_DRINK_SPRUNK    = 23
            ,SPECIAL_ACTION_PISSING         = 68
        };

        enum fight_style {
             FIGHT_STYLE_NORMAL             = 4
            ,FIGHT_STYLE_BOXING             = 5
            ,FIGHT_STYLE_KUNGFU             = 6
            ,FIGHT_STYLE_KNEEHEAD           = 7
            ,FIGHT_STYLE_GRABKICK           = 15
            ,FIGHT_STYLE_ELBOW              = 16
        };

        enum weapon_skill {
             WEAPONSKILL_PISTOL             = 0
            ,WEAPONSKILL_PISTOL_SILENCED    = 1
            ,WEAPONSKILL_DESERT_EAGLE       = 2
            ,WEAPONSKILL_SHOTGUN            = 3
            ,WEAPONSKILL_SAWNOFF_SHOTGUN    = 4
            ,WEAPONSKILL_SPAS12_SHOTGUN     = 5
            ,WEAPONSKILL_MICRO_UZI          = 6
            ,WEAPONSKILL_MP5                = 7
            ,WEAPONSKILL_AK47               = 8
            ,WEAPONSKILL_M4                 = 9
            ,WEAPONSKILL_SNIPERRIFLE        = 10
        };


        // Recording for NPC playback
        enum player_recording_type {
             PLAYER_RECORDING_TYPE_NONE     = 0
            ,PLAYER_RECORDING_TYPE_DRIVER   = 1
            ,PLAYER_RECORDING_TYPE_ONFOOT   = 2
        };

        enum weapon_state {
             WEAPONSTATE_UNKNOWN            = -1
            ,WEAPONSTATE_NO_BULLETS         = 0
            ,WEAPONSTATE_LAST_BULLET        = 1
            ,WEAPONSTATE_MORE_BULLETS       = 2
            ,WEAPONSTATE_RELOADING          = 3
        };

        enum bones {
             BONE_SPINE                     = 1
            ,BONE_HEAD                      = 2
            ,BONE_LEFT_UPPER_ARM            = 3
            ,BONE_RIGHT_UPPER_ARM           = 4
            ,BONE_LEFT_HAND                 = 5
            ,BONE_RIGHT_HAND                = 6
            ,BONE_LEFT_THIGH                = 7
            ,BONE_RIGHT_THIGH               = 8
            ,BONE_LEFT_FOOT                 = 9
            ,BONE_RIGHT_FOOT                = 10
            ,BONE_RIGHT_CALF                = 11
            ,BONE_LEFT_CALF                 = 12
            ,BONE_LEFT_FOREARM              = 13
            ,BONE_RIGHT_FOREARM             = 14
            ,BONE_LEFT_CLAVICLE             = 15
            ,BONE_RIGHT_CLAVICLE            = 16
            ,BONE_NECK                      = 17
            ,BONE_JAW                       = 18
        };
        enum carmod_type {
             CARMODTYPE_SPOILER             = 0
            ,CARMODTYPE_HOOD                = 1
            ,CARMODTYPE_ROOF                = 2
            ,CARMODTYPE_SIDESKIRT           = 3
            ,CARMODTYPE_LAMPS               = 4
            ,CARMODTYPE_NITRO               = 5
            ,CARMODTYPE_EXHAUST             = 6
            ,CARMODTYPE_WHEELS              = 7
            ,CARMODTYPE_STEREO              = 8
            ,CARMODTYPE_HYDRAULICS          = 9
            ,CARMODTYPE_FRONT_BUMPER        = 10
            ,CARMODTYPE_REAR_BUMPER         = 11
            ,CARMODTYPE_VENT_RIGHT          = 12
            ,CARMODTYPE_VENT_LEFT           = 13
        };

        // Player GUI Dialog
        enum dialog_style {
             DIALOG_STYLE_MSGBOX            = 0
            ,DIALOG_STYLE_INPUT             = 1
            ,DIALOG_STYLE_LIST              = 2
            ,DIALOG_STYLE_PASSWORD          = 3
        };

        // 0.3e

        enum camera_cut {
            CAMERA_CUT = 2,
            CAMERA_MOVE = 1
        };

        //Методы сампа

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // a_objects.inc
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int     create_object(int model_id, float x, float y, float z, float rx, float ry, float rz, float draw_distance = 300.f); // CreateObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = 0.0);
        void    set_object_pos(int object_id, float x, float y, float z); // SetObjectPos(objectid, Float:X, Float:Y, Float:Z);
        void    get_object_pos(int object_id, float& x, float& y, float& z); // GetObjectPos(objectid, &Float:X, &Float:Y, &Float:Z);
        void    set_object_rot(int object_id, float rx, float ry, float rz); // SetObjectRot(objectid, Float:RotX, Float:RotY, Float:RotZ);
        void    get_object_rot(int object_id, float& rx, float& ry, float& rz); // GetObjectRot(objectid, &Float:RotX, &Float:RotY, &Float:RotZ);
        bool    is_valid_object(int object_id); // IsValidObject(objectid);
        void    destroy_object(int object_id); // DestroyObject(objectid);
        void    move_object(int object_id, float x, float y, float z, float speed); // MoveObject(objectid, Float:X, Float:Y, Float:Z, Float:Speed);
        void    stop_object(int object_id); // StopObject(objectid);
        int     create_player_object(int player_id, int model_id, float x, float y, float z, float rx, float ry, float rz, float draw_distance = 300.f); // CreatePlayerObject(playerid, modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = 0.0);
        void    set_player_object_pos(int player_id, int object_id, float x, float y, float z); // SetPlayerObjectPos(playerid, objectid, Float:X, Float:Y, Float:Z);
        void    get_player_object_pos(int player_id, int object_id, float& x, float& y, float& z); // GetPlayerObjectPos(playerid, objectid, &Float:X, &Float:Y, &Float:Z);
        void    set_player_object_rot(int player_id, int object_id, float rx, float ry, float rz); // SetPlayerObjectRot(playerid, objectid, Float:RotX, Float:RotY, Float:RotZ);
        void    get_player_object_rot(int player_id, int object_id, float& rx, float& ry, float& rz); // GetPlayerObjectRot(playerid, objectid, &Float:RotX, &Float:RotY, &Float:RotZ);
        bool    is_valid_player_object(int player_id, int object_id); // IsValidPlayerObject(playerid, objectid);
        void    destroy_player_object(int player_id, int object_id); // DestroyPlayerObject(playerid, objectid);
        void    move_player_object(int player_id, int object_id, float x, float y, float z, float speed); // MovePlayerObject(playerid, objectid, Float:X, Float:Y, Float:Z, Float:Speed);
        void    stop_player_object(int player_id, int object_id); // StopPlayerObject(playerid, objectid);
        void    attach_object_to_player(int object_id, int player_id, float offset_x, float offset_y, float offset_z, float offset_rx, float offset_ry, float offset_rz); // AttachObjectToPlayer(objectid, playerid, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:rX, Float:rY, Float:rZ);
        void    attach_player_object_to_player(int object_player_id, int object_id, int attach_player_id, float offset_x, float offset_y, float offset_z, float offset_rx, float offset_ry, float offset_rz); // AttachPlayerObjectToPlayer(objectplayer, objectid, attachplayer, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:rX, Float:rY, Float:rZ);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // a_players.inc
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Player
        void    set_spawn_info(int player_id, int team_id, int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3); // SetSpawnInfo(playerid, team, skin, Float:x, Float:y, Float:z, Float:rotation, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
        void    spawn_player(int player_id); // SpawnPlayer(playerid);

        // Player info
        void    set_player_pos(int player_id, float x, float y, float z); // SetPlayerPos(playerid, Float:x, Float:y, Float:z);
        void    set_player_pos_findz(int player_id, float x, float y, float z); // SetPlayerPosFindZ(playerid, Float:x, Float:y, Float:z);
        void    get_player_pos(int player_id, float& x, float& y, float& z); // GetPlayerPos(playerid, &Float:x, &Float:y, &Float:z);
        void    set_player_facing_angle(int player_id, float rz); // SetPlayerFacingAngle(playerid,Float:ang);
        float   get_player_facing_angle(int player_id); // GetPlayerFacingAngle(playerid,&Float:ang);
        bool    is_player_in_range_of_point(int player_id, float range, float x, float y, float z); // IsPlayerInRangeOfPoint(playerid, Float:range, Float:x, Float:y, Float:z);
        bool    is_player_streamed_in(int player_id, int for_player_id); // IsPlayerStreamedIn(playerid, forplayerid);
        void    set_player_interior(int player_id, int interior_id); // SetPlayerInterior(playerid,interiorid);
        int     get_player_interior(int player_id); // GetPlayerInterior(playerid);
        void    set_player_health(int player_id, float health); // SetPlayerHealth(playerid, Float:health);
        float   get_player_health(int player_id); // GetPlayerHealth(playerid, &Float:health);
        void    set_player_armour(int player_id, float armour); // SetPlayerArmour(playerid, Float:armour);
        float   get_player_armour(int player_id); // GetPlayerArmour(playerid, &Float:armour);
        void    set_player_ammo(int player_id, int weapon_slot, int ammo); // SetPlayerAmmo(playerid, weaponslot, ammo);
        int     get_player_ammo(int player_id); // GetPlayerAmmo(playerid);
        weapon_state    get_player_weapon_state(int player_id); // GetPlayerWeaponState(playerid);
        void    set_player_team(int player_id, int team_id); // SetPlayerTeam(playerid, teamid);
        int     get_player_team(int player_id); // GetPlayerTeam(playerid);
        void    set_player_score(int player_id, int score); // SetPlayerScore(playerid,score);
        int     get_player_score(int player_id); // GetPlayerScore(int player_id);
        int     get_player_drunk_level(int player_id); // GetPlayerDrunkLevel(playerid);
        void    set_player_drunk_level(int player_id, int level); // SetPlayerDrunkLevel(playerid, level);
        void    set_player_color(int player_id, unsigned color); // SetPlayerColor(playerid,color);
        unsigned int    get_player_color(int player_id); // GetPlayerColor(playerid);
        void    set_player_skin(int player_id, int skin_id); // SetPlayerSkin(playerid, skinid);
        int     get_player_skin(int player_id); // GetPlayerSkin(playerid);
        void    give_player_weapon(int player_id, int weapon_id, int weapon_ammo); // GivePlayerWeapon(playerid, weaponid, ammo);
        void    reset_player_weapons(int player_id); // ResetPlayerWeapons(playerid);
        void    set_player_armed_weapon(int player_id, int weapon_id); // SetPlayerArmedWeapon(playerid, weaponid);
        void    get_player_weapon_data(int player_id, int slot, int& weapon_id, int& weapon_ammo); // GetPlayerWeaponData(playerid, slot, &weapons, &ammo);
        void    give_player_money(int player_id, int money); // GivePlayerMoney(playerid,money);
        void    reset_player_money(int player_id); // ResetPlayerMoney(playerid);
        int     set_player_name(int player_id, std::string const& name); // SetPlayerName(playerid, const name[]);
        int     get_player_money(int player_id); // GetPlayerMoney(playerid);
        player_state    get_player_state(int player_id); // GetPlayerState(playerid);
        std::string     get_player_ip(int player_id); // GetPlayerIp(playerid, name[], len);
        int     get_player_ping(int player_id); // GetPlayerPing(playerid);
        int     get_player_weapon(int player_id); // GetPlayerWeapon(playerid);
        void    get_player_keys(int player_id, int& keys, int& updown, int& leftright); // GetPlayerKeys(playerid, &keys, &updown, &leftright);
        std::string     get_player_name(int player_id); // GetPlayerName(playerid, const name[], len);
        void    set_player_time(int player_id, int hour, int minute); // SetPlayerTime(playerid, hour, minute);
        void    get_player_time(int player_id, int& hour, int& minute); // GetPlayerTime(playerid, &hour, &minute);
        void    toggle_player_clock(int player_id, int toggle); // TogglePlayerClock(playerid, toggle);
        void    set_player_weather(int player_id, int weather); // SetPlayerWeather(playerid, weather);
        void    force_class_selection(int player_id); // ForceClassSelection(playerid);
        void    set_player_wanted_level(int player_id, int level); // SetPlayerWantedLevel(playerid, level);
        int     get_player_wanted_level(int player_id); // GetPlayerWantedLevel(playerid);
        void    set_player_fighting_style(int player_id, fight_style style); // SetPlayerFightingStyle(playerid, style);
        fight_style     get_player_fighting_style(int player_id); // GetPlayerFightingStyle(playerid);
        void    set_player_velocity(int player_id, float x, float y, float z); // SetPlayerVelocity(playerid, Float:X, Float:Y, Float:Z);
        void    get_player_velocity(int player_id, float& x, float& y, float& z); // GetPlayerVelocity(playerid, &Float:X, &Float:Y, &Float:Z);
        void    play_crime_report_for_player(int player_id, int suspect_id, int crime_id); // PlayCrimeReportForPlayer(playerid, suspectid, crime);
        void    set_player_shop_name(int player_id, std::string const& shop_name); // SetPlayerShopName(playerid, shopname[]);
        void    set_player_skill_level(int player_id, weapon_skill skill, int level); // SetPlayerSkillLevel(playerid, skill, level);
        int     get_player_surfing_vehicle_id(int player_id); // GetPlayerSurfingVehicleID(playerid);
        void    set_player_holding_object(int player_id, int model_id, bones bone_id, float offset_x = 0.0f, float offset_y = 0.0f, float offset_z = 0.0f, float rx = 0.0f, float ry = 0.0f, float rz = 0.0f); // SetPlayerHoldingObject(playerid, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0);
        void    stop_player_holding_object(int player_id); // StopPlayerHoldingObject(playerid);
        bool    is_player_holding_object(int player_id); // IsPlayerHoldingObject(playerid);
        
        void    set_player_chat_bubble(int player_id, std::string const& text, unsigned int color, float draw_distance, int expire_time); // SetPlayerChatBubble(playerid, text[], color, Float:drawdistance, expiretime);
        
        // Player controls
        void    put_player_in_vehicle(int player_id, int vehicle_id, int seat_id); // PutPlayerInVehicle(playerid, vehicleid, seatid);
        int     get_player_vehicle_id(int player_id); // GetPlayerVehicleID(playerid);
        int     get_player_vehicle_seat(int player_id); // GetPlayerVehicleSeat(playerid);
        void    remove_player_from_vehicle(int player_id); // RemovePlayerFromVehicle(playerid);
        void    toggle_player_controllable(int player_id, bool is_unfreeze); // TogglePlayerControllable(playerid, toggle);
        void    player_play_sound(int player_id, int sound_id, float x, float y, float z); // PlayerPlaySound(playerid, soundid, Float:x, Float:y, Float:z);
        void    apply_animation(int player_id, std::string const& anim_lib, std::string const& anim_name, float delta, int loop, int lock_x, int lock_y, int freeze, int time, int forcesync); // ApplyAnimation(playerid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync = 0);
        void    clear_animations(int player_id, int forcesync); // ClearAnimations(playerid, forcesync = 0);
        int     get_player_animation_index(int player_id); // GetPlayerAnimationIndex(playerid);
        void    get_animation_name(int index, std::string& anim_lib, std::string& anim_name); // GetAnimationName(index, animlib[], len1, animname[], len2);
        special_action  get_player_special_action(int player_id); // GetPlayerSpecialAction(playerid);
        void    set_player_special_action(int player_id, special_action action_id); // SetPlayerSpecialAction(playerid,actionid);

        // Player world/map related
        void    set_player_checkpoint(int player_id, float x, float y, float z, float size); // SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size);
        void    disable_player_checkpoint(int player_id); // DisablePlayerCheckpoint(playerid);
        void    set_player_race_checkpoint(int player_id, int type_id, float x, float y, float z, float next_x, float next_y, float next_z, float size); // SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size);
        void    disable_player_race_checkpoint(int player_id); // DisablePlayerRaceCheckpoint(playerid);
        void    set_player_world_bounds(int player_id, float x_max, float x_min, float y_max, float y_min); // SetPlayerWorldBounds(playerid,Float:x_max,Float:x_min,Float:y_max,Float:y_min);
        void    set_player_marker_for_player(int player_id, int show_player_id, unsigned color); // SetPlayerMarkerForPlayer(playerid, showplayerid, color);
        void    show_player_name_tag_for_player(int player_id, int show_player_id, bool show); // ShowPlayerNameTagForPlayer(playerid, showplayerid, show);
        void    set_player_mapicon(int player_id, int icon_id, float x, float y, float z, int markertype, unsigned color); // SetPlayerMapIcon(playerid, iconid, Float:x, Float:y, Float:z, markertype, color);
        void    remove_player_mapicon(int player_id, int icon_id); // RemovePlayerMapIcon(playerid, iconid);
        void    allow_player_teleport(int player_id, bool allow); // AllowPlayerTeleport(playerid, allow);

        // Player camera
        void    set_player_camera_pos(int player_id, float x, float y, float z); // SetPlayerCameraPos(playerid,Float:x, Float:y, Float:z);
        //void    set_player_camera_look_at(int player_id, float x, float y, float z); // SetPlayerCameraLookAt(playerid, Float:x, Float:y, Float:z);
        void    set_camera_behind_player(int player_id); // SetCameraBehindPlayer(playerid);
        void    get_player_camera_pos(int player_id, float& x, float& y, float& z); // GetPlayerCameraPos(playerid, &Float:x, &Float:y, &Float:z);
        void    get_player_camera_front_vector(int player_id, float& x, float& y, float& z); // GetPlayerCameraFrontVector(playerid, &Float:x, &Float:y, &Float:z);

        // Player conditionals
        bool    is_player_connected(int player_id); // IsPlayerConnected(playerid);
        bool    is_player_in_vehicle(int player_id, int vehicle_id); // IsPlayerInVehicle(playerid, vehicleid);
        bool    is_player_in_any_vehicle(int player_id); // IsPlayerInAnyVehicle(playerid);
        bool    is_player_in_checkpoint(int player_id); // IsPlayerInCheckpoint(playerid);
        bool    is_player_in_race_checkpoint(int player_id); // IsPlayerInRaceCheckpoint(playerid);

        // Virtual Worlds
        void    set_player_virtual_world(int player_id, int world_id); // SetPlayerVirtualWorld(playerid, worldid);
        int     get_player_virtual_world(int player_id); // GetPlayerVirtualWorld(playerid);

        // Insane Stunts
        void    enable_stunt_bonus_for_player(int player_id, bool enable); // EnableStuntBonusForPlayer(playerid, enable);
        void    enable_stunt_bonus_for_all(bool enable); // EnableStuntBonusForAll(enable);

        // Spectating
        void    toggle_player_spectating(int player_id, bool toggle); // TogglePlayerSpectating(playerid, toggle);
        void    player_spectate_player(int player_id, int target_player_id, spectate_mode mode = SPECTATE_MODE_NORMAL); // PlayerSpectatePlayer(playerid, targetplayerid, mode = SPECTATE_MODE_NORMAL);
        void    player_spectate_vehicle(int player_id, int target_vehicle_id, spectate_mode mode = SPECTATE_MODE_NORMAL); // PlayerSpectateVehicle(playerid, targetvehicleid, mode = SPECTATE_MODE_NORMAL);

        // Recording for NPC playback
        void    start_recording_player_data(int player_id, player_recording_type record_type, std::string const& record_name); // StartRecordingPlayerData(playerid, recordtype, recordname[]);
        void    stop_recording_player_data(int player_id); // StopRecordingPlayerData(playerid);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // a_samp.inc
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Util - далеко не все нативы тут, в связи со своей ненужностью в C++
        void    send_client_message(int player_id, unsigned color, std::string const& message); // SendClientMessage(playerid, color, const message[]);
        void    send_player_message_to_player(int player_id, int sender_id, std::string const& message); // SendPlayerMessageToPlayer(playerid, senderid, const message[]);
        void    send_death_message(int killer_id, int killed_id, int weapon_id); // SendDeathMessage(killer,killee,weapon);
        void    game_text_for_player(int player_id, std::string const& string, int time, int style); // GameTextForPlayer(playerid,const string[],time,style);
        int     get_max_players(); // GetMaxPlayers();

        // Game
        void    set_game_mode_text(std::string const& text); // SetGameModeText(const string[]);
        void    set_team_count(int count); // SetTeamCount(count);
        int     add_player_class(int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3); // AddPlayerClass(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
        int     add_player_class_ex(int team_id, int skin_id, float x, float y, float z, float rz, int weapon_id1, int weapon_ammo1, int weapon_id2, int weapon_ammo2, int weapon_id3, int weapon_ammo3); // AddPlayerClassEx(teamid, modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
        void    add_static_vehicle(int model_id, float x, float y, float z, float rz, int color_id1, int color_id2); // AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2);
        int     add_static_vehicle_ex(int model_id, float x, float y, float z, float rz, int color_id1, int color_id2, int respawn_delay); // AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay);
        void    add_static_pickup(int model, int type, float x, float y, float z, int virtual_world); // AddStaticPickup(model, type, Float:X, Float:Y, Float:Z, virtualworld = 0);
        int     create_pickup(int model, int type, float x, float y, float z, int virtual_world); // CreatePickup(model, type, Float:X, Float:Y, Float:Z, virtualworld = 0);
        void    destroy_pickup(int pickup_id); // DestroyPickup(pickup);
        void    show_name_tags(bool is_show); // ShowNameTags(show);
        void    show_player_markers(player_markers_mode mode); // ShowPlayerMarkers(mode);
        void    gamemode_exit(); // GameModeExit();
        void    set_world_time(int hour); // SetWorldTime(hour);
        std::string get_weapon_name(int weapon_id); // GetWeaponName(weaponid, const weapon[], len);
        void    enable_tire_popping(bool is_enable); // EnableTirePopping(enable);
        void    allow_interior_weapons(bool is_allow); // AllowInteriorWeapons(allow);
        void    set_weather(int weather_id); // SetWeather(weatherid);
        void    set_gravity(float gravity); // SetGravity(Float:gravity);
        void    allow_admin_teleport(bool is_allow); // AllowAdminTeleport(allow);
        void    set_death_drop_amount(int amount); // SetDeathDropAmount(amount);
        void    create_explosion(float x, float y, float z, int type, float radius); // CreateExplosion(Float:X, Float:Y, Float:Z, type, Float:Radius);
        void    enable_zone_names(bool is_enable); // EnableZoneNames(enable);
        void    use_player_ped_anims(); // UsePlayerPedAnims(); Will cause the players to use CJ running/walking animations
        void    disable_interior_enter_exits(); // DisableInteriorEnterExits();  will disable all interior enter/exits in the game.
        void    set_name_tag_draw_distance(float distance); // SetNameTagDrawDistance(Float:distance); Distance at which nametags will start rendering on the client.
        void    disable_name_tag_los(); // DisableNameTagLOS(); // Disables the nametag Line-Of-Sight checking
        void    limit_global_chat_radius(float chat_radius); // LimitGlobalChatRadius(Float:chat_radius);
        void    limit_player_marker_radius(float marker_radius); // LimitPlayerMarkerRadius(Float:marker_radius);

        // Npc
        void    connect_npc(std::string const& name, std::string const& script); // ConnectNPC(name[], script[]);
        bool    is_player_npc(int player_id); // IsPlayerNPC(playerid);

        // Admin
        bool    is_player_admin(int player_id); // IsPlayerAdmin(playerid);
        void    kick(int player_id); // Kick(playerid);
        void    ban(int player_id); // Ban(playerid);
        void    ban_ex(int player_id, std::string const& reason); // BanEx(playerid, const reason[]);
        void    send_rcon_command(std::string const& command); // SendRconCommand(command[]);
        std::string get_server_var_as_string(std::string const& var_name); // GetServerVarAsString(const varname[], buffer[], len);
        int     get_server_var_as_int(std::string const& var_name); // GetServerVarAsInt(const varname[]);
        bool    get_server_var_as_bool(std::string const& var_name); // GetServerVarAsBool(const varname[]);

        // Menu
        int     create_menu(std::string const& title, int columns, float x, float y, float col1width, float col2width); // CreateMenu(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0);
        void    destroy_menu(int menu_id); // DestroyMenu(Menu:menuid);
        void    add_menu_item(int menu_id, int column, std::string const& text); // AddMenuItem(Menu:menuid, column, const menutext[]);
        void    set_menu_column_header(int menu_id, int column, std::string const& header); // SetMenuColumnHeader(Menu:menuid, column, const columnheader[]);
        void    show_menu_for_player(int menu_id, int player_id); // ShowMenuForPlayer(Menu:menuid, playerid);
        void    hide_menu_for_player(int menu_id, int player_id); // HideMenuForPlayer(Menu:menuid, playerid);
        bool    is_valid_menu(int menu_id); // IsValidMenu(Menu:menuid);
        void    disable_menu(int menu_id); // DisableMenu(Menu:menuid);
        void    disable_menu_row(int menu_id, int row); // DisableMenuRow(Menu:menuid, row);
        int     get_player_menu(int player_id); // GetPlayerMenu(playerid);

        // Text Draw
        int     textdraw_create(float x, float y, std::string const& text); // TextDrawCreate(Float:x, Float:y, text[]);
        void    textdraw_destroy(int text_id); // TextDrawDestroy(Text:text);
        void    textdraw_letter_size(int text_id, float x, float y); // TextDrawLetterSize(Text:text, Float:x, Float:y);
        void    textdraw_text_size(int text_id, float x, float y); // TextDrawTextSize(Text:text, Float:x, Float:y);
        void    textdraw_alignment(int text_id, int alignment); // TextDrawAlignment(Text:text, alignment);
        void    textdraw_color(int text_id, unsigned color); // TextDrawColor(Text:text, color);
        void    textdraw_use_box(int text_id, int use); // TextDrawUseBox(Text:text, use);
        void    textdraw_box_color(int text_id, unsigned color); // TextDrawBoxColor(Text:text, color);
        void    textdraw_set_shadow(int text_id, int size); // TextDrawSetShadow(Text:text, size);
        void    textdraw_set_outline(int text_id, int size); // TextDrawSetOutline(Text:text, size);
        void    textdraw_background_color(int text_id, unsigned color); // TextDrawBackgroundColor(Text:text, color);
        void    textdraw_font(int text_id, int font); // TextDrawFont(Text:text, font);
        void    textdraw_set_proportional(int text_id, bool set); // TextDrawSetProportional(Text:text, set);
        void    textdraw_show_for_player(int player_id, int text_id); // TextDrawShowForPlayer(playerid, Text:text);
        void    textdraw_hide_for_player(int player_id, int text_id); // TextDrawHideForPlayer(playerid, Text:text);
        void    textdraw_set_string(int text_id, std::string const& text); // TextDrawSetString(Text:text, string[]);

        // Gang Zones
        int     gangzone_create(float minx, float miny, float maxx, float maxy); // GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy);
        void    gangzone_destroy(int zone_id); // GangZoneDestroy(zone);
        void    gangzone_show_for_player(int player_id, int zone_id, unsigned int color); // GangZoneShowForPlayer(playerid, zone, color);
        void    gangzone_hide_for_player(int player_id, int zone_id); // GangZoneHideForPlayer(playerid, zone);
        void    gangzone_flash_for_player(int player_id, int zone_id, unsigned int flashcolor); // GangZoneFlashForPlayer(playerid, zone, flashcolor);
        void    gangzone_stop_flash_for_player(int player_id, int zone_id); // GangZoneStopFlashForPlayer(playerid, zone);

        // Global 3D Text Labels
        int     create_3dtextlabel(std::string const& text, unsigned int color, float x, float y, float z, float draw_distance, int world, bool is_test_los = true); // Text3D:Create3DTextLabel(text[], color, Float:X, Float:Y, Float:Z, Float:DrawDistance, virtualworld, testLOS=0);
        void    delete_3dtextlabel(int text3d_id); // Delete3DTextLabel(Text3D:id);
        void    attach_3dtextlabel_to_player(int text3d_id, int player_id, float offset_x, float offset_y, float offset_z); // Attach3DTextLabelToPlayer(Text3D:id, playerid, Float:OffsetX, Float:OffsetY, Float:OffsetZ);
        void    attach_3dtextlabel_to_vehicle(int text3d_id, int vehicle_id, float offset_x, float offset_y, float offset_z); // Attach3DTextLabelToVehicle(Text3D:id, vehicleid, Float:OffsetX, Float:OffsetY, Float:OffsetZ);
        void    update_3dtextlabel_text(int text3d_id, unsigned int color, std::string const& text); // Update3DTextLabelText(Text3D:id, color, text[]);

        // Per-player 3D Text Labels
        int     create_player3dtextlabel(int player_id, std::string const& text, unsigned int color, float x, float y, float z, float draw_distance, int attached_player_id = INVALID_PLAYER_ID, int attached_vehicle_id = INVALID_VEHICLE_ID, bool is_test_los = true); // PlayerText3D:CreatePlayer3DTextLabel(playerid, text[], color, Float:X, Float:Y, Float:Z, Float:DrawDistance, attachedplayer=INVALID_PLAYER_ID, attachedvehicle=INVALID_VEHICLE_ID, testLOS=0);
        void    delete_player3dtextlabel(int player_id, int playertext3d_id); // DeletePlayer3DTextLabel(playerid, PlayerText3D:id);
        void    update_player3dtextlabel_text(int player_id, int playertext3d_id, unsigned int color, std::string const& text); // UpdatePlayer3DTextLabelText(playerid, PlayerText3D:id, color, text[]);

        // Player GUI Dialog
        void    show_player_dialog(int player_id, int dialog_id, dialog_style style, std::string const& caption, std::string const& info, std::string const& button_ok, std::string const& button_cancel); // ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[]);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // a_vehicles.inc
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Vehicle
        int     create_vehicle(int vehicle_model, float x, float y, float z, float rz, int color_id1, int color_id2, int respawn_delay); // CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay);
        void    destroy_vehicle(int vehicle_id); // DestroyVehicle(vehicleid);
        bool    is_vehicle_streamed_in(int vehicle_id, int for_player_id); // IsVehicleStreamedIn(vehicleid, forplayerid);
        void    get_vehicle_pos(int vehicle_id, float& x, float& y, float& z); // GetVehiclePos(vehicleid, &Float:x, &Float:y, &Float:z);
        void    set_vehicle_pos(int vehicle_id, float x, float y, float z); // SetVehiclePos(vehicleid, Float:x, Float:y, Float:z);
        float   get_vehicle_zangle(int vehicle_id); // GetVehicleZAngle(vehicleid, &Float:z_angle);
        void    get_vehicle_rotation_quat(int vehicle_id, float& w, float& x, float& y, float& z); // GetVehicleRotationQuat(vehicleid, &Float:w, &Float:x, &Float:y, &Float:z);
        void    set_vehicle_zangle(int vehicle_id, float rz); // SetVehicleZAngle(vehicleid, Float:z_angle);
        void    set_vehicle_params_for_player(int vehicle_id, int player_id, bool objective, bool doorslocked); // SetVehicleParamsForPlayer(vehicleid,playerid,objective,doorslocked);
        void    set_vehicle_to_respawn(int vehicle_id); // SetVehicleToRespawn(vehicleid);
        void    link_vehicle_to_interior(int vehicle_id, int interior_id); // LinkVehicleToInterior(vehicleid, interiorid);
        void    add_vehicle_component(int vehicle_id, int component_id); // AddVehicleComponent(vehicleid, componentid);
        void    remove_vehicle_component(int vehicle_id, int component_id); // RemoveVehicleComponent(vehicleid, componentid);
        void    change_vehicle_color(int vehicle_id, int color_id1, int color_id2); // ChangeVehicleColor(vehicleid, color1, color2);
        void    change_vehicle_paintjob(int vehicle_id, int paintjob_id); // ChangeVehiclePaintjob(vehicleid, paintjobid);
        void    set_vehicle_health(int vehicle_id, float health); // SetVehicleHealth(vehicleid, Float:health);
        float   get_vehicle_health(int vehicle_id); // GetVehicleHealth(vehicleid, &Float:health);
        void    attach_trailer_to_vehicle(int trailer_id, int vehicle_id); // AttachTrailerToVehicle(trailerid, vehicleid);
        void    detach_trailer_from_vehicle(int vehicle_id); // DetachTrailerFromVehicle(vehicleid);
        bool    is_trailer_attached_to_vehicle(int vehicle_id); // IsTrailerAttachedToVehicle(vehicleid);
        int     get_vehicle_trailer(int vehicle_id); // GetVehicleTrailer(vehicleid);
        void    set_vehicle_number_plate(int vehicle_id, std::string const& numberplate); // SetVehicleNumberPlate(vehicleid, numberplate[]);
        int     get_vehicle_model(int vehicle_id); // GetVehicleModel(vehicleid);
        int     get_vehicle_component_in_slot(int vehicle_id, carmod_type slot); // GetVehicleComponentInSlot(vehicleid, slot); // There is 1 slot for each CARMODTYPE_*
        carmod_type get_vehicle_component_type(int component_id); // GetVehicleComponentType(component); // Find CARMODTYPE_* for component id
        void    repair_vehicle(int vehicle_id); // RepairVehicle(vehicleid); // Repairs the damage model and resets the health
        void    get_vehicle_velocity(int vehicle_id, float& x, float& y, float& z); // GetVehicleVelocity(vehicleid, &Float:X, &Float:Y, &Float:Z);
        void    set_vehicle_velocity(int vehicle_id, float x, float y, float z); // SetVehicleVelocity(vehicleid, Float:X, Float:Y, Float:Z);
        void    set_vehicle_angular_velocity(int vehicle_id, float x, float y, float z); // SetVehicleAngularVelocity(vehicleid, Float:X, Float:Y, Float:Z);
        void    get_vehicle_damage_status(int vehicle_id, int& panels, int& doors, int& lights, int& tires); // GetVehicleDamageStatus(vehicleid, &panels, &doors, &lights, &tires);
        void    update_vehicle_damage_status(int vehicle_id, int panels, int doors, int lights, int tires); // UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
        
        // Virtual Worlds
        void set_vehicle_virtual_world(int vehicle_id, int world_id); // SetVehicleVirtualWorld(vehicleid, worldid);
        int get_vehicle_virtual_world(int vehicle_id); // GetVehicleVirtualWorld(vehicleid);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Недокументированные возможности
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // В сампе 0.3b возращает хеш пути к "GTA San Andreas User Files" в моих документах
        std::string get_serial(int player_id); // gpci(playerid, serial[], len);
        
        
        // 0.3e
        
        void manual_vehicle_engine_and_lights (); // native ManualVehicleEngineAndLights();
		void set_vehicle_params_ex (int vehicleid, int engine, int lights, int alarm, int doors, int bonnet, int boot, int objective); // native SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		void get_vehicle_params_ex (int vehicleid, int& engine, int& lights, int& alarm, int& doors, int& bonnet, int& boot, int& objective); // native GetVehicleParamsEx(vehicleid, &engine, &lights, &alarm, &doors, &bonnet, &boot, &objective);
		void get_vehicle_model_info (int vehiclemodel, int infotype, float& X, float& Y, float& Z); // native GetVehicleModelInfo(vehiclemodel, infotype, &Float:X, &Float:Y, &Float:Z);
		int get_vehicle_virtual_world (int vehicleid); // native GetVehicleVirtualWorld(vehicleid);
        int get_player_target_player (int playerid); // native GetPlayerTargetPlayer(playerid);
        int play_audio_stream_for_player (int playerid, const std::string& url, float posX, float posY, float posZ, float distance, int usepos); // native PlayAudioStreamForPlayer(playerid, url[], Float:posX = 0.0, Float:posY = 0.0, Float:posZ = 0.0, Float:distance = 50.0, usepos = 0);
        int stop_audio_stream_for_player (int playerid); // native StopAudioStreamForPlayer(playerid);
        int get_player_surfing_object_id (int playerid); // native GetPlayerSurfingObjectID(playerid);
        int remove_building_for_player (int playerid, int modelid, float fX, float fY, float fZ, float fRadius); // native RemoveBuildingForPlayer(playerid, modelid, Float:fX, Float:fY, Float:fZ, Float:fRadius);






        //int attach_object_to_vehicle (int objectid, int vehicleid, float OffsetX, float OffsetY, float OffsetZ, float RotX, float RotY, float RotZ); // native AttachObjectToVehicle(objectid, vehicleid, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:RotX, Float:RotY, Float:RotZ);
        int attach_object_to_object (int objectid, int attachtoid, float OffsetX, float OffsetY, float OffsetZ, float RotX, float RotY, float RotZ, int SyncRotation); // native AttachObjectToObject(objectid, attachtoid, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:RotX, Float:RotY, Float:RotZ, SyncRotation = 1);
        //int attach_object_to_player (int objectid, int playerid, float OffsetX, float OffsetY, float OffsetZ, float RotX, float RotY, float RotZ); // native AttachObjectToPlayer(objectid, playerid, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:RotX, Float:RotY, Float:RotZ);
        int move_object (int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ); // native MoveObject(objectid, Float:X, Float:Y, Float:Z, Float:Speed, Float:RotX = -1000.0, Float:RotY = -1000.0, Float:RotZ = -1000.0);
        int is_object_moving (int objectid); // native IsObjectMoving(objectid);
        int edit_object (int playerid, int objectid); // native EditObject(playerid, objectid);
        int edit_player_object (int playerid, int objectid); // native EditPlayerObject(playerid, objectid);
        int select_object (int playerid); // native SelectObject(playerid);
        int cancel_edit (int playerid); // native CancelEdit(playerid);
        int attach_player_object_to_vehicle (int playerid, int objectid, int vehicleid, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float RotZ); // native AttachPlayerObjectToVehicle(playerid, objectid, vehicleid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:RotZ);
        int move_player_object (int playerid, int objectid, float X, float Y, float Z, float Speed, float RotX, float RotY, float RotZ); // native MovePlayerObject(playerid, objectid, Float:X, Float:Y, Float:Z, Float:Speed, Float:RotX = -1000.0, Float:RotY = -1000.0, Float:RotZ = -1000.0);
        int is_player_object_moving (int playerid, int objectid); // native IsPlayerObjectMoving(playerid, objectid);
        int set_object_material (int objectid, int materialindex, int modelid, std::string& txdname, std::string& texturename, int materialcolor=0); // native SetObjectMaterial(objectid, materialindex, modelid, txdname[], texturename[], materialcolor=0);
        int set_player_object_material (int playerid, int objectid, int materialindex, int modelid, std::string& txdname, std::string& texturename, int materialcolor=0); // native SetPlayerObjectMaterial(playerid, objectid, materialindex, modelid, txdname[], texturename[], materialcolor=0);
        int set_object_material_text (int objectid, std::string& text, int materialindex, int materialsize, std::string& fontface, int fontsize, int bold, int fontcolor, int backcolor, int textalignment); // native SetObjectMaterialText(objectid, text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128, fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0);
        int set_player_object_material_text (int playerid, int objectid, std::string& text, int materialindex, int materialsize, std::string& fontface, int fontsize, int bold, int fontcolor, int backcolor, int textalignment); // native SetPlayerObjectMaterialText(playerid, objectid, text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128, fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0);/*  SA-MP Player Functions
        float get_player_distance_from_point (int playerid, float X, float Y, float Z); // native Float:GetPlayerDistanceFromPoint(playerid, Float:X, Float:Y, Float:Z);

        int set_player_attached_object (int playerid, int index, int modelid, int bone, float fOffsetX, float fOffsetY, float fOffsetZ, float fRotX, float fRotY, float fRotZ, float fScaleX, float fScaleY, float fScaleZ, int materialcolor1, int materialcolor2); // native SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0, materialcolor1 = 0, materialcolor2 = 0);
        //int remove_player_attached_object (int playerid, int index); // native RemovePlayerAttachedObject(playerid, index);
        //int is_player_attached_object_slot_used (int playerid, int index); // native IsPlayerAttachedObjectSlotUsed(playerid, index);
        int edit_attached_object (int playerid, int index); // native EditAttachedObject(playerid, index);

        /*
        playertext create_player_text_draw (int playerid, float x, float y, std::string& text); // native PlayerText:CreatePlayerTextDraw(playerid, Float:x, Float:y, text[]);
        int player_text_draw_destroy (int playerid, playertext text); // native PlayerTextDrawDestroy(playerid, PlayerText:text);
        int player_text_draw_letter_size (int playerid, playertext text, float x, float y); // native PlayerTextDrawLetterSize(playerid, PlayerText:text, Float:x, Float:y);
        int player_text_draw_text_size (int playerid, playertext text, float x, float y); // native PlayerTextDrawTextSize(playerid, PlayerText:text, Float:x, Float:y);
        int player_text_draw_alignment (int playerid, playertext text, int alignment); // native PlayerTextDrawAlignment(playerid, PlayerText:text, alignment);
        int player_text_draw_color (int playerid, playertext text, int color); // native PlayerTextDrawColor(playerid, PlayerText:text, color);
        int player_text_draw_use_box (int playerid, playertext text, int use); // native PlayerTextDrawUseBox(playerid, PlayerText:text, use);
        int player_text_draw_box_color (int playerid, playertext text, int color); // native PlayerTextDrawBoxColor(playerid, PlayerText:text, color);
        int player_text_draw_set_shadow (int playerid, playertext text, int size); // native PlayerTextDrawSetShadow(playerid, PlayerText:text, size);
        int player_text_draw_set_outline (int playerid, playertext text, int size); // native PlayerTextDrawSetOutline(playerid, PlayerText:text, size);
        int player_text_draw_background_color (int playerid, playertext text, int color); // native PlayerTextDrawBackgroundColor(playerid, PlayerText:text, color);
        int player_text_draw_font (int playerid, playertext text, int font); // native PlayerTextDrawFont(playerid, PlayerText:text, font);
        int player_text_draw_set_proportional (int playerid, playertext text, int set); // native PlayerTextDrawSetProportional(playerid, PlayerText:text, set);
        int player_text_draw_set_selectable (int playerid, playertext text, int set); // native PlayerTextDrawSetSelectable(playerid, PlayerText:text, set);
        int player_text_draw_show (int playerid, playertext text); // native PlayerTextDrawShow(playerid, PlayerText:text);
        int player_text_draw_hide (int playerid, playertext text); // native PlayerTextDrawHide(playerid, PlayerText:text);
        int player_text_draw_set_string (int playerid, playertext text, std::string& string); // native PlayerTextDrawSetString(playerid, PlayerText:text, string[]);
        */

        int set_player_map_icon (int playerid, int iconid, float x, float y, float z, int markertype, int color, int style); // native SetPlayerMapIcon(playerid, iconid, Float:x, Float:y, Float:z, markertype, color, style = MAPICON_LOCAL);
        int set_player_camera_look_at (int playerid, float x, float y, float z, camera_cut cut = CAMERA_CUT); // native SetPlayerCameraLookAt(playerid, Float:x, Float:y, Float:z, cut = CAMERA_CUT);
        int get_player_camera_mode (int playerid); // native GetPlayerCameraMode(playerid);
        int attach_camera_to_object (int playerid, int objectid); // native AttachCameraToObject(playerid, objectid);
        int attach_camera_to_player_object (int playerid, int playerobjectid); // native AttachCameraToPlayerObject(playerid, playerobjectid);
        int interpolate_camera_pos (int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, camera_cut cut = CAMERA_CUT); // native InterpolateCameraPos(playerid, Float:FromX, Float:FromY, Float:FromZ, Float:ToX, Float:ToY, Float:ToZ, time, cut = CAMERA_CUT);
        int interpolate_camera_look_at (int playerid, float FromX, float FromY, float FromZ, float ToX, float ToY, float ToZ, int time, camera_cut cut = CAMERA_CUT); // native InterpolateCameraLookAt(playerid, Float:FromX, Float:FromY, Float:FromZ, Float:ToX, Float:ToY, Float:ToZ, time, cut = CAMERA_CUT);
        //int stop_recording_player_data (int playerid); // native StopRecordingPlayerData(playerid);


        /*
        int select_text_draw (int playerid, int hovercolor); // native SelectTextDraw(playerid, hovercolor); // enables the mouse so the player can select a textdraw
        int cancel_select_text_draw (int playerid); // native CancelSelectTextDraw(playerid);	// cancel textdraw selection with the mouse
        int get_player_network_stats (int playerid, std::string& retstr, int retstr_size); // native GetPlayerNetworkStats(playerid, retstr[], retstr_size);
        int get_network_stats (string retstr, int retstr_size); // native GetNetworkStats(retstr[], retstr_size);
        int get_player_version (int playerid, const std::string& version, int len); // native GetPlayerVersion(playerid, const version[], len); // Returns the SA-MP client revision as reported by the player
        int text_draw_set_selectable (text text, int set); // native TextDrawSetSelectable(Text:text, set);
        float get_vehicle_distance_from_point (int vehicleid, float X, float Y, float Z); // native Float:GetVehicleDistanceFromPoint(vehicleid, Float:X, Float:Y, Float:Z);
        */

} // namespace 

#endif // PAWN_NATIVES_H


