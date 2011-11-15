#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <boost/static_assert.hpp> 


#pragma pack(push)

// http://www.gtamodding.com/index.php?title=Paths_%28GTA_SA%29

#pragma pack(1) // 1-byte alignement
struct header
{
  uint32_t nodes;
  uint32_t vehicle_nodes;
  uint32_t ped_nodes;
  uint32_t navi_nodes;
  uint32_t links;  
};
BOOST_STATIC_ASSERT(sizeof(header) == 20);


#pragma pack(1)
struct path_node
{
  uint32_t unused1; // unused
  uint32_t unused2; // unused
  
  int16_t x;
  int16_t y;
  int16_t z;
  
  int16_t unused3; // unused
  
  uint16_t link;
  uint16_t area;
  uint16_t node;
  
  uint8_t path_width;
  uint8_t type;
  
  struct flags_t // bitfield, uint32_t
  {
    unsigned links : 4; // links from (node::link) to (node::link + node::flags::links)
    unsigned traffic : 2; // unused
    // TODO: add more flags
    unsigned : 24; // unused
  } flags;
  BOOST_STATIC_ASSERT(sizeof(flags_t) == 4);
};
BOOST_STATIC_ASSERT(sizeof(path_node) == 28);

#pragma pack(1)
struct navi_node // unused
{
  int16_t x;
  int16_t y;
  
  uint16_t area;
  uint16_t node;
  
  int8_t dx;
  int8_t dy;
  
  uint32_t flags;
};
BOOST_STATIC_ASSERT(sizeof(navi_node) == 14);

#pragma pack(1)
struct path_link
{
  uint16_t area;
  uint16_t node;
};
BOOST_STATIC_ASSERT(sizeof(path_link) == 4);

#pragma pack(1)
struct navi_link // unused
{
  uint16_t unused;
};
BOOST_STATIC_ASSERT(sizeof(navi_link) == 2);

#pragma pack(1)
struct link_len
{
  uint8_t length;
};
BOOST_STATIC_ASSERT(sizeof(link_len) == 1);

#pragma pack(pop)

#endif
