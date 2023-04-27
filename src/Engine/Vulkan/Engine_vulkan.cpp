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
#include "VK_buffer.h"
#include "VK_descriptor.h"
#include "VK_uniform.h"
#include "VK_texture.h"
#include "VK_depth.h"

#include "../../Load/Loader.h"

#include "../Core/GUI.h"
#include "../Node_engine.h"



//Constructor / Destructor
Engine_vulkan::Engine_vulkan(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->vk_instance = new VK_instance();
  this->vk_window = new VK_window(this);
  this->vk_device = new VK_device(this);
  this->vk_swapchain = new VK_swapchain(this);
  this->vk_renderpass = new VK_renderpass(this);
  this->vk_descriptor = new VK_descriptor(this);
  this->vk_pipeline = new VK_pipeline(this);
  this->vk_framebuffer = new VK_framebuffer(this);
  this->vk_buffer = new VK_buffer(this);
  this->vk_command = new VK_command(this);
  this->vk_synchronization = new VK_synchronization(this);
  this->vk_uniform = new VK_uniform(this);
  this->vk_drawing = new VK_drawing(this);
  this->vk_texture = new VK_texture(this);
  this->vk_depth = new VK_depth(this);

  //---------------------------
}
Engine_vulkan::~Engine_vulkan(){}

//Main function
void Engine_vulkan::init_vulkan(){
  //---------------------------
/*
  Loader loaderManager;
  Cloud* cloud = loaderManager.load_cloud("/home/aeter/Desktop/Point_cloud/ply/bun_zipper.ply");
  say("Bunny loaded !");

  const std::vector<Vertex> vertices = {
      {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
      {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
      {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
      {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
  };

  for(int i=0; i<cloud->xyz.size(); i++){
    Vertex vertex;
    vertex.pos =
  }*/


  vk_window->init_window();
  vk_instance->create_instance();
  vk_instance->create_validationLayer();
  vk_window->create_window_surface();
  vk_device->select_physical_device();
  vk_device->create_logical_device();
  vk_swapchain->create_swapChain();
  vk_swapchain->create_image_views();
  vk_renderpass->create_render_pass();
  vk_descriptor->create_descriptorSet_layout();
  vk_pipeline->create_graphics_pipeline();
  vk_command->create_command_pool();
  vk_depth->create_depth_resources();
  vk_framebuffer->create_framebuffers();
  vk_texture->create_texture_image();
  vk_texture->create_texture_image_view();
  vk_texture->create_texture_sampler();
  vk_buffer->load_model();
  vk_buffer->create_vertex_buffer();
  vk_buffer->create_index_buffer();
  vk_uniform->create_uniform_buffers();
  vk_descriptor->create_descriptor_pool();
  vk_descriptor->create_descriptor_sets();
  vk_command->create_command_buffers();
  vk_synchronization->create_sync_objects();

  //---------------------------
}
void Engine_vulkan::main_loop() {
  GLFWwindow* window = vk_window->get_window();
  VkDevice device = vk_device->get_device();
  //---------------------------

  GUI* guiManager= node_engine->get_guiManager();

  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    guiManager->loop();
    vk_drawing->draw_frame();
  }

  vkDeviceWaitIdle(device);

  //---------------------------
}
void Engine_vulkan::clean_vulkan(){
  //---------------------------

  vk_depth->cleanup();
  vk_framebuffer->cleanup();
  vk_swapchain->cleanup_swapChain();
  vk_pipeline->cleanup();
  vk_renderpass->cleanup();
  vk_uniform->cleanup();

  vk_descriptor->cleanup_pool();
  vk_texture->cleanup();
  vk_descriptor->cleanup_layout();
  vk_buffer->cleanup();

  vk_synchronization->cleanup();
  vk_command->cleanup();
  vk_device->cleanup();
  vk_window->clean_surface();
  vk_instance->cleanup();
  vk_window->clean_window();

  //---------------------------
}
