#include "VK_viewport.h"

#include "../Engine_vulkan.h"

#include "../../Dimension/Dimension.h"
#include "../../Node_engine.h"


//Constructor / Destructor
VK_viewport::VK_viewport(Engine_vulkan* engine_vulkan){
  //---------------------------

  Node_engine* node_engine = engine_vulkan->get_node_engine();

  this->dimManager = node_engine->get_dimManager();

  //---------------------------
}
VK_viewport::~VK_viewport(){}

void VK_viewport::init_viewport(VkExtent2D swapchain_extent){
  //---------------------------

  //Viewport
  viewport = {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width  = (float) swapchain_extent.width;
  viewport.height = (float) swapchain_extent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  //Full viewport scissor
  scissor = {};
  scissor.offset = {0, 0};
  scissor.extent = swapchain_extent;

  //---------------------------
}
