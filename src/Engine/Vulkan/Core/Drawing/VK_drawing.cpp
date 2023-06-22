#include "VK_drawing.h"
#include "VK_cmd.h"

#include "../Pipeline/VK_pipeline.h"
#include "../Command/VK_submit.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Core/Command/VK_command.h"
#include "../../Render/Canvas/VK_canvas.h"
#include "../../Render/Binding/VK_descriptor.h"


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
  Struct_submit_commands commands;
  timer_time t1 = timer.start_t();
  //---------------------------

  vk_submit->acquire_next_image(&vk_param->swapchain);
  this->draw_scene(&vk_param->renderpass_scene);
  this->draw_edl(&vk_param->renderpass_edl);
  this->draw_psr(&vk_param->renderpass_psr);
  this->draw_ui(&vk_param->renderpass_ui);
  vk_submit->submit_presentation(&vk_param->swapchain);
  vk_submit->set_next_frame_ID(&vk_param->swapchain);

  //---------------------------
  vk_param->time.draw_frame.push_back(timer.stop_ms(t1));
}

//Draw frame parts
void VK_drawing::draw_scene(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer_primary(renderpass->command_buffer);
  vk_cmd->cmd_record_scene(renderpass);
  vk_command->stop_command_buffer(renderpass->command_buffer);

  //Submit command
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame_swap->semaphore_image_ready;
  command.semaphore_to_run = frame_swap->semaphore_scene_ready;
  command.fence = VK_NULL_HANDLE;
  command.wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  vk_submit->submit_graphics_command(&command);

  //---------------------------
  vk_param->time.renderpass_scene.push_back(timer.stop_ms(t1));
}
void VK_drawing::draw_edl(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  Frame* frame_scene = vk_param->renderpass_scene.get_rendering_frame();
  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();

  //Update descriptor
  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle_EDL");
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer_primary(renderpass->command_buffer);
  vk_cmd->cmd_record_edl(renderpass);
  vk_command->stop_command_buffer(renderpass->command_buffer);

  //Submit command
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame_swap->semaphore_scene_ready;
  command.semaphore_to_run = frame_swap->semaphore_render_ready;
  command.fence = VK_NULL_HANDLE;
  command.wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  vk_submit->submit_graphics_command(&command);

  //---------------------------
  vk_param->time.renderpass_edl.push_back(timer.stop_ms(t1));
}
void VK_drawing::draw_psr(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  Frame* frame_scene = vk_param->renderpass_scene.get_rendering_frame();
  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();

  //Update descriptor
  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle");
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->color);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_scene->depth);

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer_primary(renderpass->command_buffer);
  //vk_cmd->cmd_record_edl(renderpass);
  vk_command->stop_command_buffer(renderpass->command_buffer);

  //Submit command
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame_swap->semaphore_scene_ready;
  command.semaphore_to_run = frame_swap->semaphore_render_ready;
  command.fence = VK_NULL_HANDLE;
  command.wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  //vk_submit->submit_graphics_command(&command);

  //---------------------------
  vk_param->time.renderpass_psr.push_back(timer.stop_ms(t1));
}
void VK_drawing::draw_ui(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  Frame* frame_edl = vk_param->renderpass_edl.get_rendering_frame();
  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();

  //Update descriptor
  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle");
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_edl->color);

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer_primary(renderpass->command_buffer);
  vk_cmd->cmd_record_ui(renderpass);
  vk_command->stop_command_buffer(renderpass->command_buffer);

  //Submit command
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame_swap->semaphore_render_ready;
  command.semaphore_to_run = frame_swap->semaphore_ui_ready;
  command.fence = frame_swap->fence;
  command.wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  vk_submit->submit_graphics_command(&command);

  //---------------------------
  vk_param->time.renderpass_ui.push_back(timer.stop_ms(t1));
}

//Subfunction
void VK_drawing::submit_draw(Struct_renderpass* renderpass){
  //---------------------------


  //---------------------------
}
