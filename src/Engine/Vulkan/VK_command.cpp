#include "VK_command.h"
#include "VK_device.h"
#include "VK_swapchain.h"
#include "VK_renderpass.h"
#include "VK_pipeline.h"
#include "Engine_vulkan.h"

#include "../Node_engine.h"


//Constructor / Destructor
VK_command::VK_command(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_device = engine_vulkan->get_vk_device();
  this->vk_swapchain = engine_vulkan->get_vk_swapchain();
  this->vk_renderpass = engine_vulkan->get_vk_renderpass();
  this->vk_pipeline = engine_vulkan->get_vk_pipeline();

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
  VkResult result = vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create command pool!");
  }

  //---------------------------
}
void VK_command::create_command_buffers(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

  //Command buffer allocation
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = commandPool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

  VkResult result = vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
void VK_command::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyCommandPool(device, commandPool, nullptr);

  //---------------------------
}

//Graphics pipeline
void VK_command::record_command_buffer(VkCommandBuffer commandBuffer, uint32_t imageIndex){
  std::vector<VkFramebuffer> swapChain_fbo = vk_swapchain->get_swapChain_fbo();
  VkExtent2D swapChain_extent = vk_swapchain->get_swapChain_extent();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  VkPipeline graphicsPipeline = vk_pipeline->get_graphicsPipeline();
  //---------------------------

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = 0; // Optional
  beginInfo.pInheritanceInfo = nullptr; // Optional

  VkResult result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //Starting a render pass
  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = renderPass;
  renderPassInfo.framebuffer = swapChain_fbo[imageIndex];
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = swapChain_extent;
  VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
  renderPassInfo.clearValueCount = 1;
  renderPassInfo.pClearValues = &clearColor;

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

  //Dynamic commands
  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = static_cast<float>(swapChain_extent.width);
  viewport.height = static_cast<float>(swapChain_extent.height);
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = swapChain_extent;
  vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

  vkCmdDraw(commandBuffer, 3, 1, 0, 0);
  vkCmdEndRenderPass(commandBuffer);

  result = vkEndCommandBuffer(commandBuffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }


  //---------------------------
}
