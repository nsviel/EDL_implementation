#include "VK_synchronization.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Device/VK_device.h"


//Constructor / Destructor
VK_synchronization::VK_synchronization(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();

  //---------------------------
}
VK_synchronization::~VK_synchronization(){}

//Main function
void VK_synchronization::create_sync_objects(Frame* frame){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Semaphore info
  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  //Fence info
  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  //Semaphore and fence creation
  VkResult result_sema_1 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &frame->semaphore_image_available);
  VkResult result_sema_2 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &frame->semaphore_render_finished);
  VkResult result_hence = vkCreateFence(device, &fenceInfo, nullptr, &frame->fence_inflight);
  if(result_sema_1 != VK_SUCCESS || result_sema_2 != VK_SUCCESS || result_hence != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphores!");
  }

  //---------------------------
}
void VK_synchronization::clean_sync_obj(Frame* frame){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroySemaphore(device, frame->semaphore_render_finished, nullptr);
  vkDestroySemaphore(device, frame->semaphore_image_available, nullptr);
  vkDestroyFence(device, frame->fence_inflight, nullptr);

  //---------------------------
}
