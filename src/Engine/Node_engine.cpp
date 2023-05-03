#include "Node_engine.h"

#include "Vulkan/Engine_vulkan.h"
#include "Loop/Loop.h"
#include "Core/Scene.h"
#include "Core/Dimension.h"

#include "../Load/Node_load.h"
#include "../GUI/Node_gui.h"


//Constructor / Destructor
Node_engine::Node_engine(){
  //---------------------------

  this->node_load = new Node_load(this);
  this->node_gui = new Node_gui(this);

  this->engine_vulkan = new Engine_vulkan(this);
  this->engine_loop = new Loop(this);
  this->sceneManager = new Scene(this);
  this->dimManager = new Dimension();

  //---------------------------
}
Node_engine::~Node_engine(){
  //---------------------------

  delete engine_vulkan;
  delete engine_loop;
  delete dimManager;
  delete sceneManager;

  delete node_load;
  delete node_gui;

  //---------------------------
}

//Main function
