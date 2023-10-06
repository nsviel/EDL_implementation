#include "Loop.h"
#include "Param.h"
#include "../GUI/UI_loop.h"
#include "../GUI/Vulkan/UI_main.h"

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
  this->ui_loop = new UI_loop();
  this->engine = new Engine(window);

  //---------------------------
}
Loop::~Loop(){}

//Main function
void Loop::main_loop(){
  Param param;
  //---------------------------

  window->create_window(param.window_dim.x, param.window_dim.y, param.window_title);

  engine->init();
  ui_loop->init(engine);

  auto start_time = std::chrono::steady_clock::now();
  while(!glfwWindowShouldClose(window->get_window())){
    glfwPollEvents();

    ui_loop->loop(engine);
    engine->loop();
  }

  engine->exit();
  window->destroy_window();

  //---------------------------
}
