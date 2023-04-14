#include "Engine_vulkan.h"
#include "VK_instance.h"
#include "VK_device.h"
#include "VK_swapchain.h"
#include "VK_renderpass.h"
#include "VK_pipeline.h"
#include "VK_framebuffer.h"
#include "VK_command.h"
#include "VK_synchronization.h"
#include "VK_window.h"
#include "VK_drawing.h"

#include "../Core/GUI.h"
#include "../Node_engine.h"

static uint32_t currentFrame = 0;

//Constructor / Destructor
Engine_vulkan::Engine_vulkan(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->vk_window = new VK_window();
  this->vk_instance = new VK_instance();
  this->vk_device = new VK_device(this);
  this->vk_swapchain = new VK_swapchain(this);
  this->vk_renderpass = new VK_renderpass(this);
  this->vk_pipeline = new VK_pipeline(this);
  this->vk_framebuffer = new VK_framebuffer(this);
  this->vk_command = new VK_command(this);
  this->vk_synchronization = new VK_synchronization(this);
  this->vk_drawing = new VK_drawing(this);

  //---------------------------
}
Engine_vulkan::~Engine_vulkan(){}

//Main function
void Engine_vulkan::init_vulkan(){
  //---------------------------

  vk_window->init_window();
  vk_instance->create_instance();
  this->instance = vk_instance->get_vk_instance();
  this->surface = vk_window->create_window_surface(instance);
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


  vk_synchronization->create_sync_objects();
  this->imageAvailableSemaphores = vk_synchronization->get_imageAvailableSemaphores();
  this->renderFinishedSemaphores = vk_synchronization->get_renderFinishedSemaphores();
  this->inFlightFences = vk_synchronization->get_inFlightFences();



  GUI* guiManager= node_engine->get_guiManager();
  guiManager->init();

  //---------------------------
}
void Engine_vulkan::main_loop() {
  GLFWwindow* window = vk_window->get_window();
  //---------------------------

  GUI* guiManager= node_engine->get_guiManager();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    //this->draw_frame();
    vk_drawing->draw_frame();
    guiManager->loop();
  }

  vkDeviceWaitIdle(device);

  //---------------------------
}
void Engine_vulkan::draw_frame(){
  swapChain = vk_swapchain->get_swapChain();
  //---------------------------

  framebufferResized = vk_window->check_for_resizing();

  //Waiting for the previous frame
  vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

  //Acquiring an image from the swap chain
  uint32_t imageIndex;
  VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    this->swapChain = vk_swapchain->get_swapChain();
    this->swapChain_image_format = vk_swapchain->get_swapChain_image_format();
    this->swapChain_extent = vk_swapchain->get_swapChain_extent();
    this->swapChain_images = vk_swapchain->get_swapChain_images();
    this->swapChain_image_views = vk_swapchain->get_swapChain_image_views();
    this->swapChain_fbo = vk_swapchain->get_swapChain_fbo();

    vk_framebuffer->create_framebuffers();
    this->swapChain_fbo = vk_framebuffer->get_swapChain_fbo();
    return;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  vkResetFences(device, 1, &inFlightFences[currentFrame]);

  //If window resized
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    this->swapChain = vk_swapchain->get_swapChain();
    this->swapChain_image_format = vk_swapchain->get_swapChain_image_format();
    this->swapChain_extent = vk_swapchain->get_swapChain_extent();
    this->swapChain_images = vk_swapchain->get_swapChain_images();
    this->swapChain_image_views = vk_swapchain->get_swapChain_image_views();
    this->swapChain_fbo = vk_swapchain->get_swapChain_fbo();

    vk_framebuffer->create_framebuffers();
    this->swapChain_fbo = vk_framebuffer->get_swapChain_fbo();
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
    vk_swapchain->recreate_swapChain();
    this->swapChain = vk_swapchain->get_swapChain();
    this->swapChain_image_format = vk_swapchain->get_swapChain_image_format();
    this->swapChain_extent = vk_swapchain->get_swapChain_extent();
    this->swapChain_images = vk_swapchain->get_swapChain_images();
    this->swapChain_image_views = vk_swapchain->get_swapChain_image_views();
    this->swapChain_fbo = vk_swapchain->get_swapChain_fbo();

    vk_framebuffer->create_framebuffers();
    this->swapChain_fbo = vk_framebuffer->get_swapChain_fbo();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

  //---------------------------
}
void Engine_vulkan::clean_vulkan(){
  //---------------------------

  vk_swapchain->cleanup_swapChain();
  vk_pipeline->cleanup();
  vk_renderpass->cleanup();
  vk_synchronization->cleanup();
  vk_command->cleanup();
  vk_device->cleanup();

  VkInstance instance = vk_instance->get_vk_instance();
  vkDestroySurfaceKHR(instance, surface, nullptr);

  vk_instance->cleanup();

  vk_window->clean_window();

  //---------------------------
}
