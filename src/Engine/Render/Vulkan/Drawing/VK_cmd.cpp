#include "VK_cmd.h"

#include "../VK_engine.h"
#include "../VK_param.h"
#include "../Camera/VK_viewport.h"

#include <Specific/Function/fct_math.h>


//Constructor / Destructor
VK_cmd::VK_cmd(VK_engine* vk_engine){
  //---------------------------

  Render_node* render_node = vk_engine->get_render_node();
  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_viewport = vk_engine->get_vk_viewport();

  //---------------------------
}
VK_cmd::~VK_cmd(){}

//Main function
void VK_cmd::cmd_viewport_scene(Struct_renderpass* renderpass){
  //---------------------------

  VkViewport viewport = vk_viewport->get_viewport();

  //Viewport
  vkCmdSetViewport(renderpass->command_buffer, 0, 1, &viewport);

  //Scissor
  VkRect2D scissor = vk_viewport->get_scissor();
  vkCmdSetScissor(renderpass->command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_cmd::cmd_viewport_canvas(Struct_renderpass* renderpass){
  //---------------------------

  VkViewport viewport = vk_viewport->get_viewport();

  //Viewport
  vkCmdSetViewport(renderpass->command_buffer, 0, 1, &viewport);

  //Scissor
  VkRect2D scissor = vk_viewport->get_scissor();
  vkCmdSetScissor(renderpass->command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_cmd::cmd_bind_pipeline(Struct_renderpass* renderpass, string pipeline_name){
  //---------------------------

  Struct_pipeline* pipeline = renderpass->get_pipeline_byName(pipeline_name);
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //---------------------------
}
void VK_cmd::cmd_draw_data(Struct_renderpass* renderpass, Struct_data* data){
  //---------------------------

  VkDeviceSize offsets[] = {0};
  if(data->xyz.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 1, &data->xyz.vbo, offsets);
  }
  if(data->rgb.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(renderpass->command_buffer, 1, 1, &data->rgb.vbo, offsets);
  }
  if(data->uv.vbo != VK_NULL_HANDLE){
    vkCmdBindVertexBuffers(renderpass->command_buffer, 2, 1, &data->uv.vbo, offsets);
  }
  vkCmdDraw(renderpass->command_buffer, data->object->xyz.size(), 1, 0, 0);

  //---------------------------
}
void VK_cmd::cmd_bind_descriptor(Struct_renderpass* renderpass, string pipeline_name, VkDescriptorSet set){
  //---------------------------

  Struct_pipeline* pipeline = renderpass->get_pipeline_byName(pipeline_name);
  vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &set, 0, nullptr);

  //---------------------------
}
void VK_cmd::cmd_line_with(Struct_renderpass* renderpass, Struct_data* data){
  //---------------------------

  vkCmdSetLineWidth(renderpass->command_buffer, data->object->draw_line_width);

  //---------------------------
}
