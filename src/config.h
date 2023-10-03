#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct configuration{
  //---------------------------

  //Window
  string window_title = "Nephos";
  glm::vec2 window_dimension = glm::vec2(1024, 500);
  glm::vec2 window_dimension_min = glm::vec2(500, 250);

  //---------------------------
};

#endif
