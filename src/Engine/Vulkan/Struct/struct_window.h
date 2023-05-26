#ifndef STRUCT_WINDOW_H
#define STRUCT_WINDOW_H

#include "../../../common.h"


struct Struct_window{
  std::string title = "Nephos";
  VkExtent2D extent;
  VkSurfaceKHR surface;
  glm::vec2 dim = glm::vec2(1024, 500);
  glm::vec2 dim_min = glm::vec2(500, 250);
};


#endif
