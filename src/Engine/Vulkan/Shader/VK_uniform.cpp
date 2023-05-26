#include "VK_uniform.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Data/VK_buffer.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Camera/VK_camera.h"


//Constructor / Destructor
VK_uniform::VK_uniform(Engine* engineManager){
  //---------------------------

  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_buffer = engineManager->get_vk_buffer();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_camera = engineManager->get_vk_camera();

  //---------------------------
}
VK_uniform::~VK_uniform(){}

//Main function
void VK_uniform::create_uniform_buffers(Struct_pipeline* pipeline){
  //---------------------------

  vk_buffer->create_gpu_buffer(sizeof(MVP), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, pipeline->uniform.buffer);
  vk_buffer->bind_buffer_memory(MEMORY_CPU_VISIBLE_GPU, pipeline->uniform.buffer, pipeline->uniform.mem);
  vkMapMemory(param_vulkan->device, pipeline->uniform.mem, 0, sizeof(MVP), 0, &pipeline->uniform.mapped);

  //---------------------------
}
void VK_uniform::update_uniform_buffer(Struct_pipeline* pipeline, MVP& mvp){
  //---------------------------

  memcpy(pipeline->uniform.mapped, &mvp, sizeof(mvp));

  //---------------------------
}
void VK_uniform::clean_uniform(Struct_pipeline* pipeline){
  //---------------------------

  vkDestroyBuffer(param_vulkan->device, pipeline->uniform.buffer, nullptr);
  vkFreeMemory(param_vulkan->device, pipeline->uniform.mem, nullptr);

  //---------------------------
}
