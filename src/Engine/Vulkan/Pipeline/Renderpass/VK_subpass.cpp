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
void VK_subpass::create_subpass_clear_info(Struct_renderpass* renderpass){
  Struct_subpass* subpass = new Struct_subpass();
  //---------------------------

  subpass->color.binding = 0;
  subpass->color.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_COLOR_ATTACHMENT;

  subpass->depth.binding = 1;
  subpass->depth.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH_ATTACHMENT;

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}
void VK_subpass::create_subpass_conserve_info(Struct_renderpass* renderpass){
  Struct_subpass* subpass = new Struct_subpass();
  //---------------------------

  subpass->color.binding = 0;
  subpass->color.load_operation = ATTACHMENT_LOADOP_LOAD;
  subpass->color.layout_initial = IMAGE_LAYOUT_COLOR_ATTACHMENT;
  subpass->color.layout_final = IMAGE_LAYOUT_PRESENT;

  subpass->depth.binding = 1;
  subpass->depth.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_DEPTH_ATTACHMENT;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH_ATTACHMENT;

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}
