#include "VK_scene.h"
#include "VK_renderpass.h"
#include "VK_subpass.h"

#include "../Pipeline/VK_pipeline.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"


//Constructor / Destructor
VK_scene::VK_scene(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
VK_scene::~VK_scene(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void VK_scene::init_renderpass_scene(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  //Render pass
  renderpass->name = "scene";
  renderpass->frame_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

  this->create_subpass(renderpass);

  this->create_pipeline_point(renderpass);
  this->create_pipeline_line(renderpass);
  this->create_pipeline_edl(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
  vk_renderpass->create_renderpass_frame(renderpass, "rp");
}

//Subpass
void VK_scene::create_subpass(Struct_renderpass* renderpass){
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
void VK_scene::create_pipeline_point(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline_point = new Struct_pipeline();
  pipeline_point->name = "point";
  pipeline_point->topology = "point";
  pipeline_point->compile_shader = true;
  pipeline_point->path_shader_vs = "Base/shader_scene_vs";
  pipeline_point->path_shader_fs = "Base/shader_scene_fs";
  pipeline_point->vec_data_name.push_back("location");
  pipeline_point->vec_data_name.push_back("color");
  pipeline_point->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline_point);

  //---------------------------
}
void VK_scene::create_pipeline_line(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline_line = new Struct_pipeline();
  pipeline_line->name = "line";
  pipeline_line->topology = "line";
  pipeline_line->compile_shader = true;
  pipeline_line->path_shader_vs = "Base/shader_scene_vs";
  pipeline_line->path_shader_fs = "Base/shader_scene_fs";
  pipeline_line->vec_data_name.push_back("location");
  pipeline_line->vec_data_name.push_back("color");
  pipeline_line->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline_line);

  //---------------------------
}
void VK_scene::create_pipeline_edl(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline_point_edl = new Struct_pipeline();
  pipeline_point_edl->name = "triangle_EDL";
  pipeline_point_edl->topology = "triangle";
  pipeline_point_edl->compile_shader = true;
  pipeline_point_edl->path_shader_vs = "EDL/shader_edl_vs";
  pipeline_point_edl->path_shader_fs = "EDL/shader_edl_fs";
  pipeline_point_edl->vec_data_name.push_back("location");
  pipeline_point_edl->vec_data_name.push_back("color");
  pipeline_point_edl->binding.vec_required_binding.push_back(std::make_tuple("tex_depth", 0, 0, TYPE_SAMPLER, STAGE_FS));
  pipeline_point_edl->binding.vec_required_binding.push_back(std::make_tuple("tex_color", 0, 1, TYPE_SAMPLER, STAGE_FS));
  pipeline_point_edl->binding.vec_required_binding.push_back(std::make_tuple("EDL_param", sizeof(EDL_param), 2, TYPE_UNIFORM, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline_point_edl);

  //---------------------------
}
