#include "VK_draw_ui.h"
#include "../../Drawing/VK_cmd.h"
#include "../../Command/VK_submit.h"
#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Command/VK_command.h"
#include "../../Presentation/VK_canvas.h"
#include "../../Binding/VK_descriptor.h"
#include "../../Binding/VK_uniform.h"
#include "../../Data/VK_data.h"
#include "../../Window/VK_gui.h"


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
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_canvas = vk_engine->get_vk_canvas();

  //---------------------------
}
VK_draw_ui::~VK_draw_ui(){}

//Main function
void VK_draw_ui::draw_ui(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  this->update_descriptor(renderpass);
  this->record_command(renderpass);
  this->submit_command(renderpass);

  //---------------------------
  vk_param->time.renderpass_ui.push_back(timer.stop_ms(t1));
}

//Subfunction
void VK_draw_ui::update_descriptor(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_edl = vk_param->renderpass_edl.get_rendering_frame();
  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle");
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, &frame_edl->color);

  //---------------------------
}
void VK_draw_ui::record_command(Struct_renderpass* renderpass){
  Frame* frame = vk_param->swapchain.get_frame_current();
  //---------------------------

  //Command buffer
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer_primary(renderpass->command_buffer);

  //Render pass
  vk_command->start_render_pass(renderpass, frame, false);
  vk_cmd->cmd_viewport_canvas(renderpass);
  this->cmd_draw(renderpass);
  vk_gui->command_gui(renderpass);
  vk_command->stop_render_pass(renderpass);
  vk_command->stop_command_buffer(renderpass->command_buffer);

  //---------------------------
}
void VK_draw_ui::submit_command(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame_swap->semaphore_edl_ready;
  command.semaphore_to_run = frame_swap->semaphore_ui_ready;
  command.fence = frame_swap->fence;
  command.wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  vk_submit->submit_graphics_command(&command);

  //---------------------------
}

//Command function
void VK_draw_ui::cmd_draw(Struct_renderpass* renderpass){
  //---------------------------

  Struct_pipeline* pipeline = renderpass->get_pipeline_byName("triangle");
  Struct_data* canvas = vk_canvas->get_data_canvas();

  vk_cmd->cmd_bind_pipeline(renderpass, "triangle");
  vk_cmd->cmd_bind_descriptor(renderpass, "triangle", pipeline->binding.descriptor.set);
  vk_cmd->cmd_draw_data(renderpass, canvas);

  //---------------------------
}
