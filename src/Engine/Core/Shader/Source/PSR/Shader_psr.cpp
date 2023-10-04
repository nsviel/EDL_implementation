#include "Shader_psr.h"

#include "../../../Node_core.h"
#include "../../../Param_core.h"
#include "../../../Dimension/Dimension.h"


Shader_psr::Shader_psr(Node_core* node_core){
  //---------------------------

  this->param_engine = node_core->get_param_engine();
  this->dimManager = node_core->get_dimManager();

  this->struct_pyramid = new Struct_pyramid();

  //---------------------------
  this->update_shader();
}
Shader_psr::~Shader_psr(){}

void Shader_psr::update_shader(){
  Struct_camera* camera = &param_engine->camera;
  //---------------------------

  // Depth setup
  struct_pyramid->z_near = camera->clip_near;
  struct_pyramid->z_far = camera->clip_far;

  //Dimension
  Tab* tab_rendering = dimManager->get_tab("rendering");
  struct_pyramid->tex_width = tab_rendering->dim.x;
  struct_pyramid->tex_height = tab_rendering->dim.y;

  //---------------------------
}
