#include "VK_cmd.h"

#include "../Command/VK_command.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Instance/Element/VK_gui.h"
#include "../../Core/Pipeline/VK_pipeline.h"
#include "../../Data/VK_buffer.h"
#include "../../Presentation/Swapchain/VK_frame.h"
#include "../../Presentation/Camera/VK_camera.h"
#include "../../Presentation/Camera/VK_viewport.h"
#include "../../Render/Binding/VK_binding.h"
#include "../../Render/Binding/VK_descriptor.h"
#include "../../Render/Binding/VK_uniform.h"
#include "../../Render/Canvas/VK_canvas.h"
#include "../../Data/VK_data.h"

#include "../../../Node_engine.h"
#include "../../../Shader/Source/EDL/Shader_edl.h"


//Constructor / Destructor
VK_cmd::VK_cmd(VK_engine* vk_engine){
  //---------------------------

  Node_engine* node_engine = vk_engine->get_node_engine();
  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_camera = vk_engine->get_vk_camera();
  this->vk_canvas = vk_engine->get_vk_canvas();
  this->vk_binding = vk_engine->get_vk_binding();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->shader_edl = node_engine->get_shader_edl();

  //---------------------------
}
VK_cmd::~VK_cmd(){}

//Main function
void VK_cmd::cmd_record_scene(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  Frame* frame = renderpass->get_rendering_frame();
  vk_command->start_render_pass(renderpass, frame, false);
  this->cmd_viewport(renderpass->command_buffer);
  this->cmd_scissor(renderpass->command_buffer);
  this->cmd_draw_scene(renderpass);
  this->cmd_draw_glyph(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
  frame->color.name = "tex_color_scene";
  frame->depth.name = "tex_depth_scene";
}
void VK_cmd::cmd_record_render(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  Frame* frame = renderpass->get_rendering_frame();
  vk_command->start_render_pass(renderpass, frame, false);
  VkViewport viewport = vk_viewport->get_viewport_canvas();
  vkCmdSetViewport(renderpass->command_buffer, 0, 1, &viewport);
  this->cmd_scissor(renderpass->command_buffer);
  this->cmd_draw_edl(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
  frame->color.name = "tex_color_final";
  frame->depth.name = "tex_depth_final";
}
void VK_cmd::cmd_record_ui(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  VK_gui* vk_gui = vk_engine->get_vk_gui();
  //---------------------------

  Frame* frame = vk_param->swapchain.get_frame_current();
  vk_command->start_render_pass(renderpass, frame, false);
  VkViewport viewport = vk_viewport->get_viewport_canvas();
  vkCmdSetViewport(renderpass->command_buffer, 0, 1, &viewport);
  this->cmd_scissor(renderpass->command_buffer);
  this->cmd_draw_canvas(renderpass);
  vk_gui->command_gui(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}

//Renderpass commands
void VK_cmd::cmd_viewport(VkCommandBuffer command_buffer){
  //---------------------------

  vk_viewport->update_viewport(vk_param->window.extent);
  VkViewport viewport = vk_viewport->get_viewport();
  vkCmdSetViewport(command_buffer, 0, 1, &viewport);

  //---------------------------
}
void VK_cmd::cmd_scissor(VkCommandBuffer command_buffer){
  //---------------------------

  VkRect2D scissor = vk_viewport->get_scissor();
  vkCmdSetScissor(command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_cmd::cmd_draw_scene(Struct_renderpass* renderpass){
  //---------------------------

  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "point");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  list<Struct_data*> list_data_scene = vk_data->get_list_data_scene();
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "point"){
      //Camera
      vk_camera->compute_mvp(object);
      vk_uniform->update_uniform_mat4("mvp", &pipeline->binding, data->object->mvp);
      vk_uniform->update_uniform_int("point_size", &pipeline->binding, data->object->draw_point_size);
      vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

      //Data
      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(renderpass->command_buffer, object->xyz.size(), 1, 0, 0);

      //vkCmdExecuteCommands(renderpass->command_buffer, 1, &data->command_buffer);
    }
  }

  //---------------------------
}
void VK_cmd::cmd_draw_glyph(Struct_renderpass* renderpass){
  //---------------------------

  //Pipine
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "line");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  list<Struct_data*> list_data_glyph = vk_data->get_list_data_glyph();
  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data =  *next(list_data_glyph.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "line"){
      //Camera
      vk_camera->compute_mvp(object);
      vk_uniform->update_uniform_mat4("mvp", &pipeline->binding, data->object->mvp);
      vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

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
void VK_cmd::cmd_draw_canvas(Struct_renderpass* renderpass){
  //---------------------------

  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "triangle");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Descriptor
  vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

  //Data
  Struct_data* data = vk_canvas->get_data_canvas();
  Object* canvas = data->object;
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 1, &data->xyz.vbo, offsets);
  vkCmdBindVertexBuffers(renderpass->command_buffer, 2, 1, &data->uv.vbo, offsets);
  vkCmdDraw(renderpass->command_buffer, canvas->xyz.size(), 1, 0, 0);

  //---------------------------
}
void VK_cmd::cmd_draw_edl(Struct_renderpass* renderpass){
  //---------------------------

  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "triangle_EDL");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  shader_edl->update_shader();
  Struct_edl* edl_param = shader_edl->get_edl_param();

  //Descriptor
  vk_uniform->update_uniform_edl("Struct_edl", &pipeline->binding, *edl_param);
  vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

  //Data
  Struct_data* data = vk_canvas->get_data_canvas();
  Object* canvas = data->object;
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 1, &data->xyz.vbo, offsets);
  vkCmdBindVertexBuffers(renderpass->command_buffer, 2, 1, &data->uv.vbo, offsets);
  vkCmdDraw(renderpass->command_buffer, canvas->xyz.size(), 1, 0, 0);

  //---------------------------
}

//Secondary command buffer
void VK_cmd::cmd_record_scene_secondcb(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  //Bind and draw vertex buffers
  list<Struct_data*> list_data_scene = vk_data->get_list_data_scene();
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "point"){
      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};

      vkResetCommandBuffer(data->command_buffer, 0);
      vk_command->start_command_buffer_secondary(renderpass, data->command_buffer);

      Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "point");
      vkCmdBindPipeline(data->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

      this->cmd_viewport(data->command_buffer);
      this->cmd_scissor(data->command_buffer);

      //vk_camera->compute_mvp(object);
      //vk_uniform->update_uniform_mat4("mvp", &pipeline->binding, data->object->mvp);
      vkCmdBindDescriptorSets(data->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

      vkCmdBindVertexBuffers(data->command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(data->command_buffer, object->xyz.size(), 1, 0, 0);

      vk_command->stop_command_buffer(data->command_buffer);
    }
  }

  //---------------------------
}
