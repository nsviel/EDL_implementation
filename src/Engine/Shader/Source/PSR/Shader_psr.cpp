#include "Shader_psr.h"

#include "../../../Node_engine.h"
#include "../../../Param_engine.h"
#include "../../../Dimension/Dimension.h"


Shader_psr::Shader_psr(Node_engine* node_engine){
  //---------------------------

  this->param_engine = node_engine->get_param_engine();
  this->dimManager = node_engine->get_dimManager();

  this->struct_psr = new Struct_psr();
  struct_psr->activated = true;
  struct_psr->strength = 15.0;
  struct_psr->radius = 1.0;

  //---------------------------
  this->update_shader();
}
Shader_psr::~Shader_psr(){}

void Shader_psr::update_shader(){
  Struct_camera* camera = &param_engine->camera;
  //---------------------------

  // Depth setup
  struct_psr->z_near = camera->clip_near;
  struct_psr->z_far = camera->clip_far;

  //Dimension
  Tab* tab_rendering = dimManager->get_tab("rendering");
  struct_psr->tex_width = tab_rendering->dim.x;
  struct_psr->tex_height = tab_rendering->dim.y;

  //---------------------------
}
