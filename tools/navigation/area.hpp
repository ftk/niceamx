#ifndef AREA_HPP
#define AREA_HPP

#define MAX_AREAS 64


#include "structs.h"

class area // holds one area (one NODES*.dat file)
{
private:
  
  header hdr;

  path_node * vehicle_nodes;
  path_node * ped_nodes;
  
  navi_node * navi_nodes; // unused
  
  path_link * links;
  navi_link * navi_links; // unused
  link_len * link_lens;
  
  bool initialized;
public:
  area() : initialized(false) {}
  
  area(const char * filename) : initialized(false) 
  {
    init(filename);
  }
  
  void init(const char * filename);
  
  virtual ~area()
  {
    if(initialized)
    {
      delete [] vehicle_nodes;
      delete [] ped_nodes;
      delete [] navi_nodes;
      delete [] links;
      delete [] navi_links;
      delete [] link_lens;
    }
  }
};


#endif
