#include "VK_draw_scene.h"

#include "../VK_cmd.h"

#include "../../Command/VK_submit.h"

#include "../../../VK_engine.h"
#include "../../../VK_param.h"
#include "../../../Core/Command/VK_command.h"
#include "../../../Render/Canvas/VK_canvas.h"
#include "../../../Render/Binding/VK_descriptor.h"
#include "../../../Presentation/Camera/VK_camera.h"
#include "../../../Render/Binding/VK_uniform.h"
#include "../../../Data/VK_data.h"


//Constructor / Destructor
VK_draw_scene::VK_draw_scene(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_cmd = vk_engine->get_vk_cmd();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = vk_engine->get_vk_submit();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_camera = vk_engine->get_vk_camera();
  this->vk_data = vk_engine->get_vk_data();

  //---------------------------
}
VK_draw_scene::~VK_draw_scene(){}

//Draw frame parts
void VK_draw_scene::draw_scene(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  this->record_command(renderpass);
  this->submit_command(renderpass);

  //---------------------------
  vk_param->time.renderpass_scene.push_back(timer.stop_ms(t1));
}

//Subfunction
void VK_draw_scene::record_command(Struct_renderpass* renderpass){
  Frame* frame = renderpass->get_rendering_frame();
  //---------------------------

  //Command buffer
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer_primary(renderpass->command_buffer);

  //Render pass
  vk_command->start_render_pass(renderpass, frame, false);
  vk_cmd->cmd_viewport_scene(renderpass);
  this->cmd_draw_scene(renderpass);
  this->cmd_draw_glyph(renderpass);
  vk_command->stop_render_pass(renderpass);

  vk_command->stop_command_buffer(renderpass->command_buffer);

  //---------------------------
  frame->color.name = "tex_color_scene";
  frame->depth.name = "tex_depth_scene";
}
void VK_draw_scene::submit_command(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = frame_swap->semaphore_image_ready;
  command.semaphore_to_run = frame_swap->semaphore_scene_ready;
  command.fence = VK_NULL_HANDLE;
  command.wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  vk_submit->submit_graphics_command(&command);

  //---------------------------
}

//Command function
void VK_draw_scene::cmd_draw_scene(Struct_renderpass* renderpass){
  list<Struct_data*> list_data_scene = vk_data->get_list_data_scene();
  //---------------------------

  vk_cmd->cmd_bind_pipeline(renderpass, "point");

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);

    if(data->object->draw_type_name == "point" && data->object->is_visible){
      vk_camera->compute_mvp(data->object);
      vk_uniform->update_uniform_mat4("mvp", &data->binding, data->object->mvp);
      vk_uniform->update_uniform_int("point_size", &data->binding, data->object->draw_point_size);

      vk_cmd->cmd_bind_descriptor(renderpass, "point", data->binding.descriptor.set);
      vk_cmd->cmd_draw_data(renderpass, data);
    }
  }

  //---------------------------
}
void VK_draw_scene::cmd_draw_glyph(Struct_renderpass* renderpass){
  list<Struct_data*> list_data_glyph = vk_data->get_list_data_glyph();
  //---------------------------

  vk_cmd->cmd_bind_pipeline(renderpass, "line");

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data =  *next(list_data_glyph.begin(),i);

    if(data->object->draw_type_name == "line" && data->object->is_visible){
      vk_camera->compute_mvp(data->object);
      vk_uniform->update_uniform_mat4("mvp", &data->binding, data->object->mvp);

      vk_cmd->cmd_bind_descriptor(renderpass, "line", data->binding.descriptor.set);
      vk_cmd->cmd_line_with(renderpass, data);
      vk_cmd->cmd_draw_data(renderpass, data);
    }
  }

  //---------------------------
}
