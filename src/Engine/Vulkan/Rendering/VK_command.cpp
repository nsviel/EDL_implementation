#include "VK_command.h"
#include "VK_renderpass.h"
#include "VK_pipeline.h"

#include "../VK_struct.h"
#include "../VK_parameter.h"
#include "../Engine_vulkan.h"

#include "../Model/VK_buffer.h"
#include "../Element/VK_device.h"
#include "../Shader/VK_descriptor.h"

#include "../Swapchain/VK_swapchain.h"
#include "../Swapchain/VK_framebuffer.h"

#include "../../Node_engine.h"


//Constructor / Destructor
VK_command::VK_command(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_device = engine_vulkan->get_vk_device();
  this->vk_swapchain = engine_vulkan->get_vk_swapchain();
  this->vk_renderpass = engine_vulkan->get_vk_renderpass();
  this->vk_pipeline = engine_vulkan->get_vk_pipeline();
  this->vk_buffer = engine_vulkan->get_vk_buffer();
  this->vk_framebuffer = engine_vulkan->get_vk_framebuffer();
  this->vk_descriptor = engine_vulkan->get_vk_descriptor();

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

//Graphics pipeline
void VK_command::record_command_buffer(VkCommandBuffer commandBuffer, uint32_t imageIndex){
  std::vector<VkFramebuffer> swapChain_fbo = vk_framebuffer->get_swapChain_fbo();
  VkExtent2D swapChain_extent = vk_swapchain->get_swapChain_extent();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  VkPipeline graphicsPipeline = vk_pipeline->get_graphicsPipeline();
  VkPipelineLayout pipelineLayout = vk_pipeline->get_pipelineLayout();
  vector<uint32_t> indices = vk_buffer->get_indices();
  //---------------------------

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

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

  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
  clearValues[1].depthStencil = {1.0f, 0};

  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassInfo.pClearValues = clearValues.data();

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

  //Binding the vertex buffer
  std::vector<VkDescriptorSet> descriptorSets = vk_descriptor->get_descriptorSets();
  VkBuffer vertexBuffer = vk_buffer->get_buffer_vertex();
  VkBuffer indexBuffer = vk_buffer->get_buffer_index();

  VkBuffer vertexBuffers[] = {vertexBuffer};
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
  vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);

  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
  vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[currentFrame], 0, nullptr);

  //vkCmdDraw(commandBuffer, static_cast<uint32_t>(vertices.size()), 1, 0, 0);
  vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

  //vkCmdDraw(commandBuffer, 3, 1, 0, 0);
  vkCmdEndRenderPass(commandBuffer);

  result = vkEndCommandBuffer(commandBuffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }

  //---------------------------
}
