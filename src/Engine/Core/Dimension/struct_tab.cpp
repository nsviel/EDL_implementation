#include "struct_tab.h"


Tab::Tab(std::string name){
  //---------------------------

  this->name = name;
  this->pos = vec2(0);
  this->dim = vec2(100);
  this->dim_min = vec2(10);
  this->dim_max = vec2(1000);
  this->center = vec2(50);

  //---------------------------
}
