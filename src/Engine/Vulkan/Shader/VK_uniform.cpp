#include "VK_uniform.h"

#include "../Engine.h"
#include "../Data/VK_buffer.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Camera/VK_camera.h"

#include "../../Param_engine.h"


//Constructor / Destructor
VK_uniform::VK_uniform(Engine* engineManager){
  //---------------------------

  this->param_engine = engineManager->get_param_engine();
  this->vk_device = engineManager->get_vk_device();
  this->vk_buffer = engineManager->get_vk_buffer();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_camera = engineManager->get_vk_camera();

  //---------------------------
}
VK_uniform::~VK_uniform(){}

//Main function
void VK_uniform::create_uniform_buffers(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Resize ubo vectors
  VkDeviceSize bufferSize = sizeof(MVP);
  uniform_buffer.resize(param_engine->max_frame_inflight);
  uniform_buffer_memory.resize(param_engine->max_frame_inflight);
  uniform_buffer_mapped.resize(param_engine->max_frame_inflight);

  //Create a buffer to hold the UBO data per frame
  for(size_t i=0; i<param_engine->max_frame_inflight; i++){
    vk_buffer->create_buffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform_buffer[i]);
    vk_buffer->bind_buffer_memory(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniform_buffer[i], uniform_buffer_memory[i]);
    vkMapMemory(device, uniform_buffer_memory[i], 0, bufferSize, 0, &uniform_buffer_mapped[i]);
  }

  //---------------------------
}
void VK_uniform::update_uniform_buffer(uint32_t currentImage, MVP& mvp){
  VkExtent2D swapchain_extent = vk_swapchain->get_extent();
  //---------------------------

  memcpy(uniform_buffer_mapped[currentImage], &mvp, sizeof(mvp));

  //---------------------------
}
void VK_uniform::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  for(size_t i=0; i<param_engine->max_frame_inflight; i++){
    vkDestroyBuffer(device, uniform_buffer[i], nullptr);
    vkFreeMemory(device, uniform_buffer_memory[i], nullptr);
  }

  //---------------------------
}
