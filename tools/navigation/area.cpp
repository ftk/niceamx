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
  assert(hdr.links > 0);
  
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
  // check
  for(size_t i = 0; i < hdr.vehicle_nodes; i++)
  {
    assert(vehicle_nodes[i].node == i);
  }
  for(size_t i = 0; i < hdr.ped_nodes; i++)
  {
    assert(ped_nodes[i].node == i + hdr.vehicle_nodes);
  }
  /*
  for(size_t i = 0; i < hdr.links; i++)
  {
    //printf("%d %d %d\n", links[i].area, links[i].node, i);
    //assert(links[i].node == i);
  }*/
  
  // done
  fclose(fp);
  initialized = true;
}


void areas::init(const char * path)
{
  for(size_t i = 0; i < MAX_AREAS; i++)
  {
    char file[100];
    sprintf(file, "%s/NODES%d.dat", path, i);
    a[i].init(file);
    // check
    for(size_t j = 0; j < a[i].hdr.vehicle_nodes; j++)
    {
      assert(a[i].vehicle_nodes[j].area == i);
    }
    for(size_t j = 0; j < a[i].hdr.ped_nodes; j++)
    {
      assert(a[i].ped_nodes[j].area == i);
    }
    /*
    for(size_t j = 0; j < a[i].hdr.links; j++)
    {
      assert(a[i].links[j].area == i);
    }
    */

  }
}

void get_position(path_node node, double& x, double& y, double& z)
{
  // divide by 8
  x = static_cast<double>(node.x) / 8.0;
  y = static_cast<double>(node.y) / 8.0;
  z = static_cast<double>(node.z) / 8.0;
}

