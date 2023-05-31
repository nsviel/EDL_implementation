#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H

#include "typedef.h"
#include "struct_data.h"
#include "struct_binding.h"
#include "../../../common.h"


struct Struct_buffer{
  //---------------------------

  VkBuffer vbo;
  VkDeviceMemory mem;

  //---------------------------
};

struct Struct_data{ 
  //---------------------------

  Object* object;

  //Data
  bool has_xyz = false;
  bool has_rgb = false;
  bool has_uv = false;

  //Buffer
  Struct_buffer xyz;
  Struct_buffer rgb;
  Struct_buffer uv;

  //Binding
  Struct_binding binding;

  //---------------------------
};

#endif
