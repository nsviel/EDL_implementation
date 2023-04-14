#include "Engine_vulkan.h"
#include "VK_instance.h"
#include "VK_device.h"
#include "VK_swapchain.h"
#include "VK_renderpass.h"
#include "VK_pipeline.h"
#include "VK_framebuffer.h"
#include "VK_command.h"

#include "../Core/Engine_window.h"
#include "../Core/GUI.h"

#include "../Node_engine.h"

#include <vector>
#include <set>
#include <glm/glm.hpp>
#include <algorithm>
#include <fstream>
#include <cstring>

const int MAX_FRAMES_IN_FLIGHT = 2;
uint32_t currentFrame = 0;


void sayHello(){
  std::cout<<"Hello"<<std::endl;
}


//Constructor / Destructor
Engine_vulkan::Engine_vulkan(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->engine_window = node_engine->get_engine_window();
  this->vk_instance = new VK_instance();
  this->vk_device = new VK_device(this);
  this->vk_swapchain = new VK_swapchain(this);
  this->vk_renderpass = new VK_renderpass(this);
  this->vk_pipeline = new VK_pipeline(this);
  this->vk_framebuffer = new VK_framebuffer(this);
  this->vk_command = new VK_command(this);

  //---------------------------
}
Engine_vulkan::~Engine_vulkan(){}

//Main function
void Engine_vulkan::init_vulkan(){
  //---------------------------

  vk_instance->create_instance();
  this->instance = vk_instance->get_vk_instance();
  this->surface = engine_window->create_window_surface(instance);
  this->physical_device = vk_device->select_physical_device(instance);
  this->device = vk_device->create_logical_device();
  this->queue_graphics = vk_device->get_queue_graphics();
  this->queue_presentation = vk_device->get_queue_presentation();

  vk_swapchain->create_swapChain();
  this->swapChain = vk_swapchain->get_swapChain();
  this->swapChain_image_format = vk_swapchain->get_swapChain_image_format();
  this->swapChain_extent = vk_swapchain->get_swapChain_extent();
  this->swapChain_images = vk_swapchain->get_swapChain_images();
  this->swapChain_image_views = vk_swapchain->get_swapChain_image_views();
  this->swapChain_fbo = vk_swapchain->get_swapChain_fbo();
  vk_swapchain->create_image_views();
  this->swapChain_image_views = vk_swapchain->get_swapChain_image_views();

  vk_renderpass->create_render_pass();
  this->renderPass = vk_renderpass->get_renderPass();


  vk_pipeline->create_graphics_pipeline();
  this->pipelineLayout = vk_pipeline->get_pipelineLayout();
  this->graphicsPipeline = vk_pipeline->get_graphicsPipeline();


  vk_framebuffer->create_framebuffers();
  this->swapChain_fbo = vk_framebuffer->get_swapChain_fbo();


  vk_command->create_command_pool();
  vk_command->create_command_buffers();
  this->commandPool = vk_command->get_commandPool();
  this->commandBuffers = vk_command->get_commandBuffers();


  this->create_sync_objects();

  GUI* guiManager= node_engine->get_guiManager();
  guiManager->init();

  //---------------------------
}
void Engine_vulkan::main_loop() {
  GLFWwindow* window = engine_window->get_window();
  //---------------------------

  GUI* guiManager= node_engine->get_guiManager();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    this->draw_frame();
    guiManager->loop();
  }

  vkDeviceWaitIdle(device);

  //---------------------------
}
void Engine_vulkan::draw_frame(){
  swapChain = this->get_swapChain();
  //---------------------------

  framebufferResized = engine_window->check_for_resizing();

  //Waiting for the previous frame
  vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

  //Acquiring an image from the swap chain
  uint32_t imageIndex;
  VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    this->recreate_swapChain();
    return;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  vkResetFences(device, 1, &inFlightFences[currentFrame]);

  //If window resized
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    this->recreate_swapChain();
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
    this->framebufferResized = false;
    this->recreate_swapChain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

  //---------------------------
}
void Engine_vulkan::clean_vulkan(){
  //---------------------------

  /*if(with_validation_layer){
    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
  }*/
  VkInstance instance = vk_instance->get_vk_instance();

  vk_swapchain->cleanup_swapChain();
  vk_pipeline->cleanup();
  vk_renderpass->cleanup();

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
    vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
    vkDestroyFence(device, inFlightFences[i], nullptr);
  }

  vk_command->cleanup();
  vk_device->cleanup();

  vkDestroySurfaceKHR(instance, surface, nullptr);
  
  vk_instance->cleanup();

  //---------------------------
}

//Subfunction
void Engine_vulkan::create_sync_objects(){
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


//Swap chain settings
void Engine_vulkan::recreate_swapChain(){
  //---------------------------

  vkDeviceWaitIdle(device);

  this->cleanup_swapChain();

  vk_swapchain->create_swapChain();
  vk_swapchain->create_image_views();
  this->swapChain = vk_swapchain->get_swapChain();
  this->swapChain_image_format = vk_swapchain->get_swapChain_image_format();
  this->swapChain_extent = vk_swapchain->get_swapChain_extent();
  this->swapChain_images = vk_swapchain->get_swapChain_images();
  this->swapChain_image_views = vk_swapchain->get_swapChain_image_views();
  this->swapChain_fbo = vk_swapchain->get_swapChain_fbo();
  vk_framebuffer->create_framebuffers();
  this->swapChain_fbo = vk_framebuffer->get_swapChain_fbo();

  //---------------------------
}
void Engine_vulkan::cleanup_swapChain(){
  //---------------------------

  for(size_t i=0; i<swapChain_fbo.size(); i++){
    vkDestroyFramebuffer(device, swapChain_fbo[i], nullptr);
  }

  for(size_t i=0; i<swapChain_image_views.size(); i++){
    vkDestroyImageView(device, swapChain_image_views[i], nullptr);
  }

  vkDestroySwapchainKHR(device, swapChain, nullptr);

  //---------------------------
}
