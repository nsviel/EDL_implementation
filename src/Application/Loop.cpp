#include "Loop.h"
#include "Param.h"
#include <GUI_node.h>
#include <Style/Vulkan/UI_main.h>

#include <Engine.h>
#include <Render/Render_node.h>
#include <Render/GPU/GPU_gui.h>
#include <Render/Vulkan/VK_engine.h>
#include <Camera/Camera.h>

#include <Window/Window.h>
#include <iostream>


//Constructor / Destructor
Loop::Loop(){
  //---------------------------

  this->window = new Window();
  this->engine = new Engine(window);
  this->gui_node = new GUI_node(engine);

  //---------------------------
}
Loop::~Loop(){}

//Main function
void Loop::main_loop(){
  Param param;
  //---------------------------

  window->create_window(param.window_dim.x, param.window_dim.y, param.window_title);

  engine->init();
  gui_node->init();

  auto start_time = std::chrono::steady_clock::now();
  while(!glfwWindowShouldClose(window->get_window())){
    glfwPollEvents();

    gui_node->loop();
    engine->loop();
  }

  engine->exit();
  window->destroy_window();

  //---------------------------
}
