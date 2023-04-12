#include "Loop.h"

#include "../Node_engine.h"
#include "../Core/Engine_window.h"
#include "../Core/Engine_vulkan.h"


//Constructor / Destructor
Loop::Loop(Node_engine* node_engine){
  //---------------------------

  this->engine_window = node_engine->get_engine_window();
  this->engine_vulkan = node_engine->get_engine_vulkan();

  //---------------------------
}
Loop::~Loop(){
  //---------------------------

  //---------------------------
}

//Main function
void Loop::run_loop(){
  //---------------------------



  //---------------------------
}
