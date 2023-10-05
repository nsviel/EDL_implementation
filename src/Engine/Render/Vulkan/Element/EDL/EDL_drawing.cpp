#include "EDL_drawing.h"

#include "../../Drawing/VK_cmd.h"
#include "../../Pipeline/VK_pipeline.h"
#include "../../Command/VK_submit.h"
#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Command/VK_command.h"
#include "../../Presentation/VK_canvas.h"
#include "../../Binding/VK_descriptor.h"
#include "../../Binding/VK_uniform.h"

#include "../../../Render_node.h"
#include "../../../Shader/Shader.h"
#include "../../../Shader/Source/EDL/Shader_edl.h"


//Constructor / Destructor
EDL_drawing::EDL_drawing(VK_engine* vk_engine){
  //---------------------------

  Render_node* render_node = vk_engine->get_render_node();
  Shader* shaderManager = render_node->get_shaderManager();
  this->shader_edl = shaderManager->get_shader_edl();

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_cmd = vk_engine->get_vk_cmd();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = vk_engine->get_vk_submit();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_canvas = vk_engine->get_vk_canvas();

  //---------------------------
}
EDL_drawing::~EDL_drawing(){}

//Main function
void EDL_drawing::draw_edl(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  this->update_descriptor(renderpass);
  this->record_command(renderpass);
  this->submit_command(renderpass);

  //---------------------------
  vk_param->time.renderpass_edl.push_back(timer.stop_ms(t1));
}

//Subfunction
void EDL_drawing::update_descriptor(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_scene = vk_param->renderpass_scene.get_rendering_frame();
  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle_EDL");
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);

  //---------------------------
}
void EDL_drawing::record_command(Struct_renderpass* renderpass){
  Frame* frame = renderpass->get_rendering_frame();
  //---------------------------


  vk_command->start_render_pass(renderpass, frame, false);
  vk_cmd->cmd_viewport_canvas(renderpass);
  this->cmd_draw(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void EDL_drawing::submit_command(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();
  renderpass->semaphore_to_wait = frame_swap->semaphore_scene_ready;
  renderpass->semaphore_to_run = frame_swap->semaphore_edl_ready;
  renderpass->fence = VK_NULL_HANDLE;
  vk_submit->submit_graphics_command(renderpass);

  //---------------------------
}

//Command function
void EDL_drawing::cmd_draw(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle_EDL");
  Struct_edl* edl_param = shader_edl->get_edl_param();
  Struct_data* canvas = vk_canvas->get_data_canvas();

  vk_cmd->cmd_bind_pipeline(renderpass, "triangle_EDL");
  shader_edl->update_shader();
  vk_uniform->update_uniform_edl("Struct_edl", &pipeline->binding, *edl_param);
  vk_cmd->cmd_bind_descriptor(renderpass, "triangle_EDL", pipeline->binding.descriptor.set);
  vk_cmd->cmd_draw_data(renderpass, canvas);

  //---------------------------
}
