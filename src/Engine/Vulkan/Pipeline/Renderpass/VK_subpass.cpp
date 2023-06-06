#include "VK_subpass.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"


//Constructor / Destructor
VK_subpass::VK_subpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();

  //---------------------------
}
VK_subpass::~VK_subpass(){}

//Main function
void VK_subpass::create_subpass_info(Struct_renderpass* renderpass){
  Struct_subpass* subpass = new Struct_subpass();
  //---------------------------

  subpass->color.binding = 0;
  subpass->color.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_PRESENT;

  subpass->depth.binding = 1;
  subpass->depth.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH;

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}
