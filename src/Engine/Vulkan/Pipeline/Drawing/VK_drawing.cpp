#include "VK_drawing.h"
#include "VK_cmd.h"

#include "../Pipeline/VK_pipeline.h"
#include "../Command/VK_submit.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Pipeline/Command/VK_command.h"
#include "../../Rendering/Render/VK_canvas.h"
#include "../../Rendering/Binding/VK_descriptor.h"


//Constructor / Destructor
VK_drawing::VK_drawing(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_cmd = vk_engine->get_vk_cmd();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = vk_engine->get_vk_submit();

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  //---------------------------

  vk_submit->acquire_next_image(&vk_param->swapchain);
  this->draw_scene(&vk_param->renderpass_scene);
  this->draw_render(&vk_param->renderpass_render);
  this->draw_ui(&vk_param->renderpass_ui);
  vk_submit->submit_presentation(&vk_param->swapchain);
  vk_submit->set_next_frame_ID(&vk_param->swapchain);

  //---------------------------
}

//Draw frame parts
void VK_drawing::draw_scene(Struct_renderpass* renderpass){
  //---------------------------

  //Update descriptor
  Struct_pipeline* pipeline_point = renderpass->get_pipeline_byName("point");
  Struct_pipeline* pipeline_line = renderpass->get_pipeline_byName("line");
  vk_descriptor->update_descriptor_uniform(&pipeline_point->binding);
  vk_descriptor->update_descriptor_uniform(&pipeline_line->binding);

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer(renderpass);
  vk_cmd->cmd_record_scene(renderpass);
  vk_command->stop_command_buffer(renderpass);

  //Submit command
  Frame* frame = vk_param->swapchain.get_frame_inflight();
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame->semaphore_presentation;
  command.semaphore_to_run = frame->semaphore_scene_ready;
  command.fence = VK_NULL_HANDLE;
  vk_submit->submit_graphics_command(&command);

  //---------------------------
}
void VK_drawing::draw_render(Struct_renderpass* renderpass){
  //---------------------------

  //Update descriptor
  Frame* frame_scene = vk_param->renderpass_scene.get_rendering_frame();
  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle_EDL");
  vk_descriptor->update_descriptor_uniform(&pipeline->binding);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer(renderpass);
  vk_cmd->cmd_record_render(renderpass);
  vk_command->stop_command_buffer(renderpass);

  //Submit command
  Frame* frame = vk_param->swapchain.get_frame_inflight();
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame->semaphore_scene_ready;
  command.semaphore_to_run = frame->semaphore_render_ready;
  command.fence = VK_NULL_HANDLE;
  vk_submit->submit_graphics_command(&command);

  //---------------------------
}
void VK_drawing::draw_ui(Struct_renderpass* renderpass){
  //---------------------------

  //Update descriptor
  Frame* frame_final = vk_param->renderpass_render.get_rendering_frame();
  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle");
  vk_descriptor->update_descriptor_uniform(&pipeline->binding);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_final->color);

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer(renderpass);
  vk_cmd->cmd_record_ui(renderpass);
  vk_command->stop_command_buffer(renderpass);

  //Submit command
  Frame* frame = vk_param->swapchain.get_frame_inflight();
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame->semaphore_render_ready;
  command.semaphore_to_run = frame->semaphore_ui_ready;
  command.fence = frame->fence;
  vk_submit->submit_graphics_command(&command);

  //---------------------------
}
