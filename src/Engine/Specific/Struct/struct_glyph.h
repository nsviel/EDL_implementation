#ifndef GLYPH_STRUCT_H
#define GLYPH_STRUCT_H

#include <Specific/Struct/struct_object.h>


struct Glyph : public Object
{
  //---------------------------

  Glyph();

  bool is_permanent;
  Object* linked_object;

  //---------------------------
};

#endif
