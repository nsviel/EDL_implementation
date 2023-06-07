#ifndef MESH_STRUCT_H
#define MESH_STRUCT_H

#include "struct_object.h"
#include "../../Engine/Vulkan/Struct/struct_image.h"
#include "../../common.h"


struct Mesh : public Object{
  //---------------------------

  list<Struct_image*> list_texture;

  //---------------------------
};

#endif
