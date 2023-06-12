#include "Shader_edl.h"

#include "../../../Camera/Camera.h"
#include "../../../Node_engine.h"
#include "../../../Dimension/Dimension.h"


Shader_edl::Shader_edl(Node_engine* node_engine){
  //---------------------------

  this->cameraManager = node_engine->get_cameraManager();
  this->dimManager = node_engine->get_dimManager();

  this->struct_edl = new Struct_edl();
  struct_edl->activated = true;
  struct_edl->strength = 100.0;
  struct_edl->distance = 1.0;
  struct_edl->radius = 1.0;

  //---------------------------
  this->update_shader();
}
Shader_edl::~Shader_edl(){}

void Shader_edl::update_shader(){
  Cam* camera = cameraManager->get_camera();
  //---------------------------

  // Depth setup
  float clip_near = camera->clip_near;
  float clip_far = camera->clip_far;
  struct_edl->A = (clip_far + clip_near) / (clip_far - clip_near);
  struct_edl->B = (-2 * clip_far * clip_near) / (clip_far - clip_near);

  //Dimension
  struct_edl->width = camera->dim.x;
  struct_edl->height = camera->dim.y;
say(camera->dim);
  //---------------------------
}
