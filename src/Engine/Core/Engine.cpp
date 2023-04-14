#include "Engine.h"

#include "../Vulkan/Engine_vulkan.h"

#include "../Node_engine.h"
#include "../Loop/Loop.h"


//Constructor / Destructor
Engine::Engine(){
  //---------------------------

  this->node_engine = new Node_engine();
  this->engine_vulkan = node_engine->get_engine_vulkan();
  this->engine_loop = node_engine->get_engine_loop();

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
