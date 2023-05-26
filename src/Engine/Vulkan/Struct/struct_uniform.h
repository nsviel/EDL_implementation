#ifndef STRUCT_UNIFORM_H
#define STRUCT_UNIFORM_H

#include "../../../common.h"


struct Struct_uniform{
  VkBuffer buffer;
  VkDeviceMemory mem;
  void* mapped;
};

struct MVP{
  glm::mat4 mvp;
};


#endif
