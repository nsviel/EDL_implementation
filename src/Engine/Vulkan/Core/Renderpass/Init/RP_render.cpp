#include "RP_render.h"

#include "../VK_renderpass.h"
#include "../VK_subpass.h"

#include "../../Pipeline/VK_pipeline.h"

#include "../../../VK_engine.h"
#include "../../../VK_param.h"


//Constructor / Destructor
RP_render::RP_render(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
RP_render::~RP_render(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void RP_render::init_renderpass_render(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  renderpass->name = "render";
  renderpass->color_image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  renderpass->color_sampler_layout = IMAGE_LAYOUT_SHADER_READONLY;
  renderpass->depth_image_usage = IMAGE_USAGE_DEPTH;
  renderpass->depth_sampler_layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

  this->create_subpass(renderpass);
  this->create_pipeline_triangle(renderpass);
  this->create_pipeline_edl(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Subpass
void RP_render::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  Struct_subpass* subpass = new Struct_subpass();
  subpass->color.binding = 0;
  subpass->color.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->color.store_operation = ATTACHMENT_STOREOP_NOTHING;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_SHADER_READONLY;

  subpass->depth.binding = 1;
  subpass->depth.load_operation = ATTACHMENT_LOADOP_CLEAR;
  subpass->color.store_operation = ATTACHMENT_STOREOP_STORE;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  renderpass->vec_subpass.push_back(subpass);

  //---------------------------
}

//Pipeline
void RP_render::create_pipeline_triangle(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "triangle";
  pipeline->topology = "triangle";
  pipeline->compile_shader = false;
  pipeline->path_shader_vs = "Misc/shader_quad_test_vs";
  pipeline->path_shader_fs = "Misc/shader_quad_test_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color_scene", 0, 0, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth_scene", 0, 1, TYPE_SAMPLER, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
void RP_render::create_pipeline_edl(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "triangle_EDL";
  pipeline->topology = "triangle";
  pipeline->compile_shader = false;
  pipeline->path_shader_vs = "EDL/shader_edl_vs";
  pipeline->path_shader_fs = "EDL/shader_edl_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color_scene", 0, 0, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth_scene", 0, 1, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("Struct_edl", sizeof(Struct_edl), 2, TYPE_UNIFORM, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
