#include "VK_viewport.h"

#include "../../VK_engine.h"

#include "../../../Dimension/Dimension.h"
#include "../../../Node_engine.h"


//Constructor / Destructor
VK_viewport::VK_viewport(VK_engine* vk_engine){
  //---------------------------

  Node_engine* node_engine = vk_engine->get_node_engine();

  this->dimManager = node_engine->get_dimManager();

  //---------------------------
}
VK_viewport::~VK_viewport(){}

void VK_viewport::update_viewport(VkExtent2D swapchain_extent){
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
  scissor.extent = swapchain_extent;

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
