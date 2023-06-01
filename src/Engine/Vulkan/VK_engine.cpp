#include "VK_engine.h"

#include "VK_param.h"
#include "Pipeline/Renderpass/VK_renderpass.h"
#include "Pipeline/VK_pipeline.h"
#include "Pipeline/Command/VK_command.h"
#include "Pipeline/Command/VK_synchronization.h"
#include "Shader/Descriptor/VK_descriptor.h"
#include "Shader/Binding/VK_uniform.h"
#include "Shader/VK_shader.h"
#include "Shader/Binding/VK_binding.h"
#include "Data/VK_buffer.h"
#include "Data/VK_texture.h"
#include "Data/VK_data.h"
#include "Pipeline/Command/VK_drawing.h"
#include "Instance/Device/VK_device.h"
#include "Instance/Device/VK_physical_device.h"
#include "Instance/Element/VK_window.h"
#include "Instance/Element/VK_gui.h"
#include "Instance/VK_instance.h"
#include "Instance/Element/VK_validation.h"
#include "Pipeline/Renderpass/VK_framebuffer.h"
#include "Pipeline/Rendering/VK_canvas.h"
#include "Pipeline/Attachment/VK_depth.h"
#include "Pipeline/Attachment/VK_color.h"
#include "Presentation/Swapchain/VK_swapchain.h"
#include "Presentation/Swapchain/VK_frame.h"
#include "Presentation/Camera/VK_viewport.h"
#include "Presentation/Camera/VK_camera.h"

#include "../Node_engine.h"
#include "../Param_engine.h"


//Constructor / Destructor
VK_engine::VK_engine(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->param_engine = node_engine->get_param_engine();

  this->vk_param = new VK_param();
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
  this->vk_descriptor = new VK_descriptor(this);
  this->vk_binding = new VK_binding(this);
  this->vk_data = new VK_data(this);
  this->vk_synchronization = new VK_synchronization(this);
  this->vk_swapchain = new VK_swapchain(this);
  this->vk_renderpass = new VK_renderpass(this);
  this->vk_framebuffer = new VK_framebuffer(this);
  this->vk_frame = new VK_frame(this);
  this->vk_shader = new VK_shader(this);
  this->vk_pipeline = new VK_pipeline(this);
  this->vk_camera = new VK_camera(this);
  this->vk_canvas = new VK_canvas(this);
  this->vk_command = new VK_command(this);
  this->vk_drawing = new VK_drawing(this);
  this->vk_gui = new VK_gui(this);

  //---------------------------
}
VK_engine::~VK_engine(){}

//Main function
void VK_engine::init_vulkan(){
  auto start = std::chrono::steady_clock::now();
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
  vk_canvas->create_canvas();

  //Pipeline
  vk_swapchain->create_swapchain();
  vk_renderpass->init_renderpass();
  vk_frame->init_image();
  vk_pipeline->init_pipeline();


  //PRIORITY
  //Switchr contenance de l'information c'est le renderpass qui contient un ou des pipelines et non le pipeline qui contient un renderpass associé
  //put framebuffer on canvas / put canvas front screen
    //-il faut une deuxième renderpass avec own commandbuffer et own images to render et own framebuffer
    //-abstraction framebuffer et convert it into a texture
    //-bind the texture to the quad
    //-when ok, suppress scene_2 pipeline

  //LATER
  //Essayer de ne relancer les commandes que lorsque cela changé
  // one command buffer per pipeline
  //Save the commands and redraw only necessary
  //Il faut que le descriptor layout des objects soit celui-ci du pipeline parent
    //-faire en sorte que ce soit le cas dans l'abosolu et non pas en parrallèle



  //Specific
  vk_gui->init_gui();

  //---------------------------
  auto end = std::chrono::steady_clock::now();
  this->time_init = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000.0f;
}
void VK_engine::main_loop() {
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

  vkDeviceWaitIdle(vk_param->device.device);

  //---------------------------
}
void VK_engine::clean_vulkan(){
  //---------------------------

  vk_gui->cleanup();
  vk_renderpass->clean_renderpass();
  vk_swapchain->clean_swapchain();
  vk_pipeline->cleanup();
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
void VK_engine::fps_control(const std::chrono::time_point<std::chrono::steady_clock>& start){
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
void VK_engine::fps_calcul(std::chrono::steady_clock::time_point& start_time){
  //---------------------------

  static int num_frames = 0;
  num_frames++;

  if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count() >= 1000){
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    this->time_fps = num_frames / (elapsed_time / 1000000.0);
    num_frames = 0;
    start_time = end_time;
  }

  //---------------------------
}
