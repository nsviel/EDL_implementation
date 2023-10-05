#include "Shader_psr.h"
#include "../../../Render_node.h"
#include "../../../Render_param.h"

#include <Window/Window.h>


Shader_psr::Shader_psr(Render_node* render_node){
  //---------------------------

  this->core_param = render_node->get_core_param();
  this->window = render_node->get_window();

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
  vec2 window_dim = window->get_window_dim();
  struct_pyramid->tex_width = window_dim.x;
  struct_pyramid->tex_height = window_dim.y;

  //---------------------------
}
