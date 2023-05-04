#include "Engine.h"

#include "../Vulkan/Engine_vulkan.h"
#include "../Node_engine.h"


//Constructor / Destructor
Engine::Engine(){
  //---------------------------

  this->node_engine = new Node_engine();
  this->engine_vulkan = node_engine->get_engine_vulkan();

  //---------------------------
}
Engine::~Engine(){
  //---------------------------

  delete node_engine;

  //---------------------------
}

//Main function
void Engine::init_engine(){
  //---------------------------

  engine_vulkan->init_vulkan();
  node_engine->init();

  //---------------------------
}
void Engine::loop(){
  //---------------------------

  engine_vulkan->main_loop();

  //---------------------------
}
void Engine::cleanup(){
  //---------------------------

  engine_vulkan->clean_vulkan();



  //---------------------------
}
