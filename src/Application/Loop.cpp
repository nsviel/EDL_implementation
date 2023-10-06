#include "Loop.h"
#include "../config.h"

#include <GUI.h>
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
  this->gui = new GUI(engine);

  //---------------------------
}
Loop::~Loop(){}

//Main function
void Loop::run(){
  Config config;
  //---------------------------

  window->create_window(config.window_dim.x, config.window_dim.y, config.window_title);

  engine->init();
  gui->init();

  auto start_time = std::chrono::steady_clock::now();
  while(!window->window_should_close()){
    glfwPollEvents();

    gui->loop();
    engine->loop();
  }

  engine->exit();
  window->destroy_window();

  //---------------------------
}
