#include "Axis_object.h"


//Constructor / destructor
Axis_object::Axis_object(){
  //---------------------------

  this->name = "axis";
  this->is_visible = true;

  //---------------------------
  this->create_axis_scene();
}
Axis_object::~Axis_object(){
  //---------------------------

  delete axis_scene;

  //---------------------------
}

void Axis_object::create_axis_scene(){
  axis_scene = new Glyph();
  //---------------------------

  //Create glyph
  axis_scene->name = "axis";
  axis_scene->draw_line_width = 4;
  axis_scene->is_visible = true;
  axis_scene->draw_type_name = "line";
  axis_scene->is_permanent = true;

  //Parameters
  vector<vec3>& XYZ = axis_scene->xyz;
  vector<vec4>& RGB = axis_scene->rgb;

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
void Axis_object::create_axis_circle(float circleRadius){
  axis_circle = new Glyph();
  //---------------------------

  //Create glyph
  axis_circle->name = "axis_circle";
  axis_circle->draw_line_width = 1;
  axis_circle->is_visible = false;
  axis_circle->draw_type_name = "line";
  axis_circle->is_permanent = true;

  //Parameters
  int nb_segm = 100;
  vector<vec3>& XYZ = axis_circle->xyz;
  vector<vec4>& RGB = axis_circle->rgb;

  //Contruct glyph
  int cpt = 0;
  for(int i=0; i<nb_segm; i++){
    float theta_1 = 2.0f * 3.1415926f * float(i) / float(nb_segm);
    float theta_2 = 2.0f * 3.1415926f * float(i+1) / float(nb_segm);

    //Vertex 1
    float x = circleRadius * cosf(theta_1);
    float y = circleRadius * sinf(theta_1);
    XYZ.push_back(vec3(x, y, 0));
    RGB.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));

    //Vertex 2
    x = circleRadius * cosf(theta_2);
    y = circleRadius * sinf(theta_2);
    XYZ.push_back(vec3(x, y, 0));
    RGB.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));
  }

  //---------------------------
}
Glyph* Axis_object::create_axis_subset(Object* object){
  Glyph* axis_subset = new Glyph();
  //---------------------------

  //Create glyph
  axis_subset->name = "axis";
  axis_subset->draw_line_width = 3;
  axis_subset->is_visible = is_visible;
  axis_subset->draw_type_name = "line";

  //Axis_object colors
  vector<vec4>& RGB = axis_subset->rgb;
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.9f, 0.2f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.9f, 0.2f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));
  RGB.push_back(vec4(0.2f, 0.2f, 0.9f, 1.0f));

  //---------------------------
  return axis_subset;
}
void Axis_object::update_axis_subset(Object* object, Glyph* glyph){
  if(glyph == nullptr) return;
  vector<vec3>& XYZ = glyph->xyz;
  vec3 subset_root = object->root;
  //---------------------------

  glyph->is_visible = is_visible;
  XYZ.clear();

  //Axis_object rotation
  mat4 R = object->rotat;
  vec4 Rx = vec4(0.1,0,0,1) * R;
  vec4 Ry = vec4(0,0.1,0,1) * R;
  vec4 Rz = vec4(0,0,0.1,1) * R;

  //X Axis_object
  vec3 subsey_x = vec3(subset_root.x + Rx.x, subset_root.y + Rx.y, subset_root.z + Rx.z);
  XYZ.push_back(subset_root);
  XYZ.push_back(subsey_x);

  //Y Axis_object
  vec3 subsey_y = vec3(subset_root.x + Ry.x, subset_root.y + Ry.y, subset_root.z + Ry.z);
  XYZ.push_back(subset_root);
  XYZ.push_back(subsey_y);

  //Z Axis_object
  vec3 subsey_z = vec3(subset_root.x + Rz.x, subset_root.y + Rz.y, subset_root.z + Rz.z);
  XYZ.push_back(subset_root);
  XYZ.push_back(subsey_z);

  //---------------------------
}
