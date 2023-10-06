#include "struct_camera.h"


Struct_camera::Struct_camera(){
  //---------------------------

  this->reset();

  //---------------------------
}

void Struct_camera::reset(){
  //---------------------------

  this->angle_azimuth = M_PI + M_PI/4;
  this->angle_elevation = -M_PI/6;
  this->fov = 65;
  this->speed_mouse = 0.0030000000260770321;
  this->speed_move = 3;
  this->clip_far = 100.0;
  this->clip_near = 0.01;

  this->cam_R = glm::normalize(glm::vec3(cos(angle_azimuth - M_PI/2.0f), sin(angle_azimuth - M_PI/2.0f), 0));
  this->cam_P = glm::vec3(5, 5, 5);

  this->projection = "perspective";
  this->view = "oblique";
  this->mode = "first_person";

  //---------------------------
}
