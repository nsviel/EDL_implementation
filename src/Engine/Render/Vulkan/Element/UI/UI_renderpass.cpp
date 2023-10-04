#include "UI_renderpass.h"

#include "../../Renderpass/VK_renderpass.h"
#include "../../Renderpass/VK_subpass.h"
#include "../../Pipeline/VK_pipeline.h"
#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Camera/VK_viewport.h"


//Constructor / Destructor
UI_renderpass::UI_renderpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
UI_renderpass::~UI_renderpass(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void UI_renderpass::init_renderpass(Struct_renderpass* renderpass){
  VK_renderpass* vk_renderpass = vk_engine->get_vk_renderpass();
  //---------------------------

  renderpass->name = "ui";
  vk_subpass->create_subpass_presentation(renderpass);
  this->create_pipeline_canvas(renderpass);

  //---------------------------
  vk_renderpass->create_renderpass(renderpass);
}

//Pipeline
void UI_renderpass::create_pipeline_canvas(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "triangle";
  pipeline->purpose = "ui";
  pipeline->topology = "triangle";
  pipeline->compile_shader = true;
  pipeline->with_depth_test = false;
  pipeline->path_shader_vs = "Canvas/shader_canvas_empty_vs";
  pipeline->path_shader_fs = "Canvas/shader_canvas_empty_fs";
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
}
