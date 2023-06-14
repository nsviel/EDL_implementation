#include "VK_engine.h"
#include "VK_param.h"

#include "Data/VK_buffer.h"
#include "Data/VK_data.h"

#include "Core/Renderpass/VK_renderpass.h"
#include "Core/Pipeline/VK_pipeline.h"
#include "Core/Command/VK_command.h"
#include "Core/Command/VK_synchronization.h"
#include "Core/Command/VK_submit.h"
#include "Core/Command/VK_command_buffer.h"
#include "Core/Drawing/VK_cmd.h"
#include "Core/Drawing/VK_drawing.h"

#include "Instance/Device/VK_device.h"
#include "Instance/Device/VK_physical_device.h"
#include "Instance/Element/VK_window.h"
#include "Instance/Element/VK_gui.h"
#include "Instance/Instance/VK_instance.h"
#include "Instance/Instance/VK_validation.h"

#include "Render/Canvas/VK_canvas.h"
#include "Render/Shader/VK_shader.h"
#include "Render/Binding/VK_descriptor.h"
#include "Render/Binding/VK_binding.h"
#include "Render/Binding/VK_uniform.h"

#include "Presentation/Image/VK_depth.h"
#include "Presentation/Image/VK_color.h"
#include "Presentation/Image/VK_texture.h"
#include "Presentation/Image/VK_image.h"
#include "Presentation/Swapchain/VK_swapchain.h"
#include "Presentation/Swapchain/VK_framebuffer.h"
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
  this->vk_uniform = new VK_uniform(this);
  this->vk_image = new VK_image(this);
  this->vk_texture = new VK_texture(this);
  this->vk_depth = new VK_depth(this);
  this->vk_color = new VK_color(this);
  this->vk_descriptor = new VK_descriptor(this);
  this->vk_binding = new VK_binding(this);
  this->vk_data = new VK_data(this);
  this->vk_synchronization = new VK_synchronization(this);
  this->vk_swapchain = new VK_swapchain(this);
  this->vk_shader = new VK_shader(this);
  this->vk_pipeline = new VK_pipeline(this);
  this->vk_renderpass = new VK_renderpass(this);
  this->vk_framebuffer = new VK_framebuffer(this);
  this->vk_frame = new VK_frame(this);
  this->vk_camera = new VK_camera(this);
  this->vk_canvas = new VK_canvas(this);
  this->vk_cmd = new VK_cmd(this);
  this->vk_command_buffer = new VK_command_buffer(this);
  this->vk_command = new VK_command(this);
  this->vk_submit = new VK_submit(this);
  this->vk_gui = new VK_gui(this);
  this->vk_drawing = new VK_drawing(this);

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
  vk_physical_device->init_physical_device();
  vk_device->create_logical_device();
  vk_command_buffer->create_command_pool();
  vk_descriptor->create_descriptor_pool();
  vk_canvas->create_canvas();

  //Pipeline
  vk_swapchain->create_swapchain();
  vk_renderpass->init_renderpass();
  vk_frame->create_frame_swapchain(&vk_param->swapchain);


  //WORK
  //Subpass managment
  //Optimization
    //-use dynamic uniform buffer for mvp
    //-use pre-recorded command buffer

    //Create and record individual command buffers: For each object in the scene, create a separate command buffer that contains the rendering commands specific to that object. The command buffer should include the necessary pipeline binding, vertex buffer binding, descriptor set binding, and draw commands.
    //Record initial MVP matrices: During the initial recording of each command buffer, set the initial MVP matrices for each object. These matrices can be set as static data or based on the initial state of the objects in the scene.
    //Update MVP matrices: Whenever the MVP matrices of the objects need to be updated (e.g., due to object movement or animation), update the corresponding matrices in the CPU memory. You can update the matrices independently for each object.
    //Bind updated MVP matrices: Before executing the pre-recorded command buffers, bind the updated MVP matrices to the appropriate descriptor sets. This involves updating the descriptor sets with the new data, specifying the updated buffer bindings or dynamic offsets.
    //Execute the pre-recorded command buffers: Submit the pre-recorded command buffers for execution, and Vulkan will render the objects in the scene using the updated MVP matrices.

  //Specific
  vk_gui->init_gui();

  //---------------------------
  auto end = std::chrono::steady_clock::now();
  vk_param->time.engine_init = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000.0f;
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

  vk_gui->clean_gui();
  vk_renderpass->clean_renderpass();
  vk_swapchain->clean_swapchain();
  vk_canvas->clean_canvas();
  vk_data->clean_data();
  vk_descriptor->clean_descriptor_pool();
  vk_command_buffer->clean_command_pool();
  vk_device->clean_logical_device();
  vk_window->clean_surface();
  vk_validation->clean_layer();
  vk_instance->clean_instance();
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
    vk_param->time.engine_fps = num_frames / (elapsed_time / 1000000.0);
    num_frames = 0;
    start_time = end_time;
  }

  //---------------------------
}
