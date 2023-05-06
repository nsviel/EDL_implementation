#include "VK_viewport.h"

#include "../Engine.h"

#include "../../Dimension/Dimension.h"
#include "../../Node_engine.h"


//Constructor / Destructor
VK_viewport::VK_viewport(Engine* engineManager){
  //---------------------------

  Node_engine* node_engine = engineManager->get_node_engine();

  this->dimManager = node_engine->get_dimManager();

  //---------------------------
}
VK_viewport::~VK_viewport(){}

void VK_viewport::update_viewport(VkExtent2D swapchain_extent){
  Tab* tab = dimManager->get_tab("rendering");
  //---------------------------

  //Viewport
  viewport = {};
  viewport.x = tab->pos.x;
  viewport.y = tab->pos.y;
  viewport.width  = tab->dim.x;
  viewport.height = tab->dim.y;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  //Full viewport scissor
  scissor = {};
  scissor.offset = {0, 0};
  scissor.extent = swapchain_extent;

  //---------------------------
}
