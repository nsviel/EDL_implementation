#ifndef STRUCT_WINDOW_H
#define STRUCT_WINDOW_H

#include <Specific/common.h>


struct Struct_window{
  //---------------------------

  bool is_resized = false;
  VkExtent2D extent;
  VkSurfaceKHR surface;

  //---------------------------
};


#endif
