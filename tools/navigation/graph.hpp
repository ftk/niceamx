#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>

struct vertex
{
  double x, y, z;
};

struct adjacent_edge
{
  vertex tail;
  
  int weight;
};

class graph
{
};

#endif
