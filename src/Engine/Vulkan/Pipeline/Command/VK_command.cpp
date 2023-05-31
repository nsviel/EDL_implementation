#include "VK_command.h"
#include "VK_cmd.h"

#include "../../VK_param.h"
#include "../../VK_engine.h"
#include "../../Instance/Element/VK_gui.h"
#include "../../Instance/Element/VK_window.h"
#include "../../Pipeline/Renderpass/VK_renderpass.h"
#include "../../Pipeline/VK_pipeline.h"
#include "../../Instance/Device/VK_device.h"
#include "../../Instance/Device/VK_physical_device.h"
#include "../../Data/VK_buffer.h"
#include "../../Data/VK_data.h"
#include "../../Presentation/Swapchain/VK_frame.h"
#include "../../Presentation/Camera/VK_viewport.h"
#include "../../Presentation/Camera/VK_camera.h"
#include "../../Pipeline/Rendering/VK_canvas.h"

#include "../../../Param_engine.h"


//Constructor / Destructor
VK_command::VK_command(VK_engine* vk_engine){
  //---------------------------

  this->param_engine = vk_engine->get_param_engine();
  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_renderpass = vk_engine->get_vk_renderpass();
  this->vk_physical_device = vk_engine->get_vk_physical_device();
  this->vk_cmd = new VK_cmd(vk_engine);

  //---------------------------
}
VK_command::~VK_command(){}

//Main function
void VK_command::create_command_pool(){
  //---------------------------

  int family_graphics = vk_physical_device->find_queue_family_graphics(vk_param->device.physical_device);

  //Command pool info
  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = family_graphics;

  //Command pool creation
  VkResult result = vkCreateCommandPool(vk_param->device.device, &poolInfo, nullptr, &command_pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create command pool!");
  }

  //---------------------------
}
void VK_command::create_command_buffer(vector<Frame_inflight*> vec_frame_inflight){
  //---------------------------

  //One command buffer per frame
  vector<VkCommandBuffer> command_buffer_vec;
  command_buffer_vec.resize(vk_param->instance.max_frame);

  //Command buffer allocation
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = command_pool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t) command_buffer_vec.size();

  VkResult result = vkAllocateCommandBuffers(vk_param->device.device, &allocInfo, command_buffer_vec.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  for(int i=0; i<vec_frame_inflight.size(); i++){
    Frame_inflight* frame = vec_frame_inflight[i];
    frame->command_buffer = command_buffer_vec[i];
  }

  //---------------------------
}
void VK_command::cleanup(){
  //---------------------------

  vkDestroyCommandPool(vk_param->device.device, command_pool, nullptr);

  //---------------------------
}

//Drawing commands
void VK_command::record_command_buffer(VkCommandBuffer& command_buffer){
  VK_gui* vk_gui = vk_engine->get_vk_gui();
  //---------------------------


  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = 0;
  beginInfo.pInheritanceInfo = nullptr; // Optional

  VkResult result = vkBeginCommandBuffer(command_buffer, &beginInfo);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //Starting a render pass
  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {{
    param_engine->background_color.x,
    param_engine->background_color.y,
    param_engine->background_color.z,
    param_engine->background_color.w}};
  clearValues[1].depthStencil = {1.0f, 0};

  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = vk_renderpass->get_renderPass();
  //renderPassInfo.framebuffer = vec_image_obj[vk_param->swapchain.current_frame_swapchain_ID]->fbo;

  Frame_swapchain* image = vk_param->swapchain.get_current_frame_swapchain();
  renderPassInfo.framebuffer = image->fbo;
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = vk_param->window.extent;
  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassInfo.pClearValues = clearValues.data();

  vkCmdBeginRenderPass(command_buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

  vk_cmd->cmd_viewport(command_buffer);
  vk_cmd->cmd_drawing_scene(command_buffer);
  vk_cmd->cmd_drawing_glyph(command_buffer);
  vk_cmd->cmd_drawing_canvas(command_buffer);
  vk_gui->command_gui(command_buffer);

  //End render pass
  vkCmdEndRenderPass(command_buffer);
  result = vkEndCommandBuffer(command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }

  //---------------------------
}
VkCommandBuffer VK_command::singletime_command_buffer_begin(){
  //---------------------------

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = command_pool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer command_buffer;
  vkAllocateCommandBuffers(vk_param->device.device, &allocInfo, &command_buffer);

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(command_buffer, &beginInfo);

  //---------------------------
  return command_buffer;
}
void VK_command::singletime_command_buffer_end(VkCommandBuffer command_buffer){
  //---------------------------

  vkEndCommandBuffer(command_buffer);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &command_buffer;

  vkQueueSubmit(vk_param->device.queue_graphics, 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(vk_param->device.queue_graphics);

  vkFreeCommandBuffers(vk_param->device.device, command_pool, 1, &command_buffer);

  //---------------------------
}
