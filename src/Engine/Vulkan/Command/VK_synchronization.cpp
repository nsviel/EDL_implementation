#include "VK_synchronization.h"

#include "../Engine.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_image.h"

#include "../../Param_engine.h"


//Constructor / Destructor
VK_synchronization::VK_synchronization(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_engine = engineManager->get_param_engine();
  this->vk_device = engineManager->get_vk_device();
  this->vk_image = engineManager->get_vk_image();

  //---------------------------
}
VK_synchronization::~VK_synchronization(){}

//Main function
void VK_synchronization::create_sync_objects(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  semvec_image_available.resize(param_engine->max_frame);
  semvec_render_finish.resize(param_engine->max_frame);
  fenvec_inFlight.resize(param_engine->max_frame);

  //Semaphore info
  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  //Fence info
  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  //Semaphore and fence creation
  for(size_t i=0; i<param_engine->max_frame; i++){
    VkResult result_sema_1 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &semvec_image_available[i]);
    VkResult result_sema_2 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &semvec_render_finish[i]);
    VkResult result_hence = vkCreateFence(device, &fenceInfo, nullptr, &fenvec_inFlight[i]);
    if(result_sema_1 != VK_SUCCESS || result_sema_2 != VK_SUCCESS || result_hence != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create semaphores!");
    }
  }

  this->fill_vec_frame();

  //---------------------------
}
void VK_synchronization::fill_vec_frame(){
  vector<Frame*> vec_frame = vk_image->get_vec_frame();
  //---------------------------

  for(int i=0; i<vec_frame.size(); i++){
    Frame* frame = vec_frame[i];
    frame->semaphore_image_available = semvec_image_available[i];
    frame->semaphore_render_finished = semvec_render_finish[i];
    frame->fence_inflight = fenvec_inFlight[i];
  }

  //---------------------------
}
void VK_synchronization::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  for(size_t i=0; i<param_engine->max_frame; i++){
    vkDestroySemaphore(device, semvec_render_finish[i], nullptr);
    vkDestroySemaphore(device, semvec_image_available[i], nullptr);
    vkDestroyFence(device, fenvec_inFlight[i], nullptr);
  }

  //---------------------------
}
