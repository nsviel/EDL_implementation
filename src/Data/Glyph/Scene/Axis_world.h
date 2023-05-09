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
  void create_axis_scene();
  Glyph* create_axis_subset(Cloud* cloud);
  void update_axis_subset(Cloud* cloud, Glyph* glyph);

  inline Glyph* get_axis_scene(){return glyph;}
  inline bool* get_axis_subset_visibility(){return &is_visible;}

private:
  Glyph* glyph;
  bool is_visible;
};

#endif
