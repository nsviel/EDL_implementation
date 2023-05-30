#include "VK_command_RP.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Instance/VK_gui.h"
#include "../Pipeline/VK_pipeline.h"
#include "../Data/VK_buffer.h"
#include "../Swapchain/VK_frame.h"
#include "../Camera/VK_camera.h"
#include "../Camera/VK_viewport.h"
#include "../Shader/VK_uniform.h"
#include "../Rendering/VK_canvas.h"
#include "../Data/VK_data.h"


//Constructor / Destructor
VK_command_RP::VK_command_RP(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_pipeline = engineManager->get_vk_pipeline();
  this->vk_camera = engineManager->get_vk_camera();
  this->vk_frame = engineManager->get_vk_image();
  this->vk_canvas = engineManager->get_vk_canvas();
  this->vk_uniform = engineManager->get_vk_uniform();
  this->vk_data = engineManager->get_vk_data();
  this->vk_viewport = engineManager->get_vk_viewport();

  //---------------------------
}
VK_command_RP::~VK_command_RP(){}

//Renderpass commands
void VK_command_RP::command_viewport(VkCommandBuffer command_buffer){
  //---------------------------

  vk_viewport->update_viewport(param_vulkan->window.extent);

  VkViewport viewport = vk_viewport->get_viewport();
  VkRect2D scissor = vk_viewport->get_scissor();

  vkCmdSetViewport(command_buffer, 0, 1, &viewport);
  vkCmdSetScissor(command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_command_RP::command_drawing_scene(VkCommandBuffer command_buffer){
  //---------------------------

  Frame_inflight* frame = param_vulkan->swapchain.get_current_frame();

  //Bind pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName("scene");
  vkCmdBindPipeline(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);
  vkCmdBindDescriptorSets(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->descriptor_set, 0, nullptr);

  //Bind and draw vertex buffers
  list<Object*> list_data = vk_data->get_list_obj_scene();
  for(int i=0; i<list_data.size(); i++){
    Object* object = *next(list_data.begin(),i);

    if(object->draw_type_name == "point"){
      vk_camera->compute_mvp(object);
      vk_uniform->update_uniform_buffer(pipeline, object->mvp);

      //vkCmdPushConstants(command_buffer, pipeline->pipeline_layout, STAGE_VS, 0, sizeof(glm::mat4), &object->mvp);
      VkBuffer vertexBuffers[] = {object->vbo_xyz, object->vbo_rgb};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_command_RP::command_drawing_glyph(VkCommandBuffer command_buffer){
  //---------------------------

  Frame_inflight* frame = param_vulkan->swapchain.get_current_frame();

  //Bind pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName("glyph");
  vkCmdBindPipeline(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);
  vkCmdBindDescriptorSets(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->descriptor_set, 0, nullptr);

  //Bind and draw vertex buffers
  list<Object*> list_glyph = vk_data->get_list_obj_glyph();
  for(int i=0; i<list_glyph.size(); i++){
    Object* object = *next(list_glyph.begin(),i);

    if(object->draw_type_name == "line"){
      vk_camera->compute_mvp(object);
      vkCmdPushConstants(command_buffer, pipeline->pipeline_layout, STAGE_VS, 0, sizeof(glm::mat4), &object->mvp);
      VkBuffer vertexBuffers[] = {object->vbo_xyz, object->vbo_rgb};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdSetLineWidth(command_buffer, object->draw_line_width);
      vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_command_RP::command_drawing_canvas(VkCommandBuffer command_buffer){
  Frame_inflight* frame = param_vulkan->swapchain.get_current_frame();
  //---------------------------

  //Bind pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName("canvas");
  vkCmdBindPipeline(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);
  vkCmdBindDescriptorSets(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->descriptor_set, 0, nullptr);

  //Bind and draw vertex buffers
  Object* canvas = vk_canvas->get_canvas();
  vk_camera->compute_mvp(canvas);
  vkCmdPushConstants(command_buffer, pipeline->pipeline_layout, STAGE_VS, 0, sizeof(glm::mat4), &canvas->mvp);
  VkBuffer vertexBuffers[] = {canvas->vbo_xyz, canvas->vbo_uv};
  VkDeviceSize offsets[] = {0, 0};
  vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
  //vkCmdDraw(command_buffer, canvas->xyz.size(), 1, 0, 0);

  //---------------------------
}
