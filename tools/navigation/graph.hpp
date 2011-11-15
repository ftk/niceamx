#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <list>

#include <vector>
#include <queue>


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
  
  operator int()
  {
    return id;
  }
};

struct adjacent_edge
{
  vertex tail;
  
  int weight;
  
  adjacent_edge(vertex a, int b) : tail(a), weight(b) {}
};

class fordbellman;

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
  
  
  vertex find_nearest(double x, double y, double z)
  {
    
  }
  
  
  friend class fordbellman;
};


class fordbellman
{
private:
  graph& G;
  std::map<vertex, size_t> dist;
  std::map<vertex, vertex> previous;
public:
  fordbellman(graph& g_) : G(g_) {}
  
  
  
  void calculate(vertex s)
  {
    for(auto it = G.list.begin(); it != G.list.end(); ++it)
    //for(auto it : G.list)
    {
      dist[it->first] = 1000000;
      previous[it->first] = vertex();
    }
    dist[s] = 0;
    
    for(auto it = G.list.begin(); it != G.list.end(); ++it)
    {
      for(auto it2 : it->second)
      {
        vertex v = it->first, u = it2.tail;
        if(dist[v] >= dist[u] + it2.weight)
        {
          dist[v] = dist[u] + it2.weight;
          previous[v] = u;
        }
      }
    }
    
  }
  
  void shortest_path(std::vector<vertex>& path, vertex dest)
  {
    std::deque<vertex> S;
    vertex u = dest;
    while(previous[u] != vertex())
    {
      S.push_front(u);
      u = previous[u];
    }
    path.assign(S.begin(), S.end());
  }
  
  size_t distance(vertex dest)
  {
    return dist[dest];
  }
};


#endif
