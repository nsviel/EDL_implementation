#include "Loop.h"
#include "Param.h"
#include "../UI/UI_loop.h"
#include "../UI/Vulkan/UI_main.h"

#include <Engine.h>
#include <Render/Render_node.h>
#include <Render/GPU/GPU_gui.h>
#include <Render/Vulkan/VK_engine.h>
#include <Render/Camera/Camera.h>
#include <GUI/Node_gui.h>

#include <Window/Window.h>
#include <iostream>


//Constructor / Destructor
Loop::Loop(){
  //---------------------------

  this->window = new Window();
  this->ui_loop = new UI_loop();
  this->engine = new Engine(window);
  
  //---------------------------
}
Loop::~Loop(){}

//Main function
void Loop::main_loop(){
    UI_main gui(window);

  Param param;
  Render_node* render_node = engine->get_node_render();
  VK_engine* vk_engine = render_node->get_vk_engine();
  Camera* cameraManager = render_node->get_cameraManager();
  Node_gui* node_gui = engine->get_node_gui();
  GPU_gui* gpu_gui = vk_engine->get_gpu_gui();
  //---------------------------

  window->create_window(param.window_dim.x, param.window_dim.y, param.window_title);


  //gui.init_gui();
  engine->init();
  ui_loop->init(engine);


  auto start_time = std::chrono::steady_clock::now();
  while(!glfwWindowShouldClose(window->get_window())){
    glfwPollEvents();
    ui_loop->loop(engine);
    engine->loop();
    //gui.run_gui_main();
  }

  engine->exit();
  window->destroy_window();

  //---------------------------
}
