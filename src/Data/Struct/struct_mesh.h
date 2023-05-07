#ifndef MESH_STRUCT_H
#define MESH_STRUCT_H

#include "struct_object.h"
#include "../../Engine/Vulkan/Struct/struct_texture.h"
#include "../../common.h"


struct Mesh : public Object{
  //---------------------------

  list<Struct_texture*> list_texture;

  //---------------------------
};

#endif
