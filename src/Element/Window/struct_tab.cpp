#include "struct_tab.h"


Tab::Tab(std::string name){
  //---------------------------

  this->name = name;
  this->pos = glm::vec2(0);
  this->dim = glm::vec2(100);
  this->dim_min = glm::vec2(10);
  this->dim_max = glm::vec2(1000);
  this->center = glm::vec2(50);

  //---------------------------
}
