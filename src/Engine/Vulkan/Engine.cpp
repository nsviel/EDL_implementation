#include "Engine.h"

#include "Pipeline/VK_renderpass.h"
#include "Pipeline/VK_pipeline.h"
#include "Command/VK_command.h"
#include "Command/VK_synchronization.h"
#include "Data/VK_descriptor.h"
#include "Shader/VK_uniform.h"
#include "Data/VK_buffer.h"
#include "Data/VK_texture.h"
#include "Data/VK_data.h"
#include "Instance/VK_instance.h"
#include "Command/VK_drawing.h"
#include "Device/VK_device.h"
#include "Instance/VK_window.h"
#include "Instance/VK_gui.h"
#include "Swapchain/VK_framebuffer.h"
#include "Swapchain/VK_depth.h"
#include "Swapchain/VK_swapchain.h"
#include "Camera/VK_viewport.h"
#include "Camera/VK_camera.h"

#include "../Node_engine.h"
#include "../Param_engine.h"

#include "../GPU/GPU_data.h"


//Constructor / Destructor
Engine::Engine(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->param_engine = node_engine->get_param_engine();
  this->vk_instance = new VK_instance();
  this->vk_viewport = new VK_viewport(this);
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
  this->vk_camera = new VK_camera(this);
  this->vk_uniform = new VK_uniform(this);
  this->vk_drawing = new VK_drawing(this);
  this->vk_texture = new VK_texture(this);
  this->vk_data = new VK_data(this);
  this->vk_depth = new VK_depth(this);
  this->vk_gui = new VK_gui(this);

  //---------------------------
}
Engine::~Engine(){}

//Main function
void Engine::init_vulkan(){
  //---------------------------

  //Instance
  vk_window->init_window();
  vk_instance->init_instance();
  vk_window->create_window_surface();

  //Device
  vk_device->init_device();

  //Pipeline / swap chain
  vk_swapchain->init_swapchain();
  vk_renderpass->create_render_pass();
  vk_descriptor->create_descriptor_set_layout();
  vk_pipeline->create_graphics_pipeline();
  vk_command->create_command_pool();
  vk_depth->create_depth_resources();
  vk_framebuffer->create_framebuffers();

  //Shader
  vk_uniform->create_uniform_buffers();
  vk_descriptor->create_descriptor_pool();

  //Command
  vk_command->create_command_buffers();
  vk_synchronization->create_sync_objects();
  vk_gui->init_gui();

  //---------------------------
}
void Engine::main_loop() {
  GLFWwindow* window = vk_window->get_window();
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Model centered
  Object* object = vk_data->load_model();
  //vk_descriptor->create_descriptor_set();
  GPU_data* gpu_data = node_engine->get_gpu_data();
  gpu_data->insert_object_for_drawing(object);

  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();
    vk_gui->loop_start();
    node_engine->loop();
    vk_gui->loop_end();
    vk_drawing->draw_frame();
  }

  vkDeviceWaitIdle(device);

  //---------------------------
}
void Engine::clean_vulkan(){
  //---------------------------

  vk_gui->cleanup();
  vk_depth->cleanup();
  vk_framebuffer->cleanup();
  vk_swapchain->cleanup();
  vk_pipeline->cleanup();
  vk_renderpass->cleanup();

  vk_uniform->cleanup();
  vk_texture->cleanup();
  vk_descriptor->cleanup();
  vk_synchronization->cleanup();

  vk_command->cleanup();
  vk_device->cleanup();
  vk_window->clean_surface();
  vk_instance->cleanup();
  vk_window->clean_window();

  //---------------------------
}
