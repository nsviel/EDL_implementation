#include "VK_synchronization.h"

#include "../VK_engine.h"
#include "../Param_vulkan.h"
#include "../Device/VK_device.h"


//Constructor / Destructor
VK_synchronization::VK_synchronization(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->param_vulkan = vk_engine->get_param_vulkan();
  this->vk_device = vk_engine->get_vk_device();

  //---------------------------
}
VK_synchronization::~VK_synchronization(){}

//Main function
void VK_synchronization::create_sync_objects(Frame_inflight* frame){
  //---------------------------

  //Semaphore info
  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  //Fence info
  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  //Semaphore and fence creation
  VkResult result_sema_1 = vkCreateSemaphore(param_vulkan->device.device, &semaphoreInfo, nullptr, &frame->semaphore_image_available);
  VkResult result_sema_2 = vkCreateSemaphore(param_vulkan->device.device, &semaphoreInfo, nullptr, &frame->semaphore_render_finished);
  VkResult result_hence = vkCreateFence(param_vulkan->device.device, &fenceInfo, nullptr, &frame->fence_inflight);
  if(result_sema_1 != VK_SUCCESS || result_sema_2 != VK_SUCCESS || result_hence != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphores!");
  }

  //---------------------------
}
void VK_synchronization::clean_sync_obj(Frame_inflight* frame){
  //---------------------------

  vkDestroySemaphore(param_vulkan->device.device, frame->semaphore_render_finished, nullptr);
  vkDestroySemaphore(param_vulkan->device.device, frame->semaphore_image_available, nullptr);
  vkDestroyFence(param_vulkan->device.device, frame->fence_inflight, nullptr);

  //---------------------------
}
