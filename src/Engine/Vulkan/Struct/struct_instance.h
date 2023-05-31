#ifndef STRUCT_INSTANCE_H
#define STRUCT_INSTANCE_H

#include "../../../common.h"


struct Struct_instance{
  //---------------------------

  int max_frame = 2;
  std::string path_shader = "../src/Engine/Shader/spir/";
  VkInstance instance;
  vector<const char*> extension;

  //---------------------------
};


#endif
