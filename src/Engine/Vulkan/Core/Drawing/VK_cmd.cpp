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
