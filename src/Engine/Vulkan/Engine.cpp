#include "Engine.h"

#include "Param_vulkan.h"
#include "Pipeline/VK_renderpass.h"
#include "Pipeline/VK_pipeline.h"
#include "Command/VK_command.h"
#include "Command/VK_synchronization.h"
#include "Shader/VK_descriptor.h"
#include "Shader/VK_uniform.h"
#include "Shader/VK_shader.h"
#include "Data/VK_buffer.h"
#include "Data/VK_texture.h"
#include "Data/VK_data.h"
#include "Command/VK_drawing.h"
#include "Device/VK_device.h"
#include "Device/VK_physical_device.h"
#include "Instance/VK_window.h"
#include "Instance/VK_gui.h"
#include "Instance/VK_instance.h"
#include "Instance/VK_validation.h"
#include "Rendering/VK_framebuffer.h"
#include "Rendering/VK_canvas.h"
#include "Attachment/VK_depth.h"
#include "Attachment/VK_color.h"
#include "Swapchain/VK_swapchain.h"
#include "Swapchain/VK_frame.h"
#include "Camera/VK_viewport.h"
#include "Camera/VK_camera.h"

#include "../Node_engine.h"
#include "../Param_engine.h"


//Constructor / Destructor
Engine::Engine(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->param_engine = node_engine->get_param_engine();

  this->param_vulkan = new Param_vulkan();
  this->vk_instance = new VK_instance(this);
  this->vk_validation = new VK_validation(this);
  this->vk_viewport = new VK_viewport(this);
  this->vk_window = new VK_window(this);
  this->vk_physical_device = new VK_physical_device(this);
  this->vk_device = new VK_device(this);
  this->vk_buffer = new VK_buffer(this);
  this->vk_texture = new VK_texture(this);
  this->vk_depth = new VK_depth(this);
  this->vk_color = new VK_color(this);
  this->vk_data = new VK_data(this);
  this->vk_synchronization = new VK_synchronization(this);
  this->vk_swapchain = new VK_swapchain(this);
  this->vk_renderpass = new VK_renderpass(this);
  this->vk_framebuffer = new VK_framebuffer(this);
  this->vk_frame = new VK_frame(this);
  this->vk_descriptor = new VK_descriptor(this);
  this->vk_shader = new VK_shader(this);
  this->vk_uniform = new VK_uniform(this);
  this->vk_pipeline = new VK_pipeline(this);
  this->vk_camera = new VK_camera(this);
  this->vk_canvas = new VK_canvas(this);
  this->vk_command = new VK_command(this);
  this->vk_drawing = new VK_drawing(this);
  this->vk_gui = new VK_gui(this);

  //---------------------------
}
Engine::~Engine(){}

//Main function
void Engine::init_vulkan(){
  //---------------------------

  //Instance
  vk_window->init_window();
  vk_instance->create_instance();
  vk_validation->create_validation_layer();
  vk_window->create_window_surface();
  vk_physical_device->init_device();
  vk_device->create_logical_device();
  vk_command->create_command_pool();
  vk_descriptor->create_descriptor_pool();

  //Pipeline
  vk_swapchain->create_swapchain();
  vk_renderpass->init_renderpass();
  vk_frame->init_image();
  vk_pipeline->init_pipeline();



  // généraliser les uniform / pishconstant
  //configurer les descripteurs en fonction des uniform  et non pas les configurer en parfallèle
    //-creation des uniform selon ceux demandé par le pipeline
    //-creation des descriptor layout en fonction des uniform
    //-Allocation des descripteur set lorsque tous les pipeline sont terminés

  //Specific
  vk_canvas->create_canvas();
  vk_gui->init_gui();

  //---------------------------
}
void Engine::main_loop() {
  GLFWwindow* window = vk_window->get_window();
  //---------------------------

  auto start_time = std::chrono::steady_clock::now();
  while(!glfwWindowShouldClose(window)){
    auto start = std::chrono::steady_clock::now();
    glfwPollEvents();
    vk_gui->loop_start();
    node_engine->loop();
    vk_gui->loop_end();
    vk_drawing->draw_frame();
    this->fps_control(start);
    this->fps_calcul(start_time);
  }

  vkDeviceWaitIdle(param_vulkan->device.device);

  //---------------------------
}
void Engine::clean_vulkan(){
  //---------------------------

  vk_gui->cleanup();
  vk_frame->cleanup();
  vk_swapchain->clean_swapchain();
  vk_pipeline->cleanup();
  vk_renderpass->cleanup();
  vk_canvas->cleanup();

  vk_data->cleanup();
  vk_descriptor->cleanup();

  vk_command->cleanup();
  vk_device->cleanup();
  vk_window->clean_surface();
  vk_validation->cleanup();
  vk_instance->cleanup();
  vk_window->clean_window();

  //---------------------------
}
void Engine::fps_control(const std::chrono::time_point<std::chrono::steady_clock>& start){
  //---------------------------

  int fps_max = param_engine->max_fps;

  auto end = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

  // Calculate the time to sleep to achieve the desired FPS
  auto time_to_sleep = (1000000 / fps_max) - elapsed;

  if(time_to_sleep > 0){
    std::this_thread::sleep_for(std::chrono::microseconds(time_to_sleep));
  }

  //---------------------------
}
void Engine::fps_calcul(std::chrono::steady_clock::time_point& start_time){
  //---------------------------

  static int num_frames = 0;
  num_frames++;

  if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count() >= 1000){
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    this->fps = num_frames / (elapsed_time / 1000000.0);
    num_frames = 0;
    start_time = end_time;
  }

  //---------------------------
}
