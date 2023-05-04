#include "VK_command.h"

#include "../Instance/VK_gui.h"
#include "../Instance/VK_window.h"
#include "../Pipeline/VK_renderpass.h"
#include "../Pipeline/VK_pipeline.h"
#include "../VK_struct.h"
#include "../VK_parameter.h"
#include "../Engine_vulkan.h"
#include "../Device/VK_device.h"
#include "../Data/VK_descriptor.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Swapchain/VK_framebuffer.h"
#include "../Camera/VK_viewport.h"


//Constructor / Destructor
VK_command::VK_command(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_device = engine_vulkan->get_vk_device();
  this->vk_swapchain = engine_vulkan->get_vk_swapchain();
  this->vk_renderpass = engine_vulkan->get_vk_renderpass();
  this->vk_pipeline = engine_vulkan->get_vk_pipeline();
  this->vk_framebuffer = engine_vulkan->get_vk_framebuffer();
  this->vk_descriptor = engine_vulkan->get_vk_descriptor();
  this->vk_viewport = engine_vulkan->get_vk_viewport();
  this->vk_window = engine_vulkan->get_vk_window();

  //---------------------------
}
VK_command::~VK_command(){}

//Main function
void VK_command::create_command_pool(){
  VkPhysicalDevice physical_device = vk_device->get_physical_device();
  VkDevice device = vk_device->get_device();
  //---------------------------

  struct_queueFamily_indices queueFamily_indices = vk_device->find_queue_families(physical_device);

  //Command pool info
  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = queueFamily_indices.family_graphics.value();

  //Command pool creation
  VkResult result = vkCreateCommandPool(device, &poolInfo, nullptr, &command_pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create command pool!");
  }

  //---------------------------
}
void VK_command::create_command_buffers(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //One command buffer per frame
  command_buffer_vec.resize(MAX_FRAMES_IN_FLIGHT);

  //Command buffer allocation
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = command_pool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t) command_buffer_vec.size();

  VkResult result = vkAllocateCommandBuffers(device, &allocInfo, command_buffer_vec.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
void VK_command::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyCommandPool(device, command_pool, nullptr);

  //---------------------------
}

//Command functions
void VK_command::record_command_buffer(Cloud* cloud, VkCommandBuffer command_buffer, uint32_t imageIndex){
  std::vector<VkFramebuffer> swapChain_fbo = vk_framebuffer->get_swapChain_fbo();
  VkExtent2D swapchain_extent = vk_swapchain->get_swapChain_extent();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  //---------------------------

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

  VkResult result = vkBeginCommandBuffer(command_buffer, &beginInfo);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //Starting a render pass
  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
  clearValues[1].depthStencil = {1.0f, 0};

  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = renderPass;
  renderPassInfo.framebuffer = swapChain_fbo[imageIndex];
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = swapchain_extent;
  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassInfo.pClearValues = clearValues.data();

  //start render pass
  vkCmdBeginRenderPass(command_buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

  this->command_viewport(command_buffer);
  this->command_pipeline(command_buffer);
  this->command_drawing(cloud, command_buffer);

  //ICI command pour draw gui
  VK_gui* vk_gui = engine_vulkan->get_vk_gui();
  vk_gui->command_gui(command_buffer);

  //End render pass
  vkCmdEndRenderPass(command_buffer);
  result = vkEndCommandBuffer(command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }

  //---------------------------
}
void VK_command::command_viewport(VkCommandBuffer command_buffer){
  VkExtent2D swapchain_extent = vk_swapchain->get_swapChain_extent();
  //---------------------------

  vk_viewport->update_viewport(swapchain_extent);

  VkViewport viewport = vk_viewport->get_viewport();
  VkRect2D scissor = vk_viewport->get_scissor();

  vkCmdSetViewport(command_buffer, 0, 1, &viewport);
  vkCmdSetScissor(command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_command::command_pipeline(VkCommandBuffer command_buffer){
  VkPipeline graphicsPipeline = vk_pipeline->get_graphicsPipeline();
  VkPipelineLayout pipelineLayout = vk_pipeline->get_pipelineLayout();
  //---------------------------

  std::vector<VkDescriptorSet> descriptorSets = vk_descriptor->get_descriptorSets();
  vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
  vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[currentFrame], 0, nullptr);

  //---------------------------
}
void VK_command::command_drawing(Cloud* cloud, VkCommandBuffer command_buffer){
  //---------------------------

  VkBuffer vertexBuffers[] = {cloud->vbo_xyz, cloud->vbo_rgb, cloud->vbo_uv};
  VkDeviceSize offsets[] = {0, 0, 0};
  vkCmdBindVertexBuffers(command_buffer, 0, 3, vertexBuffers, offsets);
  vkCmdDraw(command_buffer, cloud->xyz.size(), 1, 0, 0);

  //---------------------------
}

//One time command
VkCommandBuffer VK_command::command_buffer_begin(){
  VK_command* vk_command = engine_vulkan->get_vk_command();
  VkCommandPool commandPool = vk_command->get_command_pool();
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = commandPool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer command_buffer;
  vkAllocateCommandBuffers(device, &allocInfo, &command_buffer);

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(command_buffer, &beginInfo);

  //---------------------------
  return command_buffer;
}
void VK_command::command_buffer_end(VkCommandBuffer command_buffer){
  VK_command* vk_command = engine_vulkan->get_vk_command();
  VkCommandPool commandPool = vk_command->get_command_pool();
  VkDevice device = vk_device->get_device();
  VkQueue queue_graphics = vk_device->get_queue_graphics();
  //---------------------------

  vkEndCommandBuffer(command_buffer);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &command_buffer;

  vkQueueSubmit(queue_graphics, 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(queue_graphics);

  vkFreeCommandBuffers(device, commandPool, 1, &command_buffer);

  //---------------------------
}
