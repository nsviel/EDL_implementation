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
#include "../../Render/Binding/VK_descriptor.h"
#include "../../Render/Binding/VK_uniform.h"
#include "../../Render/Canvas/VK_canvas.h"
#include "../../Data/VK_data.h"

#include "../../../Node_engine.h"
#include "../../../Shader/Shader.h"
#include "../../../Shader/Source/EDL/Shader_edl.h"

#include "../../../../Specific/Function/fct_math.h"


//Constructor / Destructor
VK_cmd::VK_cmd(VK_engine* vk_engine){
  //---------------------------

  Node_engine* node_engine = vk_engine->get_node_engine();
  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_camera = vk_engine->get_vk_camera();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_gui = vk_engine->get_vk_gui();

  this->vk_canvas = vk_engine->get_vk_canvas();

  Shader* shaderManager = node_engine->get_shaderManager();
  this->shader_edl = shaderManager->get_shader_edl();

  //---------------------------
}
VK_cmd::~VK_cmd(){}

//Main function
void VK_cmd::cmd_viewport_scene(Struct_renderpass* renderpass){
  //---------------------------

  VkViewport viewport = vk_viewport->get_viewport_scene();

  //Viewport
  vkCmdSetViewport(renderpass->command_buffer, 0, 1, &viewport);

  //Scissor
  VkRect2D scissor = vk_viewport->get_scissor();
  vkCmdSetScissor(renderpass->command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_cmd::cmd_viewport_canvas(Struct_renderpass* renderpass){
  //---------------------------

  VkViewport viewport = vk_viewport->get_viewport_canvas();

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
