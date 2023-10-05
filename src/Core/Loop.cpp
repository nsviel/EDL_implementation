#include "Loop.h"
#include "Param.h"
#include "UI_loop.h"
#include "../Engine/Node.h"
#include "../Engine/Render/Render_node.h"
#include "../Engine/Render/GPU/GPU_gui.h"
#include "../Engine/Render/Vulkan/VK_engine.h"
#include "../Engine/Render/Camera/Camera.h"
#include "../Engine/GUI/Node_gui.h"

#include <Window/Window.h>


//Constructor / Destructor
Loop::Loop(){
  //---------------------------

  this->window = new Window();
  this->ui_loop = new UI_loop();
  this->node = new Node(window);

  //---------------------------
}
Loop::~Loop(){}

//Main function
void Loop::main_loop(){
  Param param;
  Render_node* render_node = node->get_node_render();
  VK_engine* vk_engine = render_node->get_vk_engine();
  Camera* cameraManager = render_node->get_cameraManager();
  Node_gui* node_gui = node->get_node_gui();
  GPU_gui* gpu_gui = vk_engine->get_gpu_gui();
  //---------------------------

  window->create_window(param.window_dim.x, param.window_dim.y, param.window_title);
  node->init();

  auto start_time = std::chrono::steady_clock::now();
  while(!glfwWindowShouldClose(window->get_window())){
    glfwPollEvents();
    ui_loop->loop_start();
    cameraManager->input_cam_mouse();
    node_gui->loop();
    gpu_gui->loop_end();
    vk_engine->draw_frame();

  }

  vk_engine->end_loop();
  node->exit();
  window->destroy_window();

  //---------------------------
}
