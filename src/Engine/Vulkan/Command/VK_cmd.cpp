#include "VK_cmd.h"

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
VK_cmd::VK_cmd(Engine* engineManager){
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
VK_cmd::~VK_cmd(){}

//Renderpass commands
void VK_cmd::cmd_viewport(VkCommandBuffer command_buffer){
  //---------------------------

  vk_viewport->update_viewport(param_vulkan->window.extent);

  VkViewport viewport = vk_viewport->get_viewport();
  VkRect2D scissor = vk_viewport->get_scissor();

  vkCmdSetViewport(command_buffer, 0, 1, &viewport);
  vkCmdSetScissor(command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_cmd::cmd_drawing_scene(VkCommandBuffer command_buffer){
  //---------------------------

  //Get relative obejct
  list<Struct_data*> list_data_scene = vk_data->get_list_data_scene();
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName("scene");

  //Bind pipeline
  vkCmdBindPipeline(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "point"){
      vk_camera->compute_mvp(object);
      vk_uniform->update_uniform_mat4("mvp", data->binding, object->mvp);
      vkCmdBindDescriptorSets(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &data->binding.descriptor.set, 0, nullptr);

      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_cmd::cmd_drawing_glyph(VkCommandBuffer command_buffer){
  //---------------------------

  //Get relative obejct
  list<Struct_data*> list_data_glyph = vk_data->get_list_data_glyph();
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName("glyph");

  //Bind pipeline
  vkCmdBindPipeline(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data =  *next(list_data_glyph.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "line"){
      vk_camera->compute_mvp(object);
      vk_uniform->update_uniform_mat4("mvp", data->binding, object->mvp);
      vkCmdBindDescriptorSets(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &data->binding.descriptor.set, 0, nullptr);

      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdSetLineWidth(command_buffer, object->draw_line_width);
      vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_cmd::cmd_drawing_canvas(VkCommandBuffer command_buffer){
  //---------------------------

  //Get relative obejct
  Struct_data* data_canvas = vk_canvas->get_canvas();
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName("canvas");

  //Bind pipeline
  vkCmdBindPipeline(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);
  //vkCmdBindDescriptorSets(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

  //Bind and draw vertex buffers
  Object* canvas = data_canvas->object;
  vk_camera->compute_mvp(canvas);
  vkCmdPushConstants(command_buffer, pipeline->pipeline_layout, STAGE_VS, 0, sizeof(glm::mat4), &canvas->mvp);
  VkBuffer vertexBuffers[] = {data_canvas->xyz.vbo, data_canvas->uv.vbo};
  VkDeviceSize offsets[] = {0, 0};
  vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
  //vkCmdDraw(command_buffer, canvas->xyz.size(), 1, 0, 0);

  //---------------------------
}
