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

  vk_submit->acquire_next_image(&vk_param->renderpass_canvas);
  this->draw_scene(&vk_param->renderpass_scene);
  this->draw_canvas(&vk_param->renderpass_canvas);
  this->draw_gui(&vk_param->renderpass_gui);
  vk_submit->submit_presentation(&vk_param->renderpass_canvas);
  vk_submit->set_next_frame_ID(&vk_param->renderpass_canvas);

  //---------------------------
}

//Draw frame parts
void VK_drawing::draw_scene(Struct_renderpass* renderpass){
  //---------------------------

  VK_pipeline* vk_pipeline = vk_engine->get_vk_pipeline();
  Struct_pipeline* pipeline_point = vk_pipeline->get_pipeline_byName(renderpass, "point");
  Struct_pipeline* pipeline_line = vk_pipeline->get_pipeline_byName(renderpass, "line");
  vk_descriptor->update_descriptor_uniform(&pipeline_point->binding);
  vk_descriptor->update_descriptor_uniform(&pipeline_line->binding);



  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer(renderpass);
  vk_cmd->cmd_record_scene(renderpass);
  vk_command->stop_command_buffer(renderpass);

  //Submit command
  Frame* frame = vk_param->renderpass_canvas.frame_set->get_frame_inflight();
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame->semaphore_presentation;
  command.semaphore_to_run = frame->semaphore_renderOnTexture;
  command.fence = VK_NULL_HANDLE;
  vk_submit->submit_command(&command);

  //---------------------------
}
void VK_drawing::draw_canvas(Struct_renderpass* renderpass){
  Frame* frame = renderpass->frame_set->get_frame_inflight();
  //---------------------------

  VK_pipeline* vk_pipeline = vk_engine->get_vk_pipeline();
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "triangle");
  VK_canvas* vk_canvas = vk_engine->get_vk_canvas();
  Frame *frame_scene = vk_param->renderpass_scene.frame_set->get_frame_inflight();
  Struct_data* data = vk_canvas->get_data_canvas();
  list<Struct_image*> vec_image;
  vec_image.push_back(&frame_scene->color);
  vk_descriptor->update_descriptor_uniform(&pipeline->binding);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, vec_image);

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer(renderpass);
  vk_cmd->cmd_record_canvas(renderpass);
  vk_command->stop_command_buffer(renderpass);

  //Submit command
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame->semaphore_renderOnTexture;
  command.semaphore_to_run = frame->semaphore_drawOnQuad;
  command.fence = VK_NULL_HANDLE;
  vk_submit->submit_command(&command);

  //---------------------------
}
void VK_drawing::draw_gui(Struct_renderpass* renderpass){
  //---------------------------

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer(renderpass);
  vk_cmd->cmd_record_gui(renderpass);
  vk_command->stop_command_buffer(renderpass);

  //Submit command
  Frame* frame = renderpass->frame_set->get_frame_inflight();
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame->semaphore_drawOnQuad;
  command.semaphore_to_run = frame->semaphore_gui;
  command.fence = frame->fence;
  vk_submit->submit_command(&command);

  //---------------------------
}
