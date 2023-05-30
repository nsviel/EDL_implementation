#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H

#include "struct_buffer.h"
#include "../../../common.h"


struct Struct_data{ //Cloud cloud / part
  //---------------------------

  Object* object;

  VkDescriptorSet descriptor_set;
  Struct_buffer* xyz;
  Struct_buffer* rgb;
  Struct_buffer* uv;

  //---------------------------
};

#endif
