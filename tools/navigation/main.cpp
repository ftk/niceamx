
#include "progress.hpp"



#include "structs.h"
#include "area.hpp"
#include "graph.hpp"


#include <iostream>

int main()
{
  areas ars;
  ars.init("paths");
  graph g;
  ars.to_graph(g);
  
  fordbellman path(g);
  auto t = g.find_nearest(-200., -200., 0.);
  path.calculate(t);
  auto y = g.find_nearest(200., 200., 0.);
  std::cout << path.distance(y) << std::endl;
  
  return 0;
}
