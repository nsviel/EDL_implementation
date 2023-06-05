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
void VK_synchronization::init_frame_sync(Frame* frame){
  //---------------------------

  this->create_semaphore(frame->semaphore_presentation);
  this->create_semaphore(frame->semaphore_drawing);
  this->create_semaphore(frame->semaphore_scene);
  this->create_fence(frame->fence);

  //---------------------------
}
void VK_synchronization::clean_frame_sync(Frame* frame){
  //---------------------------

  this->clean_semaphore(frame->semaphore_presentation);
  this->clean_semaphore(frame->semaphore_drawing);
  this->clean_semaphore(frame->semaphore_scene);
  this->clean_fence(frame->fence);

  //---------------------------
}

//Synchronization object
void VK_synchronization::create_semaphore(VkSemaphore& semaphore){
  //---------------------------

  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkResult result = vkCreateSemaphore(vk_param->device.device, &semaphoreInfo, nullptr, &semaphore);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create semaphores!");
  }

  //---------------------------
}
void VK_synchronization::create_fence(VkFence& fence){
  //---------------------------

  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  VkResult result = vkCreateFence(vk_param->device.device, &fenceInfo, nullptr, &fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create fence!");
  }

  //---------------------------
}

//Deletetion function
void VK_synchronization::clean_semaphore(VkSemaphore& semaphore){
  //---------------------------

  vkDestroySemaphore(vk_param->device.device, semaphore, nullptr);

  //---------------------------
}
void VK_synchronization::clean_fence(VkFence& fence){
  //---------------------------

  vkDestroyFence(vk_param->device.device, fence, nullptr);

  //---------------------------
}
