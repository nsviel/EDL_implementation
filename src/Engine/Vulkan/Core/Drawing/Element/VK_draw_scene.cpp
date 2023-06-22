#include "VK_draw_scene.h"
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


//Constructor / Destructor
VK_draw_scene::VK_draw_scene(VK_engine* vk_engine){
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

  //---------------------------
}
VK_draw_scene::~VK_draw_scene(){}

//Draw frame parts
void VK_draw_scene::draw_scene(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();

  //Record command
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer_primary(renderpass->command_buffer);
  this->cmd_record_scene(renderpass);
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
void VK_draw_scene::cmd_record_scene(Struct_renderpass* renderpass){
  Frame* frame = renderpass->get_rendering_frame();
  //---------------------------

  vk_command->start_render_pass(renderpass, frame, false);
  vk_cmd->cmd_viewport(renderpass, vk_viewport->get_viewport_scene());
  this->cmd_draw_scene(renderpass);
  this->cmd_draw_glyph(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
  frame->color.name = "tex_color_scene";
  frame->depth.name = "tex_depth_scene";
}
void VK_draw_scene::cmd_draw_scene(Struct_renderpass* renderpass){
  //---------------------------

  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "point");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  list<Struct_data*> list_data_scene = vk_data->get_list_data_scene();
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "point" && object->is_visible){
      //Camera
      vk_camera->compute_mvp(object);
      vk_uniform->update_uniform_mat4("mvp", &data->binding, data->object->mvp);
      vk_uniform->update_uniform_int("point_size", &data->binding, data->object->draw_point_size);
      vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &data->binding.descriptor.set, 0, nullptr);

      //Data
      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(renderpass->command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_draw_scene::cmd_draw_glyph(Struct_renderpass* renderpass){
  //---------------------------

  //Pipine
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "line");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  list<Struct_data*> list_data_glyph = vk_data->get_list_data_glyph();
  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data =  *next(list_data_glyph.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "line" && object->is_visible){
      //Camera
      vk_camera->compute_mvp(object);
      vk_uniform->update_uniform_mat4("mvp", &data->binding, data->object->mvp);
      vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &data->binding.descriptor.set, 0, nullptr);

      //Data
      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdSetLineWidth(renderpass->command_buffer, object->draw_line_width);
      vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(renderpass->command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
