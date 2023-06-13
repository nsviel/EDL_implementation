#include "Shader_edl.h"

#include "../../../Node_engine.h"
#include "../../../Param_engine.h"
#include "../../../Dimension/Dimension.h"


Shader_edl::Shader_edl(Node_engine* node_engine){
  //---------------------------

  this->param_engine = node_engine->get_param_engine();
  this->dimManager = node_engine->get_dimManager();

  this->struct_edl = new Struct_edl();
  struct_edl->activated = true;
  struct_edl->strength = 300.0;
  struct_edl->radius = 1.5;

  //---------------------------
  this->update_shader();
}
Shader_edl::~Shader_edl(){}

void Shader_edl::update_shader(){
  Struct_camera* camera = &param_engine->camera;
  //---------------------------

  // Depth setup
  float clip_near = camera->clip_near;
  float clip_far = camera->clip_far;
  struct_edl->A = -(clip_far + clip_near) / (clip_far - clip_near);
  struct_edl->B = (-2 * clip_far * clip_near) / (clip_far - clip_near);

  //Dimension
  Tab* tab_rendering = dimManager->get_tab("rendering");
  struct_edl->width = tab_rendering->dim.x;
  struct_edl->height = tab_rendering->dim.y;

  //---------------------------
}
