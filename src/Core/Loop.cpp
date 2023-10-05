#include "Loop.h"
#include "Param.h"
#include "UI_loop.h"
#include "../Engine/Node.h"
#include "../Engine/Render/Render_node.h"
#include "../Engine/Render/GPU/GPU_gui.h"
#include "../Engine/Render/Vulkan/VK_engine.h"

#include <Window/Window.h>


//Constructor / Destructor
Loop::Loop(){
  //---------------------------

  this->window = new Window();
  this->ui_loop = new UI_loop();

  //---------------------------
}
Loop::~Loop(){}

//Main function
void Loop::main_loop(){
  Param param;
  Node node(window);

  //---------------------------

  window->create_window(param.window_dim.x, param.window_dim.y, param.window_title);
  node.init();
  Render_node* render_node = node.get_node_render();
  VK_engine* vk_engine = render_node->get_vk_engine();







  auto start_time = std::chrono::steady_clock::now();
  while(!glfwWindowShouldClose(window->get_window())){
    glfwPollEvents();
    ui_loop->loop_start();
    vk_engine->main_loop();

  }


  node.exit();

  window->destroy_window();

  //---------------------------
}
