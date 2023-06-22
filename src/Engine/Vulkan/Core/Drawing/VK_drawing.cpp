#include "VK_drawing.h"
#include "VK_cmd.h"

#include "Element/VK_draw_scene.h"
#include "Element/VK_draw_edl.h"
#include "Element/VK_draw_psr.h"
#include "Element/VK_draw_ui.h"

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
  this->vk_draw_scene = new VK_draw_scene(vk_engine);
  this->vk_draw_edl = new VK_draw_edl(vk_engine);
  this->vk_draw_psr = new VK_draw_psr(vk_engine);
  this->vk_draw_ui = new VK_draw_ui(vk_engine);

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  Struct_submit_commands commands;
  timer_time t1 = timer.start_t();
  //---------------------------

  vk_submit->acquire_next_image(&vk_param->swapchain);
  vk_draw_scene->draw_scene(&vk_param->renderpass_scene);
  vk_draw_edl->draw_edl(&vk_param->renderpass_edl);
  //vk_draw_psr->draw_psr(&vk_param->renderpass_psr);
  vk_draw_ui->draw_ui(&vk_param->renderpass_ui);
  vk_submit->submit_presentation(&vk_param->swapchain);
  vk_submit->set_next_frame_ID(&vk_param->swapchain);

  //---------------------------
  vk_param->time.draw_frame.push_back(timer.stop_ms(t1));
}
