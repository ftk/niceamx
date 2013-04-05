#ifndef API_STREAMER_HPP
#define API_STREAMER_HPP
// OBSOLETE

// macros

#define STREAMER_MAP_X_MAX 3000
#define STREAMER_MAP_Y_MAX 3000
#define STREAMER_MAP_X_MIN (-3000)
#define STREAMER_MAP_Y_MIN (-3000)

#define STREAMER_MAP_X_TOTAL (STREAMER_MAP_X_MAX - STREAMER_MAP_X_MIN) // 6000
#define STREAMER_MAP_Y_TOTAL (STREAMER_MAP_Y_MAX - STREAMER_MAP_Y_MIN)

#ifndef STREAMER_CELL_SIZE
#define STREAMER_CELL_SIZE 600 // 600x600 m^2
#endif

#define STREAMER_CELL_X_AMOUNT (STREAMER_MAP_X_TOTAL / STREAMER_CELL_SIZE) // 10
#define STREAMER_CELL_Y_AMOUNT (STREAMER_MAP_Y_TOTAL / STREAMER_CELL_SIZE)

#define STREAMER_CELL_X_OFFSET (STREAMER_MAP_X_MIN / STREAMER_CELL_SIZE) // -5
#define STREAMER_CELL_Y_OFFSET (STREAMER_MAP_Y_MIN / STREAMER_CELL_SIZE)


//

#include "object.hpp"
#include "player.hpp"

#include "util/singleton.hpp"

#include <vector>

namespace api {


class streamer : public util::singleton<streamer>
{
protected:
  
  // assume we have only one streamer
  
  // singleton
  //static streamer * instance;
public:
  //static streamer * get_instance();
  //static void rm_instance();
  
protected:
  
  typedef std::vector<object> objects_t; 
  objects_t objects[STREAMER_CELL_X_AMOUNT][STREAMER_CELL_Y_AMOUNT]; // 100
 
    
protected:
  
  
  static inline bool is_valid_indexes(int x_idx, int y_idx)
  {
    return
    (
      (x_idx >= 0 && x_idx < STREAMER_CELL_X_AMOUNT) &&
      (y_idx >= 0 && y_idx < STREAMER_CELL_Y_AMOUNT) &&
      true
    );
  }
  
  static inline bool get_indexes(float x, float y, int& x_idx, int& y_idx)
  {
    x_idx = int(x / STREAMER_CELL_SIZE) - STREAMER_CELL_X_OFFSET;
    y_idx = int(y / STREAMER_CELL_SIZE) - STREAMER_CELL_Y_OFFSET;
    return is_valid_indexes(x_idx, y_idx);
  }
  
  static bool stream_objects(const basic_player& p, objects_t & objs);

  
public:
  
  

  inline bool insert(const object& o)
  {
    int x_idx, y_idx;
    if(get_indexes(o.pos.x, o.pos.y, x_idx, y_idx))
    {
      objects[x_idx][y_idx].push_back(o);
      return true;
    }
    return false;
  }
  

  bool stream(const basic_player& p); // returns true if each object is properly streamed

  void hide_all(const basic_player& p);
  
public:
  struct exception {};
};


}

#define STREAMER (api::streamer::get_instance())

#endif
