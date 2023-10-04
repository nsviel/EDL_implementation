#ifndef GLYPH_STRUCT_H
#define GLYPH_STRUCT_H

#include <Common/struct_object.h>

#include "../../common.h"


struct Glyph : public Object
{
  //---------------------------

  Glyph();

  bool is_permanent;
  Object* linked_object;

  //---------------------------
};

#endif
