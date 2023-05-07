#include "struct_cam.h"


Cam::Cam(){
  //---------------------------

  this->reset();

  //---------------------------
}

void Cam::reset(){
  //---------------------------

  this->pos = glm::vec2(0.0f);
  this->dim = glm::vec2(0.0f);

  this->angle_azimuth = M_PI + M_PI/4;
  this->angle_elevation = -M_PI/6;
  this->fov = 65;
  this->speed_mouse = 0.0030000000260770321;
  this->speed_move = 3;
  this->zoom = 0;
  this->clip_far = 1000.0;
  this->clip_near = 0.001;

  this->cam_F = glm::vec3(0.0f);
  this->cam_R = glm::normalize(glm::vec3(cos(angle_azimuth - M_PI/2.0f), sin(angle_azimuth - M_PI/2.0f), 0));
  this->cam_U = glm::vec3(0.0f);
  this->cam_P = glm::vec3(5, 5, 5);
  this->cam_COM = glm::vec3(0.0f);

  this->projection = "perspective";
  this->view = "oblique";
  this->mode = "first_person";

  this->cam_move = false;
  this->cam_pose = false;
  this->cam_pose_mat = glm::mat4(1.0f);

  //---------------------------
}