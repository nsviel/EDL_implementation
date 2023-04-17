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
  this->vk_instance = new VK_instance();
  this->vk_window = new VK_window(this);
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
  vk_window->create_window_surface();
  vk_device->select_physical_device();
  vk_device->create_logical_device();
  vk_swapchain->create_swapChain();
  vk_swapchain->create_image_views();
  vk_renderpass->create_render_pass();
  vk_pipeline->create_graphics_pipeline();
  vk_framebuffer->create_framebuffers();
  vk_command->create_command_pool();
  vk_command->create_command_buffers();

  vk_synchronization->create_sync_objects();




  GUI* guiManager= node_engine->get_guiManager();
  guiManager->init();

  //---------------------------
}
void Engine_vulkan::main_loop() {
  GLFWwindow* window = vk_window->get_window();
  VkDevice device = vk_device->get_device();
  //---------------------------

  GUI* guiManager= node_engine->get_guiManager();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    vk_drawing->draw_frame();
    guiManager->loop();
  }

  vkDeviceWaitIdle(device);

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
  vk_window->clean_surface();
  vk_instance->cleanup();
  vk_window->clean_window();

  //---------------------------
}
