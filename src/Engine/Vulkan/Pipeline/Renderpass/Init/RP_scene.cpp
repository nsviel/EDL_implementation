#include "RP_scene.h"

#include "../VK_renderpass.h"
#include "../VK_subpass.h"

#include "../../Pipeline/VK_pipeline.h"

#include "../../../VK_engine.h"
#include "../../../VK_param.h"


//Constructor / Destructor
RP_scene::RP_scene(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
RP_scene::~RP_scene(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void RP_scene::init_renderpass_scene(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  renderpass->name = "scene";
  renderpass->frame_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

  this->create_subpass(renderpass);
  this->create_pipeline_point(renderpass);
  this->create_pipeline_line(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Subpass
void RP_scene::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  Struct_subpass* subpass = new Struct_subpass();
  subpass->color.binding = 0;
  subpass->color.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_SHADER;

  subpass->depth.binding = 1;
  subpass->depth.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH;
  renderpass->vec_subpass.push_back(subpass);

  //---------------------------
}

//Pipeline
void RP_scene::create_pipeline_point(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "point";
  pipeline->topology = "point";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_point_vs";
  pipeline->path_shader_fs = "Base/shader_point_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
void RP_scene::create_pipeline_line(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "line";
  pipeline->topology = "line";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_line_vs";
  pipeline->path_shader_fs = "Base/shader_line_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
