#ifndef STRUCT_VIEWPORT_H
#define STRUCT_VIEWPORT_H

#include <string>
#include <vulkan/vulkan.h>


struct Struct_viewport{
  //---------------------------

  VkViewport viewport;
  VkRect2D scissor;

  //---------------------------
};


#endif
