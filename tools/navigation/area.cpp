#include "area.hpp"
#include "structs.h"
#include <cstdio>
#include <cassert>


void area::init(const char * filename)
{
  if(initialized)
    return;
  FILE * fp = fopen(filename, "rb");
  assert(!!fp);
  size_t res;
  // header
  res = fread(&hdr, sizeof(header), 1, fp);
  assert(res == 1);
  // check
  assert(hdr.nodes == hdr.vehicle_nodes + hdr.ped_nodes);
  assert(hdr.nodes > 0);
  
  // fill
#define FILL(type, var, count, stream) var = new type [ count ] ; res = fread( var, sizeof ( type ), count, stream ) ; assert ( res == count ) ;
  /*
  vehicle_nodes = new path_node[hdr.vehicle_nodes];
  fread(vehicle_nodes, sizeof(path_node), hdr.vehicle_nodes, fp);
  
  ped_nodes = new path_node[hdr.ped_nodes];
  fread(ped_nodes, sizeof(path_node), hdr.ped_nodes, fp);
  
  navi_nodes = new navi_node[hdr.navi_nodes];
  fread(navi_nodes, sizeof(navi_node), hdr.navi_nodes, fp);
  */
  FILL(path_node, vehicle_nodes, hdr.vehicle_nodes, fp)
  FILL(path_node, ped_nodes, hdr.ped_nodes, fp)
  
  FILL(navi_node, navi_nodes, hdr.navi_nodes, fp)
  
  FILL(path_link, links, hdr.links, fp)
  
  fseek(fp, 768, SEEK_CUR); // skip 768 bytes
  
  FILL(navi_link, navi_links, hdr.links, fp)
  
  FILL(link_len, link_lens, hdr.links, fp)
  
#undef FILL
  // done
  fclose(fp);
  initialized = true;
}
