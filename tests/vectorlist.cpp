#include "util/arraylist.hpp"
#include <iostream>
#include "signals.hpp"
#include <cassert>

#define PRINT(list) for(auto it : list) {std::cout << it << ' ';assert(list[it]);} std::cout << '\n'
/*
INIT
{
	util::arraylist<400> vl;
	PRINT(vl);
	vl.set(1);
	PRINT(vl);
	vl.set(0);
	PRINT(vl);
	vl.unset(1);
	PRINT(vl);
	vl.set(2);
	PRINT(vl);
	vl.set(66);
	PRINT(vl);
	vl.set(65);
	PRINT(vl);
	vl.unset(65);
	PRINT(vl);
	vl.unset(0);
	PRINT(vl);
	vl.set(1);
	PRINT(vl);
	vl.set(0);
	PRINT(vl);
	vl.unset(0);
	vl.unset(1);
	vl.unset(2);
	PRINT(vl);
	vl.unset(66);
	PRINT(vl);
	vl.set(300);
	PRINT(vl);
	vl.set(20);
	PRINT(vl);
}




*/
