#include "VK_viewport.h"

#include "../VK_engine.h"
#include "../VK_param.h"

#include "../../Dimension/Dimension.h"
#include "../../Node_engine.h"


//Constructor / Destructor
VK_viewport::VK_viewport(VK_engine* vk_engine){
  //---------------------------

  Node_engine* node_engine = vk_engine->get_node_engine();
  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->dimManager = node_engine->get_dimManager();

  //---------------------------
}
VK_viewport::~VK_viewport(){}

void VK_viewport::init_viewport(){
  Tab* tab = dimManager->get_tab("rendering");
  //---------------------------

  //Viewport
  viewport_scene = {};
  viewport_scene.x = tab->pos.x;
  viewport_scene.y = tab->pos.y;
  viewport_scene.width  = tab->dim.x;
  viewport_scene.height = tab->dim.y;
  viewport_scene.minDepth = 0.0f;
  viewport_scene.maxDepth = 1.0f;

  //Full viewport scissor
  scissor = {};
  scissor.offset = {0, 0};
  scissor.extent = vk_param->window.extent;

  //Viewport
  vec2 win_dim = dimManager->get_win_dim();
  viewport_canvas = {};
  viewport_canvas.x = 0;
  viewport_canvas.y = 0;
  viewport_canvas.width  = win_dim.x;
  viewport_canvas.height = win_dim.y;
  viewport_canvas.minDepth = 0.0f;
  viewport_canvas.maxDepth = 1.0f;

  //---------------------------
}
void VK_viewport::update_viewport(){
  Tab* tab = dimManager->get_tab("rendering");
  //---------------------------

  //Viewport scene
  viewport_scene.x = tab->pos.x;
  viewport_scene.y = tab->pos.y;
  viewport_scene.width  = tab->dim.x;
  viewport_scene.height = tab->dim.y;

  //Scissor
  scissor.extent = vk_param->window.extent;

  //Viewport canvas
  vec2 win_dim = dimManager->get_win_dim();
  viewport_canvas.width  = win_dim.x;
  viewport_canvas.height = win_dim.y;

  //---------------------------
}

Struct_viewport* VK_viewport::create_viewport_scene(){
  Tab* tab = dimManager->get_tab("rendering");
  Struct_viewport* viewport = new Struct_viewport();
  //---------------------------

  //Viewport
  viewport->viewport = {};
  viewport->viewport.x = tab->pos.x;
  viewport->viewport.y = tab->pos.y;
  viewport->viewport.width  = tab->dim.x;
  viewport->viewport.height = tab->dim.y;
  viewport->viewport.minDepth = 0.0f;
  viewport->viewport.maxDepth = 1.0f;

  //Full viewport scissor
  viewport->scissor = {};
  viewport->scissor.offset = {0, 0};
  viewport->scissor.extent = vk_param->window.extent;

  //---------------------------
  return viewport;
}
Struct_viewport* VK_viewport::create_viewport_canvas(){
  Tab* tab = dimManager->get_tab("rendering");
  Struct_viewport* viewport = new Struct_viewport();
  //---------------------------

  //Viewport
  vec2 win_dim = dimManager->get_win_dim();
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
