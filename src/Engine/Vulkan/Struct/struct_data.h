#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H

#include "struct_buffer.h"
#include "struct_uniform.h"
#include "../../../common.h"


struct Struct_data{ //Cloud cloud / part
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

  //---------------------------
};

#endif
