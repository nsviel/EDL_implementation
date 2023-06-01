#include "VK_synchronization.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Instance/Device/VK_device.h"


//Constructor / Destructor
VK_synchronization::VK_synchronization(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_device = vk_engine->get_vk_device();

  //---------------------------
}
VK_synchronization::~VK_synchronization(){}

//Main function
void VK_synchronization::create_sync_objects(Frame* frame){
  //---------------------------

  //Semaphore info
  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  //Fence info
  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  //Semaphore and fence creation
  VkResult result_sema_1 = vkCreateSemaphore(vk_param->device.device, &semaphoreInfo, nullptr, &frame->semaphore_image_available);
  VkResult result_sema_2 = vkCreateSemaphore(vk_param->device.device, &semaphoreInfo, nullptr, &frame->semaphore_render_finished);
  VkResult result_hence = vkCreateFence(vk_param->device.device, &fenceInfo, nullptr, &frame->fence);
  if(result_sema_1 != VK_SUCCESS || result_sema_2 != VK_SUCCESS || result_hence != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphores!");
  }

  //---------------------------
}
void VK_synchronization::clean_sync_obj(Frame* frame){
  //---------------------------

  vkDestroySemaphore(vk_param->device.device, frame->semaphore_render_finished, nullptr);
  vkDestroySemaphore(vk_param->device.device, frame->semaphore_image_available, nullptr);
  vkDestroyFence(vk_param->device.device, frame->fence, nullptr);

  //---------------------------
}
