#include "Shader_edl.h"

#include "../../../Core_node.h"
#include "../../../Core_param.h"
#include "../../../Dimension/Dimension.h"


Shader_edl::Shader_edl(Core_node* core_node){
  //---------------------------

  this->core_param = core_node->get_core_param();
  this->dimManager = core_node->get_dimManager();

  this->struct_edl = new Struct_edl();
  struct_edl->activated = true;
  struct_edl->strength = 15.0;
  struct_edl->radius = 1.0;

  //---------------------------
  this->update_shader();
}
Shader_edl::~Shader_edl(){}

void Shader_edl::update_shader(){
  Struct_camera* camera = &core_param->camera;
  //---------------------------

  // Depth setup
  struct_edl->z_near = camera->clip_near;
  struct_edl->z_far = camera->clip_far;

  //Dimension
  Tab* tab_rendering = dimManager->get_tab("rendering");
  struct_edl->tex_width = tab_rendering->dim.x;
  struct_edl->tex_height = tab_rendering->dim.y;

  //---------------------------
}
