#include "VK_uniform.h"

#include "../VK_parameter.h"
#include "../Engine_vulkan.h"
#include "../Data/VK_buffer.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_swapchain.h"


//Constructor / Destructor
VK_uniform::VK_uniform(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->vk_device = engine_vulkan->get_vk_device();
  this->vk_buffer = engine_vulkan->get_vk_buffer();
  this->vk_swapchain = engine_vulkan->get_vk_swapchain();

  //---------------------------
}
VK_uniform::~VK_uniform(){}

//Main function
void VK_uniform::create_uniform_buffers(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkDeviceSize bufferSize = sizeof(UniformBufferObject);

  uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
  uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
  uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

  for(size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++){
    vk_buffer->create_buffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
    vkMapMemory(device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
  }

  //---------------------------
}
void VK_uniform::update_uniform_buffer(uint32_t currentImage){
  VkExtent2D swapChain_extent = vk_swapchain->get_swapChain_extent();
  //---------------------------

  static auto startTime = std::chrono::high_resolution_clock::now();
  auto currentTime = std::chrono::high_resolution_clock::now();
  float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

  UniformBufferObject ubo{};
  ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f) * 0.1f, glm::vec3(0.0f, 0.0f, 1.0f));

  ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

  ubo.proj = glm::perspective(glm::radians(45.0f), swapChain_extent.width / (float) swapChain_extent.height, 0.1f, 10.0f);
  ubo.proj[1][1] *= -1; // Because glm is designed for OpenGL convention

  memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));

  //---------------------------
}
void VK_uniform::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  for(size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++){
    vkDestroyBuffer(device, uniformBuffers[i], nullptr);
    vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
  }

  //---------------------------
}
