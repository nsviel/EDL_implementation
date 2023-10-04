#ifndef OBJECT_AXIS_OBJECT_H
#define OBJECT_AXIS_OBJECT_H

#include "../Base/Glyph_source.h"


class Axis_object : public Glyph_source
{
public:
  //Constructor / Destructor
  Axis_object();
  ~Axis_object();

public:
  void create_axis_scene();
  void create_axis_circle(float circleRadius);
  Glyph* create_axis_subset(Object* object);
  void update_axis_subset(Object* object, Glyph* glyph);

  inline Glyph* get_axis_scene(){return axis_scene;}
  inline Glyph* get_axis_circle(){return axis_circle;}
  inline bool* get_axis_subset_visibility(){return &is_visible;}

private:
  Glyph* axis_scene;
  Glyph* axis_circle;

  bool is_visible;
};

#endif
