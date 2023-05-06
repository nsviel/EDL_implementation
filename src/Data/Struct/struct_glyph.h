#ifndef GLYPH_STRUCT_H
#define GLYPH_STRUCT_H

#include "struct_object.h"

#include "../../common.h"


struct Glyph : public Object
{
  //---------------------------

  Glyph();

  bool is_permanent;
  std::vector<glm::vec3> xyz_init;
  Object* linked_object;

  //---------------------------
};

#endif
