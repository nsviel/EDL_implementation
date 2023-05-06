#include "VK_synchronization.h"

#include "../VK_parameter.h"
#include "../Engine.h"
#include "../Device/VK_device.h"

#include "../../Node_engine.h"


//Constructor / Destructor
VK_synchronization::VK_synchronization(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->vk_device = engineManager->get_vk_device();

  //---------------------------
}
VK_synchronization::~VK_synchronization(){}

//Main function
void VK_synchronization::create_sync_objects(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  semvec_image_available.resize(MAX_FRAMES_IN_FLIGHT);
  semvec_render_finish.resize(MAX_FRAMES_IN_FLIGHT);
  fenvec_inFlight.resize(MAX_FRAMES_IN_FLIGHT);

  //Semaphore info
  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  //Fence info
  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  //Semaphore and fence creation
 for(size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++){
    VkResult result_sema_1 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &semvec_image_available[i]);
    VkResult result_sema_2 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &semvec_render_finish[i]);
    VkResult result_hence = vkCreateFence(device, &fenceInfo, nullptr, &fenvec_inFlight[i]);
    if(result_sema_1 != VK_SUCCESS || result_sema_2 != VK_SUCCESS || result_hence != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create semaphores!");
    }
  }

  //---------------------------
}
void VK_synchronization::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(device, semvec_render_finish[i], nullptr);
    vkDestroySemaphore(device, semvec_image_available[i], nullptr);
    vkDestroyFence(device, fenvec_inFlight[i], nullptr);
  }

  //---------------------------
}
