#ifndef STRUCT_UNIFORM_H
#define STRUCT_UNIFORM_H

#include "../../../common.h"


struct Struct_uniform{
  std::string name;
  VkBuffer buffer;
  VkDeviceMemory mem;
  void* mapped;
};


#endif
