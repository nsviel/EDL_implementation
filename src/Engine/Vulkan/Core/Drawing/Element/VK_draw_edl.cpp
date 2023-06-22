#include "VK_draw_edl.h"

#include "../VK_cmd.h"

#include "../../Pipeline/VK_pipeline.h"
#include "../../Command/VK_submit.h"

#include "../../../VK_engine.h"
#include "../../../VK_param.h"
#include "../../../Core/Command/VK_command.h"
#include "../../../Render/Canvas/VK_canvas.h"
#include "../../../Render/Binding/VK_descriptor.h"

#include "../../../Core/Pipeline/VK_pipeline.h"
#include "../../../Presentation/Camera/VK_camera.h"
#include "../../../Presentation/Camera/VK_viewport.h"
#include "../../../Render/Binding/VK_uniform.h"
#include "../../../Data/VK_data.h"

#include "../../../../Node_engine.h"
#include "../../../../Shader/Shader.h"
#include "../../../../Shader/Source/EDL/Shader_edl.h"


//Constructor / Destructor
VK_draw_edl::VK_draw_edl(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_cmd = vk_engine->get_vk_cmd();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = vk_engine->get_vk_submit();

  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_camera = vk_engine->get_vk_camera();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_canvas = vk_engine->get_vk_canvas();

  Node_engine* node_engine = vk_engine->get_node_engine();
  Shader* shaderManager = node_engine->get_shaderManager();
  this->shader_edl = shaderManager->get_shader_edl();

  //---------------------------
}
VK_draw_edl::~VK_draw_edl(){}

//Main function
void VK_draw_edl::draw_edl(Struct_renderpass* renderpass){
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
  this->cmd_record_edl(renderpass);
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
void VK_draw_edl::cmd_record_edl(Struct_renderpass* renderpass){
  Frame* frame = renderpass->get_rendering_frame();
  //---------------------------

  vk_command->start_render_pass(renderpass, frame, false);
  vk_cmd->cmd_viewport(renderpass, vk_viewport->get_viewport_canvas());
  this->cmd_draw_edl(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
  frame->color.name = "tex_color_edl";
  frame->depth.name = "tex_depth_edl";
}
void VK_draw_edl::cmd_draw_edl(Struct_renderpass* renderpass){
  //---------------------------

  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "triangle_EDL");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  shader_edl->update_shader();
  Struct_edl* edl_param = shader_edl->get_edl_param();

  //Descriptor
  vk_uniform->update_uniform_edl("Struct_edl", &pipeline->binding, *edl_param);
  vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

  //Data
  Struct_data* data = vk_canvas->get_data_canvas();
  Object* canvas = data->object;
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 1, &data->xyz.vbo, offsets);
  vkCmdBindVertexBuffers(renderpass->command_buffer, 2, 1, &data->uv.vbo, offsets);
  vkCmdDraw(renderpass->command_buffer, canvas->xyz.size(), 1, 0, 0);

  //---------------------------
}
