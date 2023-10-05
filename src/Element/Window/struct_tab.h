#ifndef TAB_STRUCT_H
#define TAB_STRUCT_H

#include <glm/glm.hpp>
#include <string>


//Collection are cloud containers
struct Tab{
  //---------------------------

  Tab(std::string name);

  std::string name;
  glm::vec2 pos;
  glm::vec2 dim;
  glm::vec2 dim_min;
  glm::vec2 dim_max;
  glm::vec2 center;

  //---------------------------
};

#endif
