#include "UI_drawing.h"
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
UI_drawing::UI_drawing(VK_engine* vk_engine){
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
UI_drawing::~UI_drawing(){}

//Main function
void UI_drawing::draw_ui(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  this->record_command(renderpass);
  this->submit_command(renderpass);

  //---------------------------
  vk_param->time.renderpass_ui.push_back(timer.stop_ms(t1));
}

//Subfunction
void UI_drawing::record_command(Struct_renderpass* renderpass){
  Frame* frame = vk_param->swapchain.get_frame_current();
  //---------------------------

  vk_command->start_render_pass(renderpass, frame, false);
  vk_cmd->cmd_viewport_canvas(renderpass);
  vk_gui->command_gui(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void UI_drawing::submit_command(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();
  renderpass->semaphore_to_wait = frame_swap->semaphore_edl_ready;
  renderpass->semaphore_to_run = frame_swap->semaphore_ui_ready;
  renderpass->fence = frame_swap->fence;
  vk_submit->submit_graphics_command(renderpass);

  //---------------------------
}
