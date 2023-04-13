#include "Node_engine.h"

#include "Core/Engine_window.h"
#include "Vulkan/Engine_vulkan.h"
#include "Core/GUI.h"
#include "Loop/Loop.h"


//Constructor / Destructor
Node_engine::Node_engine(){
  //---------------------------

  this->engine_window = new Engine_window(this);
  this->engine_vulkan = new Engine_vulkan(this);
  this->engine_loop = new Loop(this);
  this->guiManager = new GUI(this);

  //---------------------------
}
Node_engine::~Node_engine(){
  //---------------------------

  delete engine_window;
  delete engine_vulkan;
  delete engine_loop;

  //---------------------------
}

//Main function
