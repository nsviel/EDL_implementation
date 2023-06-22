#include "VK_draw_ui.h"
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
#include "../../../Instance/Element/VK_gui.h"


//Constructor / Destructor
VK_draw_ui::VK_draw_ui(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_cmd = vk_engine->get_vk_cmd();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = vk_engine->get_vk_submit();
  this->vk_gui = vk_engine->get_vk_gui();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_camera = vk_engine->get_vk_camera();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_canvas = vk_engine->get_vk_canvas();

  //---------------------------
}
VK_draw_ui::~VK_draw_ui(){}

//Main function
void VK_draw_ui::draw_ui(Struct_renderpass* renderpass){
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
  this->cmd_record_ui(renderpass);
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
void VK_draw_ui::cmd_record_ui(Struct_renderpass* renderpass){
  Frame* frame = vk_param->swapchain.get_frame_current();
  //---------------------------

  vk_command->start_render_pass(renderpass, frame, false);
  vk_cmd->cmd_viewport(renderpass, vk_viewport->get_viewport_canvas());
  this->cmd_draw_canvas(renderpass);
  vk_gui->command_gui(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void VK_draw_ui::cmd_draw_canvas(Struct_renderpass* renderpass){
  //---------------------------

  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "triangle");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Descriptor
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
