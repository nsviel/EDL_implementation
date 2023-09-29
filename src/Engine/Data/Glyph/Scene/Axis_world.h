#ifndef OBJECT_AXIS_WORLD_H
#define OBJECT_AXIS_WORLD_H

#include "../Base/Glyph_source.h"


class Axis_world : public Glyph_source
{
public:
  //Constructor / Destructor
  Axis_world();
  ~Axis_world();

public:
  void create_glyph();

  inline bool* get_axis_subset_visibility(){return &is_visible;}

private:
  bool is_visible;
};

#endif
