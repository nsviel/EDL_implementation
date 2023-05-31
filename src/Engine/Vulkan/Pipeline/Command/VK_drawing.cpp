#include "VK_drawing.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Pipeline/Command/VK_command.h"
#include "../../Presentation/Swapchain/VK_swapchain.h"
#include "../../Instance/Element/VK_window.h"


//Constructor / Destructor
VK_drawing::VK_drawing(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_swapchain = vk_engine->get_vk_swapchain();
  this->vk_window = vk_engine->get_vk_window();
  this->vk_command = vk_engine->get_vk_command();

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
  Frame_inflight* frame = vk_param->swapchain.get_current_frame_inflight();
  //---------------------------

  //Waiting for the previous frame
  vkWaitForFences(vk_param->device.device, 1, &frame->fence_inflight, VK_TRUE, UINT64_MAX);

  //Acquiring an image from the swap chain
  VkResult result = vkAcquireNextImageKHR(vk_param->device.device, vk_param->swapchain.swapchain, UINT64_MAX, frame->semaphore_image_available, VK_NULL_HANDLE, &vk_param->swapchain.current_frame_swapchain_ID);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  //Reset fence
  vkResetFences(vk_param->device.device, 1, &frame->fence_inflight);

  //Window resizing
  vk_window->check_for_resizing();
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  //---------------------------
}
void VK_drawing::draw_command(){
  Frame_inflight* frame = vk_param->swapchain.get_current_frame_inflight();
  //---------------------------


    vkResetCommandBuffer(frame->command_buffer, 0);
    vk_command->record_command_buffer(frame->command_buffer);



  //---------------------------
}
void VK_drawing::draw_queue(){
  Frame_inflight* frame = vk_param->swapchain.get_current_frame_inflight();
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
  VkResult result = vkQueueSubmit(vk_param->device.queue_graphics, 1, &submit_info, frame->fence_inflight);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}
void VK_drawing::draw_presentation(){
  Frame_inflight* frame = vk_param->swapchain.get_current_frame_inflight();
  //---------------------------

  VkSemaphore semaphore_signal[] = {frame->semaphore_render_finished};
  VkSwapchainKHR swapChains[] = {vk_param->swapchain.swapchain};
  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = semaphore_signal;
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &vk_param->swapchain.current_frame_swapchain_ID;
  presentInfo.pResults = nullptr; // Optional

  VkResult result = vkQueuePresentKHR(vk_param->device.queue_presentation, &presentInfo);
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || vk_param->window.is_resized){
    vk_swapchain->recreate_swapChain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  vk_param->swapchain.current_frame_inflight_ID = (vk_param->swapchain.current_frame_inflight_ID + 1) % vk_param->instance.max_frame;

  //---------------------------
}
