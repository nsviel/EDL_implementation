#include "Node_engine.h"

#include "Vulkan/Engine_vulkan.h"
#include "Core/GUI.h"
#include "Loop/Loop.h"
#include "Core/Scene.h"
#include "Core/Dimension.h"

#include "../Load/Node_load.h"


//Constructor / Destructor
Node_engine::Node_engine(){
  //---------------------------

  this->engine_vulkan = new Engine_vulkan(this);
  this->engine_loop = new Loop(this);
  this->sceneManager = new Scene(this);
  this->dimManager = new Dimension();
  this->guiManager = new GUI(this);

  this->node_load = new Node_load(this);

  //---------------------------
}
Node_engine::~Node_engine(){
  //---------------------------

  delete engine_vulkan;
  delete engine_loop;
  delete dimManager;
  delete sceneManager;

  //---------------------------
}

//Main function
