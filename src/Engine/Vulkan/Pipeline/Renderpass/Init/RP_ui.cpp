#include "RP_ui.h"

#include "../VK_renderpass.h"
#include "../VK_subpass.h"

#include "../../Pipeline/VK_pipeline.h"

#include "../../../VK_engine.h"
#include "../../../VK_param.h"


//Constructor / Destructor
RP_ui::RP_ui(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
RP_ui::~RP_ui(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void RP_ui::init_renderpass_ui(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  renderpass->name = "ui";
  renderpass->color_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  renderpass->depth_usage = IMAGE_USAGE_DEPTH;

  this->create_subpass(renderpass);
  this->create_pipeline_triangle(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Subpass
void RP_ui::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  Struct_subpass* subpass = new Struct_subpass();
  subpass->color.binding = 0;
  subpass->color.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_PRESENT;

  subpass->depth.binding = 1;
  subpass->depth.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH;
  renderpass->vec_subpass.push_back(subpass);

  //---------------------------
}

//Pipeline
void RP_ui::create_pipeline_triangle(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "triangle";
  pipeline->topology = "triangle";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_quad_vs";
  pipeline->path_shader_fs = "Base/shader_quad_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color_final", 0, 1, TYPE_SAMPLER, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
