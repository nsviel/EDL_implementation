#include "Axis_world.h"


//Constructor / destructor
Axis_world::Axis_world(){
  //---------------------------

  this->name = "axis_world";
  this->is_visible = true;

  //---------------------------
  this->create_axis_scene();
}
Axis_world::~Axis_world(){
  //---------------------------

  delete glyph;

  //---------------------------
}

void Axis_world::create_axis_scene(){
  glyph = new Glyph();
  //---------------------------

  //Create glyph
  glyph->name = "axis";
  glyph->draw_line_width = 4;
  glyph->is_visible = true;
  glyph->draw_type_name = "line";
  glyph->is_permanent = true;

  //Parameters
  vector<vec3>& XYZ = glyph->xyz;
  vector<vec4>& RGB = glyph->rgb;

  //Construct glyph
  //X axis
  XYZ.push_back(vec3(0, 0, 0));
  XYZ.push_back(vec3(1, 0, 0));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));

  //Y axis
  XYZ.push_back(vec3(0, 0, 0));
  XYZ.push_back(vec3(0, 1, 0));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 1.0f, 0.0f, 1.0f));

  //Z axis
  XYZ.push_back(vec3(0, 0, 0));
  XYZ.push_back(vec3(0, 0, 1));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));
  RGB.push_back(vec4(0.0f, 0.0f, 1.0f, 1.0f));

  //---------------------------
}
void Axis_world::update_axis_subset(Cloud* cloud, Glyph* glyph){
  if(glyph == nullptr) return;
  vector<vec3>& XYZ = glyph->xyz;
  vec3 subset_root = cloud->root;
  //---------------------------

  glyph->is_visible = is_visible;
  XYZ.clear();

  //Axis_world rotation
  mat4 R = cloud->rotat;
  vec4 Rx = vec4(0.1,0,0,1) * R;
  vec4 Ry = vec4(0,0.1,0,1) * R;
  vec4 Rz = vec4(0,0,0.1,1) * R;

  //X Axis_world
  vec3 subsey_x = vec3(subset_root.x + Rx.x, subset_root.y + Rx.y, subset_root.z + Rx.z);
  XYZ.push_back(subset_root);
  XYZ.push_back(subsey_x);

  //Y Axis_world
  vec3 subsey_y = vec3(subset_root.x + Ry.x, subset_root.y + Ry.y, subset_root.z + Ry.z);
  XYZ.push_back(subset_root);
  XYZ.push_back(subsey_y);

  //Z Axis_world
  vec3 subsey_z = vec3(subset_root.x + Rz.x, subset_root.y + Rz.y, subset_root.z + Rz.z);
  XYZ.push_back(subset_root);
  XYZ.push_back(subsey_z);

  //---------------------------
}
