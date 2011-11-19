

#include "progress.hpp"



#include "structs.h"
#include "area.hpp"
#include "graph.hpp"


#include <iostream>

#include <cstdlib>


#include <fstream>

#include <list>

bool read_coords(std::istream& s, double& x, double& y, double& z)
{
  s >> x;
  s >> y;
  s >> z;
  
  return(!s.eof() && (x != 0. && y != 0. && z != 0.));
}
void write_coords(std::ostream& s, double x, double y, double z)
{
  s << x << ' ';
  s << y << ' ';
  s << z << std::endl;
}

void write_path(std::ostream& s, const path_t& path)
{
  for(vertex i : path)
    write_coords(s, i.x, i.y, i.z);
}

int main(int argc, const char * argv[])
{
  int type = 1;
  if(argc > 1)
    type = atoi(argv[1]);
  graph g;
  {
    areas ars;
    if(argc > 2)
      ars.init(argv[2]);
    else
      ars.init("paths");
    ars.to_graph(g, type);
  }
  std::cout << g.v_size() << " nodes and " << g.e_size() << " edges parsed" << std::endl;
  
  fordbellman path(g);
  /*
  auto t = g.find_nearest(-200., -200., 0.);
  std::cout << t.x << ' ' << t.y << ' ' << t.z << std::endl;
  auto y = g.find_nearest(200., 200., 0.);
  std::cout << y.x << ' ' << y.y << ' ' << y.z << std::endl;
  path.calculate(t);
  std::cout << path.distance(y) << std::endl;
  std::vector<vertex> p;
  path.shortest_path(p, y);
  for(vertex it : p)
  {
    std::cout << it.x << ' ' << it.y << ' ' << it.z << std::endl;
  }*/
  std::cout << "--------" << std::endl;
  
  std::ifstream in("navigation.in");
  std::ofstream out("navigation.out");
  
  double x, y, z;
  read_coords(in, x, y, z);
  vertex source = g.find_nearest(x, y, z);
  
  
  while(read_coords(in, x, y, z))
  {
    vertex target = g.find_nearest(x, y, z);
    
    write_coords(std::cout, source.x, source.y, source.z);
    write_coords(std::cout, target.x, target.y, target.z);
    
    path.calculate(source);
    std::cout << "distance: " << path.distance(target) << std::endl;
    
    path_t min_path;
    path.shortest_path(min_path, target);
    std::cout << "edges: " << min_path.size() << std::endl;
    write_path(out, min_path);
    std::cout << "--------" << std::endl;
    
    source = target;
  }
  
  return 0;
}
