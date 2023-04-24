#include "Engine.h"

#include "GUI.h"

#include "../Vulkan/Engine_vulkan.h"

#include "../Node_engine.h"
#include "../Loop/Loop.h"

#include "../../Load/Loader.h"


//Constructor / Destructor
Engine::Engine(){
  //---------------------------

  this->node_engine = new Node_engine();
  this->engine_vulkan = node_engine->get_engine_vulkan();
  this->engine_loop = node_engine->get_engine_loop();
  this->guiManager= node_engine->get_guiManager();

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
  guiManager->init();



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
