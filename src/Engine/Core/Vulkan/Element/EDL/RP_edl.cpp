#include "RP_edl.h"

#include "../../Renderpass/VK_renderpass.h"
#include "../../Renderpass/VK_subpass.h"
#include "../../Pipeline/VK_pipeline.h"
#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Camera/VK_viewport.h"


//Constructor / Destructor
RP_edl::RP_edl(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
RP_edl::~RP_edl(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void RP_edl::init_renderpass(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  //Renderpass
  renderpass->name = "edl";
  vk_subpass->create_subpass_shader(renderpass);
  this->create_pipeline_edl(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Pipeline
void RP_edl::create_pipeline_edl(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "triangle_EDL";
  pipeline->topology = "triangle";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "EDL/shader_edl_vs";
  pipeline->path_shader_fs = "EDL/shader_edl_fs";
  pipeline->info.vec_data_name.push_back("location");
  pipeline->info.vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_color", 0, 1, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("tex_depth", 0, 4, TYPE_SAMPLER, STAGE_FS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("Struct_edl", sizeof(Struct_edl), 5, TYPE_UNIFORM, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
