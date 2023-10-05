#include "VK_viewport.h"

#include "../VK_engine.h"
#include "../VK_param.h"

#include "../../../../Element/Window/Dimension.h"
#include "../../Render_node.h"


//Constructor / Destructor
VK_viewport::VK_viewport(VK_engine* vk_engine){
  //---------------------------

  Render_node* core_node = vk_engine->get_core_node();
  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->dimManager = core_node->get_dimManager();

  //---------------------------
}
VK_viewport::~VK_viewport(){}

void VK_viewport::init_viewport(){
  vec2 win_dim = dimManager->get_win_dim();
  //---------------------------

  //Viewport
  viewport = {};
  viewport.x = 0;
  viewport.y = 0;
  viewport.width  = win_dim.x;
  viewport.height = win_dim.y;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  //Full viewport scissor
  scissor = {};
  scissor.offset = {0, 0};
  scissor.extent = vk_param->window.extent;

  //---------------------------
}
void VK_viewport::update_viewport(){
  vec2 win_dim = dimManager->get_win_dim();
  //---------------------------

  //Viewport scene
  viewport.x = 0;
  viewport.y = 0;
  viewport.width  = win_dim.x;
  viewport.height = win_dim.y;

  //Scissor
  scissor.extent = vk_param->window.extent;

  //---------------------------
}

Struct_viewport* VK_viewport::create_viewport(){
  vec2 win_dim = dimManager->get_win_dim();
  //---------------------------

  //Viewport
  Struct_viewport* viewport = new Struct_viewport();
  viewport->viewport = {};
  viewport->viewport.x = 0;
  viewport->viewport.y = 0;
  viewport->viewport.width  = win_dim.x;
  viewport->viewport.height = win_dim.y;
  viewport->viewport.minDepth = 0.0f;
  viewport->viewport.maxDepth = 1.0f;

  //Full viewport scissor
  viewport->scissor = {};
  viewport->scissor.offset = {0, 0};
  viewport->scissor.extent = vk_param->window.extent;

  //---------------------------
  return viewport;
}
