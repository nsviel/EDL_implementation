#ifndef STRUCT_UNIFORM_H
#define STRUCT_UNIFORM_H

#include <string>
#include <vulkan/vulkan.h>


struct Struct_uniform{
  VkBuffer buffer;
  VkDeviceMemory mem;
  void* mapped;
};


#endif
