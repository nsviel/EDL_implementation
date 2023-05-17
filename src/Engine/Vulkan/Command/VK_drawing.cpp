#include "VK_drawing.h"

#include "../Command/VK_command.h"
#include "../Shader/VK_uniform.h"
#include "../Engine.h"

#include "../Swapchain/VK_swapchain.h"
#include "../Swapchain/VK_image.h"
#include "../Rendering/VK_framebuffer.h"

#include "../Instance/VK_window.h"
#include "../Device/VK_device.h"

#include "../../Node_engine.h"
#include "../../Param_engine.h"


//Constructor / Destructor
VK_drawing::VK_drawing(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_engine = engineManager->get_param_engine();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_window = engineManager->get_vk_window();
  this->vk_framebuffer = engineManager->get_vk_framebuffer();
  this->vk_command = engineManager->get_vk_command();
  this->vk_device = engineManager->get_vk_device();
  this->vk_uniform = engineManager->get_vk_uniform();
  this->vk_image = engineManager->get_vk_image();

  this->current_frame = 0;

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  //---------------------------

  this->draw_swapchain();
  this->draw_command();
  this->draw_queue();

  //---------------------------
}
void VK_drawing::draw_swapchain(){
  VkDevice device = vk_device->get_device();
  VkSwapchainKHR swapChain = vk_swapchain->get_swapChain();
  //---------------------------

  vector<Frame*> vec_frame = vk_image->get_vec_frame();
  Frame* frame = vec_frame[current_frame];

  framebufferResized = vk_window->check_for_resizing();

  //Waiting for the previous frame
  vkWaitForFences(device, 1, &frame->fence_inflight, VK_TRUE, UINT64_MAX);

  //Acquiring an image from the swap chain
  VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, frame->semaphore_image_available, VK_NULL_HANDLE, &imageIndex);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  vkResetFences(device, 1, &frame->fence_inflight);

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
  vector<Frame*> vec_frame = vk_image->get_vec_frame();
  Frame* frame = vec_frame[current_frame];
  //---------------------------

  vkResetCommandBuffer(frame->command_buffer, 0);
  vk_command->record_command_buffer(frame->command_buffer, imageIndex, current_frame);

  //---------------------------
}
void VK_drawing::draw_queue(){
  VkQueue queue_graphics = vk_device->get_queue_graphics();
  VkQueue queue_presentation = vk_device->get_queue_presentation();
  VkSwapchainKHR swapChain = vk_swapchain->get_swapChain();
  //---------------------------

  vector<Frame*> vec_frame = vk_image->get_vec_frame();
  Frame* frame = vec_frame[current_frame];

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  VkSemaphore waitSemaphores[] = {frame->semaphore_image_available};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &frame->command_buffer;
  VkSemaphore signalSemaphores[] = {frame->semaphore_render_finished};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  VkResult result = vkQueueSubmit(queue_graphics, 1, &submitInfo, frame->fence_inflight);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;

  VkSwapchainKHR swapChains[] = {swapChain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &imageIndex;
  presentInfo.pResults = nullptr; // Optional

  result = vkQueuePresentKHR(queue_presentation, &presentInfo);
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized){
    vk_swapchain->recreate_swapChain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  current_frame = (current_frame + 1) % param_engine->max_frame;

  //---------------------------
}
