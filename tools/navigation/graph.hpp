#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cassert>

#include <map>
#include <list>

#include <algorithm>

#include "progress.hpp"
#include <cstdio>

struct vertex
{
  double x, y, z;
  
  int id;
  
  vertex() : x(0.), y(0.), z(0.), id(0) {}
  
  inline bool operator == (const vertex& rhs) const
  {
    return (x == rhs.x && y == rhs.y && z == rhs.z) ;//|| id == rhs.id;
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

struct edge
{
  vertex head;
  vertex tail;
  
  int weight;
  
};

class fordbellman;

class graph
{
private:
  typedef std::list<adjacent_edge> adjacency_list;
  std::map<vertex, adjacency_list> list;
  
  std::vector<vertex> V;
  std::vector<edge> E;
  
public:
  void add_adjacent_edge(vertex head, adjacent_edge e)
  {
    add_vertex(head);
    add_vertex(e.tail);
    add_edge({head, e.tail, e.weight});
    
    list[head].push_back(e);
  }
  
private:
  bool find_vertex(vertex& dst)
  {
    auto it = std::find(V.begin(), V.end(), dst);
    if(it != V.end())
      dst.id = it->id;
    return(it != V.end());
  }
  void add_vertex(vertex& src)
  {
    static int id = 0;
    if(!find_vertex(src))
    {
      src.id = id++;
      V.push_back(src);
    }
    
  }
  
  void add_edge(edge e)
  {
    
    E.push_back(e);
  }
  /*
  int norm()
  {
    int id = 0;
    V.clear();
    V.reserve(list.size());
    E.clear();
    E.reserve(list.size() * 2);
    for(std::pair<vertex, adjacency_list> pair : list)
    {
      auto it = std::find(V.begin(), V.end(), pair.first);
      if(it == V.end())
      {
        pair.first.id = id++;
        V.push_back(pair.first);
      }
      else
      {
        assert(it->id < id);
        pair.first.id = it->id;
      }
      
      for(adjacent_edge edge : pair.second)
      {
        auto it2 = std::find(V.begin(), V.end(), edge.tail);
        if(it2 == V.end())
        {
          edge.tail.id = id++;
          V.push_back(edge.tail);
        }
        else
        {
          assert(it2->id < id);
          edge.tail.id = it2->id;
        }
        
        E.push_back({pair.first, edge.tail, edge.weight});
      }
    }
    return id;
    
  }*/
  
public:
  vertex find_nearest(double x, double y, double z)
  {
    double min_dist = 36000000.0;
    vertex res;
    
    assert(!V.empty());
    
    for(vertex& v : V)
    {
      double x1 = v.x - x;
      double y1 = v.y - y;
      double z1 = v.z - z;
      
      double dist = x1 * x1 + y1 * y1 + z1 * z1;
      if(dist < min_dist)
      {
        min_dist = dist;
        res = v;
      }
    }
    
    assert(res != vertex() && "couldnt find the nearest point");
    return res;
  }
  
  size_t v_size() const
  {
    return V.size();
  }
  size_t e_size() const
  {
    return E.size();
  }
  
  friend class fordbellman;
};

typedef std::list<vertex> path_t;

class fordbellman
{
private:
  graph& G;
  std::vector<size_t> dist;
  std::vector<int> previous;
  //std::map<vertex, vertex> previous;
public:
  fordbellman(graph& g_) : G(g_) {}
  
  
  
  void calculate(vertex s)
  {
    size_t size = G.V.size();
    //for(auto it = G.list.begin(); it != G.list.end(); ++it)
    //for(auto it : G.list)
    dist.clear();
    previous.clear();
    dist.reserve(size);
    previous.reserve(size);
    for(size_t i = 0; i < size; i++)
    {
      dist.push_back(1000000);
      previous.push_back(-1);
    }
    assert(G.find_vertex(s));
    dist.at(s.id) = 0;
    
    
    progress::progress_display timer(size);
    bool changed;
    for(size_t i = 0; i < size; i++)
    {
      changed = false;
      timer += 1;
      for(edge& e : G.E)
      {
        int v = e.head.id;
        int u = e.tail.id;
        register size_t tmp = dist[u] + e.weight;
        if(dist[v] >= tmp)
        {
          dist[v] = tmp;
          previous[v] = u;
          changed = true;
        }
      }

      if(!changed)
        break;
    }
    
  }
  
  void shortest_path(path_t& path, vertex dest)
  {
    int u = dest;
    while(previous[u] != -1)
    {
      vertex v;
      for(vertex& t : G.V)
      {
        if(t.id == u)
        {
          v = t;
          break;
        }
      }
      assert(v != vertex() && "not-connected graph?");
      
      path.push_front(v);
      u = previous[u];
    }
  }
  
  size_t distance(vertex dest)
  {
    assert(dist[dest] != 1000000 && "no path");
    return dist[dest];
  }
};


#endif
