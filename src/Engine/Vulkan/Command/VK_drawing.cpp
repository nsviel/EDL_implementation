#include "VK_drawing.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Command/VK_command.h"
#include "../Shader/VK_uniform.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Swapchain/VK_frame.h"
#include "../Rendering/VK_framebuffer.h"
#include "../Instance/VK_window.h"
#include "../Device/VK_device.h"


//Constructor / Destructor
VK_drawing::VK_drawing(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_window = engineManager->get_vk_window();
  this->vk_framebuffer = engineManager->get_vk_framebuffer();
  this->vk_command = engineManager->get_vk_command();
  this->vk_device = engineManager->get_vk_device();
  this->vk_uniform = engineManager->get_vk_uniform();
  this->vk_frame = engineManager->get_vk_image();

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  //---------------------------

  this->draw_swapchain();
  this->draw_command();
  this->draw_queue();
  this->draw_presentation();

  //---------------------------
}

//Subfunction
void VK_drawing::draw_swapchain(){
  Frame_inflight* frame = param_vulkan->swapchain.get_current_frame();
  //---------------------------

  vk_window->check_for_resizing();

  //Waiting for the previous frame
  vkWaitForFences(param_vulkan->device.device, 1, &frame->fence_inflight, VK_TRUE, UINT64_MAX);

  //Acquiring an image from the swap chain
  VkResult result = vkAcquireNextImageKHR(param_vulkan->device.device, param_vulkan->swapchain.swapchain, UINT64_MAX, frame->semaphore_image_available, VK_NULL_HANDLE, &param_vulkan->swapchain.current_image_ID);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  vkResetFences(param_vulkan->device.device, 1, &frame->fence_inflight);

  //If window resized
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  //---------------------------
}
void VK_drawing::draw_command(){
  Frame_inflight* frame = param_vulkan->swapchain.get_current_frame();
  //---------------------------

  vkResetCommandBuffer(frame->command_buffer, 0);
  vk_command->record_command_buffer(frame->command_buffer);

  //---------------------------
}
void VK_drawing::draw_queue(){
  Frame_inflight* frame = param_vulkan->swapchain.get_current_frame();
  //---------------------------

  VkSemaphore semaphore_wait[] = {frame->semaphore_image_available};
  VkSemaphore semaphore_signal[] = {frame->semaphore_render_finished};
  VkPipelineStageFlags stage_wait[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = 1;
  submit_info.pWaitSemaphores = semaphore_wait;
  submit_info.pWaitDstStageMask = stage_wait;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &frame->command_buffer;
  submit_info.signalSemaphoreCount = 1;
  submit_info.pSignalSemaphores = semaphore_signal;

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(param_vulkan->device.queue_graphics, 1, &submit_info, frame->fence_inflight);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}
void VK_drawing::draw_presentation(){
  Frame_inflight* frame = param_vulkan->swapchain.get_current_frame();
  //---------------------------

  VkSemaphore semaphore_signal[] = {frame->semaphore_render_finished};
  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = semaphore_signal;

  VkSwapchainKHR swapChains[] = {param_vulkan->swapchain.swapchain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &param_vulkan->swapchain.current_image_ID;
  presentInfo.pResults = nullptr; // Optional

  VkResult result = vkQueuePresentKHR(param_vulkan->device.queue_presentation, &presentInfo);
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || param_vulkan->window.is_resized){
    vk_swapchain->recreate_swapChain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  param_vulkan->swapchain.current_frame_ID = (param_vulkan->swapchain.current_frame_ID + 1) % param_vulkan->instance.max_frame;

  //---------------------------
}
