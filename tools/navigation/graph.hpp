#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <list>

struct vertex
{
  double x, y, z;
  
  int id;
  
  vertex() : x(0.), y(0.), z(0.), id(0) {}
  
  inline bool operator == (const vertex& rhs) const
  {
    return x == rhs.x && y == rhs.y && z == rhs.z && id == rhs.id;
  }
  inline bool operator < (const vertex& rhs) const
  {
    return id < rhs.id;
  }
};

struct adjacent_edge
{
  vertex tail;
  
  int weight;
  
  adjacent_edge(vertex a, int b) : tail(a), weight(b) {}
};

class graph
{
private:
  typedef std::list<adjacent_edge> adjacency_list;
  std::map<vertex, adjacency_list> list;
public:
  void add_adjacent_edge(vertex head, adjacent_edge e)
  {
    list[head].push_back(e);
  }
};

#endif
