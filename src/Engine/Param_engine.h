#ifndef PARAM_ENGINE_H
#define PARAM_ENGINE_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Param_engine{
  //---------------------------

  std::string title = "Nephos";
  glm::vec4 background_color = glm::vec4(0.01, 0.01, 0.01, 0.01);
  glm::vec2 window_dim = glm::vec2(1024, 500);

  //---------------------------
};

#endif
