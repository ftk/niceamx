function make_car(x, y, z, a)
{
  printf "vcc, %.2f, %.2f, %.2f, %.2f, -1, -1;\n", x, y, z, a;
}


BEGIN {
  i=0;
  x = 2023.0;
  y = 750.0;
  while(i < 15)
  {
    make_car(x, y, 41.0, 45.0);
    i++;
    x -= 3.2;
    y -= 3.17;
  }
  #print "#---"
  i=0;
  x = 2071.0;
  y = 797.0;
  while(i < 37)
  {
    make_car(x, y, 41.0, 45.0);
    i++;
    x += 3.2;
    y += 3.17;
  }
  #print "#---"
  i=0;
  x = 2068.76;
  y = -651.0;
  while(i < 65)
  {
    make_car(x, y, 32.0, 180.0);
    i++;
    x += 4.1;
  }
  #print "#---"
  i=0;
  x = 1925.25;
  y = 1336.0;
  while(i < 12)
  {
    make_car(x, y, 21.0, 0.0);
    i++;
    x += 4.75;
  }
  #print "#---"
  i=0;
  x = 1293.72;
  y = 983.5;
  while(i < 20)
  {
    make_car(x, y, 46.0, 180.0);
    i++;
    x += 4.0;
  }
  #print "#---"
  i=0;
  x = 2072.0;
  y = 1262.0;
  while(i < 25)
  {
    make_car(x, y, 21.0, 90.0);
    i++;
    y -= 4.0;
  }
  #print "#---"
  x = -1210.5;
  y = -409.0;
  while(y < 234.0)
  {
    make_car(x, y, 42.0, 0.0);
    y += 17.0;
  }
}
