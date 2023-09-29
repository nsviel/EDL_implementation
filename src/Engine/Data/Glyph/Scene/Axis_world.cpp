#include "Axis_world.h"


//Constructor / destructor
Axis_world::Axis_world(){
  //---------------------------

  this->name = "axis_world";
  this->is_visible = true;

  //---------------------------
}
Axis_world::~Axis_world(){
  //---------------------------

  delete glyph;

  //---------------------------
}

void Axis_world::create_glyph(){
  glyph = new Glyph();
  //---------------------------

  //Create glyph
  glyph->name = "axis_world";
  glyph->draw_line_width = 4;
  glyph->is_visible = true;
  glyph->draw_type_name = "line";
  glyph->is_permanent = true;

  //Parameters
  vector<vec3>& XYZ = glyph->xyz;
  vector<vec4>& RGB = glyph->rgb;

  //Construct glyph
  //X axis
  XYZ.push_back(vec3(0, 0, 0.005));
  XYZ.push_back(vec3(1, 0, 0.005));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //Y axis
  XYZ.push_back(vec3(0, 0, 0.005));
  XYZ.push_back(vec3(0, 1, 0.005));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));

  //Z axis
  XYZ.push_back(vec3(0, 0, 0.005));
  XYZ.push_back(vec3(0, 0, 1));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));

  //---------------------------
}
