#ifndef STRUCT_WINDOW_H
#define STRUCT_WINDOW_H

#include "../../Render_common.h"


struct Struct_window{
  //---------------------------

  std::string title = "Nephos";
  glm::vec2 dim = glm::vec2(1024, 500);
  glm::vec2 dim_min = glm::vec2(500, 250);

  bool is_resized = false;
  VkExtent2D extent;
  VkSurfaceKHR surface;

  //---------------------------
};


#endif
