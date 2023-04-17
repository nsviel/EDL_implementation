#include "VK_drawing.h"
#include "Engine_vulkan.h"
#include "VK_window.h"
#include "VK_swapchain.h"
#include "VK_synchronization.h"
#include "VK_framebuffer.h"
#include "VK_command.h"
#include "VK_device.h"
#include "VK_struct.h"

#include "../Node_engine.h"

static uint32_t currentFrame = 0;


//Constructor / Destructor
VK_drawing::VK_drawing(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_swapchain = engine_vulkan->get_vk_swapchain();
  this->vk_window = engine_vulkan->get_vk_window();
  this->vk_framebuffer = engine_vulkan->get_vk_framebuffer();
  this->vk_synchronization = engine_vulkan->get_vk_synchronization();
  this->vk_command = engine_vulkan->get_vk_command();
  this->vk_device = engine_vulkan->get_vk_device();

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  VkSwapchainKHR swapChain = vk_swapchain->get_swapChain();
  VkDevice device = vk_device->get_device();
  std::vector<VkFence> inFlightFences = vk_synchronization->get_inFlightFences();
  std::vector<VkSemaphore> imageAvailableSemaphores = vk_synchronization->get_imageAvailableSemaphores();
  std::vector<VkSemaphore> renderFinishedSemaphores = vk_synchronization->get_renderFinishedSemaphores();
  std::vector<VkCommandBuffer> commandBuffers = vk_command->get_commandBuffers();
  VkQueue queue_graphics = vk_device->get_queue_graphics();
  VkQueue queue_presentation = vk_device->get_queue_presentation();
  //---------------------------

  bool framebufferResized = vk_window->check_for_resizing();

  //Waiting for the previous frame
  vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

  //Acquiring an image from the swap chain
  uint32_t imageIndex;
  VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    vk_framebuffer->create_framebuffers();
    return;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  vkResetFences(device, 1, &inFlightFences[currentFrame]);

  //If window resized
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    vk_framebuffer->create_framebuffers();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  vkResetCommandBuffer(commandBuffers[currentFrame], 0);
  vk_command->record_command_buffer(commandBuffers[currentFrame], imageIndex);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffers[currentFrame];
  VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  result = vkQueueSubmit(queue_graphics, 1, &submitInfo, inFlightFences[currentFrame]);
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
    vk_framebuffer->create_framebuffers();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

  //---------------------------
}
