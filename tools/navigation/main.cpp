
#include "progress.hpp"



#include "structs.h"
#include "area.hpp"
#include "graph.hpp"


#include <iostream>

int main()
{
  graph g;
  {
    areas ars;
    ars.init("paths");
    ars.to_graph(g);
  }
  
  fordbellman path(g);
  auto t = g.find_nearest(-200., -200., 0.);
  std::cout << t.x << ' ' << t.y << ' ' << t.z << std::endl;
  auto y = g.find_nearest(200., 200., 0.);
  std::cout << y.x << ' ' << y.y << ' ' << y.z << std::endl;
  path.calculate(t);
  std::cout << path.distance(y) << std::endl;
  
  return 0;
}
