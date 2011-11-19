#include "samp.h"

#ifndef NDEBUG
#define TYPE "debug"
#else
#define TYPE ""
#endif

INIT
{
  REGISTER_CALLBACK(on_game_mode_init, []()
  {
    native::set_game_mode_text(__DATE__ " " __TIME__ " " TYPE);
    native::add_player_class(1, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    native::add_player_class(2, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
    native::add_player_class(180, 0.f, 0.f, 10.f, 0.f, 0,0, 0,0, 0,0);
  });
  
  REGISTER_CALLBACK(on_player_request_class, [](int id, int)
  {
    native::set_player_pos(id, 0.f, 0.f, 10.f);
    native::set_player_camera_pos(id, 0.f, 10.f, 10.f);
    native::set_player_camera_look_at(id, 0.f, 0.f, 10.f);
  });
  REGISTER_CALLBACK(on_player_spawn, [](int id)
  {
    native::set_camera_behind_player(id);
  });

}
