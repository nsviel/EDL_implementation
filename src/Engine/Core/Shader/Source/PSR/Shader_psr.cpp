#include "Shader_psr.h"

#include "../../../Core_node.h"
#include "../../../Core_param.h"
#include "../../../Dimension/Dimension.h"


Shader_psr::Shader_psr(Core_node* core_node){
  //---------------------------

  this->core_param = core_node->get_core_param();
  this->dimManager = core_node->get_dimManager();

  this->struct_pyramid = new Struct_pyramid();

  //---------------------------
  this->update_shader();
}
Shader_psr::~Shader_psr(){}

void Shader_psr::update_shader(){
  Struct_camera* camera = &core_param->camera;
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
