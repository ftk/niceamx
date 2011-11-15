#include "structs.h"
#include "area.hpp"

int main()
{
  areas ars;
  ars.init("paths");
  graph g;
  ars.to_graph(g);
  
  forbellman path(g);
  
  
  return 0;
}
