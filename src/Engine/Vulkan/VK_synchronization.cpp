#include "VK_synchronization.h"
#include "Engine_vulkan.h"

#include "../Node_engine.h"


//Constructor / Destructor
VK_synchronization::VK_synchronization(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;

  //---------------------------
}
VK_synchronization::~VK_synchronization(){}

//Main function
void VK_synchronization::create_sync_objects(){
  VkDevice device = engine_vulkan->get_device();
  //---------------------------

  imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

  //Semaphore info
  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  //Fence info
  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  //Semaphore and fence creation
 for(size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++){
    VkResult result_sema_1 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]);
    VkResult result_sema_2 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]);
    VkResult result_hence = vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]);
    if(result_sema_1 != VK_SUCCESS || result_sema_2 != VK_SUCCESS || result_hence != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create semaphores!");
    }
  }

  //---------------------------
}
void VK_synchronization::cleanup(){
  VkDevice device = engine_vulkan->get_device();
  //---------------------------

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
    vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
    vkDestroyFence(device, inFlightFences[i], nullptr);
  }

  //---------------------------
}
