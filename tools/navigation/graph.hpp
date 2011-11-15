#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cassert>

#include <map>
#include <list>

#include <vector>
#include <queue>

#include "progress.hpp"
#include <cstdio>

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
    double min_dist = 1000000.0;
    vertex res;
    
    for(auto it = list.begin(); it != list.end(); ++it)
    {
      double x1 = it->first.x - x;
      double y1 = it->first.y - y;
      double z1 = it->first.z - z;
      
      double dist = x1 * x1 + y1 * y1 + z1 * z1;
      if(dist < min_dist)
      {
        min_dist = dist;
        res = it->first;
      }
    }
    
    assert(res != vertex());
    return res;
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
    printf("calculating paths for %u nodes", G.list.size());
    for(auto it = G.list.begin(); it != G.list.end(); ++it)
    //for(auto it : G.list)
    {
      dist[it->first] = 1000000;
      previous[it->first] = vertex();
    }
    dist[s] = 0;
    
    progress::progress_display timer(G.list.size() * G.list.size());
    bool changed;
    for(size_t i = 0; i < G.list.size(); i++)
    {
      changed = false;
      for(auto it = G.list.begin(); it != G.list.end(); ++it)
      {
        timer += 1;
        const vertex& v = it->first;
        for(auto it2 : it->second)
        {
          const vertex& u = it2.tail;
          if(dist[v] >= dist[u] + it2.weight)
          {
            dist[v] = dist[u] + it2.weight;
            previous[v] = u;
            changed = true;
          }
        }
      }
      if(!changed)
        break;
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
