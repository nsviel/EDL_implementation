#include "VK_drawing.h"

#include "../Command/VK_synchronization.h"
#include "../Command/VK_command.h"
#include "../Shader/VK_uniform.h"
#include "../Engine.h"

#include "../Swapchain/VK_swapchain.h"
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
  this->vk_synchronization = engineManager->get_vk_synchronization();
  this->vk_command = engineManager->get_vk_command();
  this->vk_device = engineManager->get_vk_device();
  this->vk_uniform = engineManager->get_vk_uniform();

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
  std::vector<VkFence> inFlightFences = vk_synchronization->get_fenvec_inFlight();
  std::vector<VkSemaphore> semvec_image_available = vk_synchronization->get_semvec_image_available();
  VkDevice device = vk_device->get_device();
  VkSwapchainKHR swapChain = vk_swapchain->get_swapChain();
  //---------------------------

  framebufferResized = vk_window->check_for_resizing();

  //Waiting for the previous frame
  vkWaitForFences(device, 1, &inFlightFences[current_frame], VK_TRUE, UINT64_MAX);

  //Acquiring an image from the swap chain
  VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, semvec_image_available[current_frame], VK_NULL_HANDLE, &imageIndex);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  vkResetFences(device, 1, &inFlightFences[current_frame]);

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
  std::vector<VkCommandBuffer> command_buffer_vec = vk_command->get_command_buffer_vec();
  //---------------------------

  vkResetCommandBuffer(command_buffer_vec[current_frame], 0);
  vk_command->record_command_buffer(command_buffer_vec[current_frame], imageIndex, current_frame);

  //---------------------------
}
void VK_drawing::draw_queue(){
  std::vector<VkFence> inFlightFences = vk_synchronization->get_fenvec_inFlight();
  std::vector<VkSemaphore> semvec_image_available = vk_synchronization->get_semvec_image_available();
  std::vector<VkSemaphore> renderFinishedSemaphores = vk_synchronization->get_semvec_render_finish();
  std::vector<VkCommandBuffer> command_buffer_vec = vk_command->get_command_buffer_vec();
  VkQueue queue_graphics = vk_device->get_queue_graphics();
  VkQueue queue_presentation = vk_device->get_queue_presentation();
  VkSwapchainKHR swapChain = vk_swapchain->get_swapChain();
  //---------------------------

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  VkSemaphore waitSemaphores[] = {semvec_image_available[current_frame]};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &command_buffer_vec[current_frame];
  VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[current_frame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  VkResult result = vkQueueSubmit(queue_graphics, 1, &submitInfo, inFlightFences[current_frame]);
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

  current_frame = (current_frame + 1) % param_engine->MAX_FRAMES_IN_FLIGHT;

  //---------------------------
}
