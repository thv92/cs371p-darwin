
#include "Darwin.h"
#include <iostream>




Species::~Species(){
  std::cout <<"I am being deleted species" << std::endl;

}


Creature::Creature(Species s, String dir): _s(s), _dir(dir){}






