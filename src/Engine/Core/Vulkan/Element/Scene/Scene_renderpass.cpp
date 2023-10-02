#include "Scene_renderpass.h"

#include "../../Renderpass/VK_renderpass.h"
#include "../../Renderpass/VK_subpass.h"
#include "../../Pipeline/VK_pipeline.h"
#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Camera/VK_viewport.h"


//Constructor / Destructor
Scene_renderpass::Scene_renderpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
Scene_renderpass::~Scene_renderpass(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void Scene_renderpass::init_renderpass(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  renderpass->name = "scene";
  vk_subpass->create_subpass_shader(renderpass);
  this->create_pipeline_point(renderpass);
  this->create_pipeline_line(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Pipeline
void Scene_renderpass::create_pipeline_point(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "point";
  pipeline->topology = "point";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_point_vs";
  pipeline->path_shader_fs = "Base/shader_point_fs";
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("point_size", sizeof(int), 1, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
void Scene_renderpass::create_pipeline_line(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "line";
  pipeline->topology = "line";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_line_vs";
  pipeline->path_shader_fs = "Base/shader_line_fs";
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
